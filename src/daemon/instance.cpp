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

#include "instance.hpp"
#include "dbus/adaptor.hpp"
#include "listener.hpp"

using SpeechControl::Daemon::Dbus::Adaptor;
using SpeechControl::Daemon::Instance;
using SpeechControl::AbstractListener;

Instance::Instance() : QObject(QCoreApplication::instance()), bus(QDBusConnection::sessionBus())
{
  this->initializeDbus();
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

bool Instance::isListening() const
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

void Instance::startListening()
{

}

void Instance::stopListening()
{

}

Instance::~Instance()
{

}

#include "instance.moc"