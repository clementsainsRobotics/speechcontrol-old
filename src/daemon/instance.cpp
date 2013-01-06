/*
 * This file is part of SpeechControl.
 *
 * Copyright 2012 Jacky Alcine <jacky.alcine@thesii.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Library General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this program; if not, write to the
 * Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#include <QDebug>
#include <QDBusConnection>
#include <QCoreApplication>

#include "global.hpp"
#include "instance.hpp"
#include "dbus/adaptor.hpp"
#include "listener.hpp"

using SpeechControl::Daemon::Dbus::Adaptor;
using SpeechControl::Daemon::Instance;
using SpeechControl::Listeners::AbstractListener;

Instance::Instance() : QObject(QCoreApplication::instance()), bus(QDBusConnection::sessionBus()),
 listeners()
{
  this->initializeDbus();
  QCoreApplication::addLibraryPath(SPCHCNTRL_LISTENERS_LIB_PATH);
  QStringList listeners = AbstractListener::listenerNames();
}

void Instance::initializeDbus()
{
  bus.connectToBus(QDBusConnection::SessionBus,"SpeechControl");
  bus.registerService("org.thesii.SpeechControl");

  Adaptor* adaptor = new Adaptor(this);
  bus.registerObject("/Daemon",adaptor,QDBusConnection::ExportAllContents);
}

QStringList Instance::listenerNames() const
{
  return AbstractListener::listenerNames();
}

bool Instance::isListening(const QString& p_listenerName) const
{
  if (this->listeners.empty()){
    return false;
  }
  
  foreach (AbstractListener* listener, this->listeners){
    if (listener->active())
      return true;
  }
  
  return false;
}

void Instance::startListening(const QString& p_listenerName)
{
  AbstractListener* listener = 0;
  listener = obtainListener(p_listenerName);
  if (listener){
    connect(listener,SIGNAL(startedListening()),this,SIGNAL(startedListening()));
    connect(listener,SIGNAL(stoppedListening()),this,SIGNAL(stoppedListening()));
    connect(listener,SIGNAL(finishedListening(QString)),this,SLOT(captureFinishedResult(QString)));
    listener->start();
  }  
}

void Instance::stopListening(const QString& p_listenerName)
{
  AbstractListener* listener = 0;
  listener = obtainListener(p_listenerName);
  if (listener){
    disconnect(listener,SIGNAL(startedListening()),this,SIGNAL(startedListening()));
    disconnect(listener,SIGNAL(stoppedListening()),this,SIGNAL(stoppedListening()));
    listener->stop();
  }
}

AbstractListener* Instance::obtainListener(QString p_listenerName)
{
  AbstractListener* listener = 0;
  
  if (listeners.count(p_listenerName) == 0){
    listener = AbstractListener::obtain(p_listenerName);
    
    if (listener != 0){
      qDebug() << "Made a new instance of a listener of" << p_listenerName << ".";
      listeners.insert(p_listenerName,listener);
    }
  } else {
    listener = listeners.value(p_listenerName);
  }
  
  return listener;
}


void Instance::captureFinishedResult(const QString& p_listenerText)
{
  qDebug() << "Word on the block was " << p_listenerText;
  emit finishedListening(QString::null,p_listenerText);
}

Instance::~Instance()
{

}

#include "instance.moc"