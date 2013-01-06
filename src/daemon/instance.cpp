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
 listeners(), curListener(0)
{
  this->initializeDbus();
  QCoreApplication::addLibraryPath(SPCHCNTRL_LISTENERS_LIB_PATH);
  QStringList listeners = AbstractListener::listenerNames();
  qDebug () << "Found" << listeners.count() << "listener(s);" << listeners;
  foreach (QString listener, listeners){
    AbstractListener* instanceListener = AbstractListener::obtain(listener);
    
    if (instanceListener != 0){
      qDebug() << "Loaded listener" << instanceListener->name();
    } else {
      qDebug() << "Invalid listener" << listener;
    }
  }
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
  if (listener() != 0){
    listener()->start();
  }
  
  emit startedListening();
}

void Instance::stopListening(const QString& p_listenerName)
{
  if (listener() != 0){
    listener()->stop();
  }
  
  emit stoppedListening();
}

AbstractListener* Instance::listener() const
{
  return curListener;
}

Instance::~Instance()
{

}

#include "instance.moc"