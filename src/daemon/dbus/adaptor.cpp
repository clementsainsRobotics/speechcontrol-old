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

#include "adaptor.hpp"
#include "../instance.hpp"
#include <QCoreApplication>

using SpeechControl::Listeners::AbstractListener;
using SpeechControl::Daemon::Instance;
using SpeechControl::Daemon::Dbus::Adaptor;

Adaptor::Adaptor(Instance* p_instance) : QDBusAbstractAdaptor(p_instance)
{
  setAutoRelaySignals(true);
}

Instance* Adaptor::instance() const
{
  return qobject_cast<SpeechControl::Daemon::Instance*>(parent());
}

bool Adaptor::isListening(const QString& p_listenerName) const
{
  return instance()->isListening(p_listenerName);
}

void Adaptor::startListening(const QString& p_listenerName)
{
  instance()->startListening(p_listenerName);
}

void Adaptor::stopListening(const QString& p_listenerName)
{
  instance()->stopListening(p_listenerName);
}

QStringList Adaptor::listeners() const
{
  return instance()->listenerNames();
}

void Adaptor::disableListener(const QString& p_listenerName)
{
  AbstractListener::disableListener(p_listenerName);
}

void Adaptor::enableListener(const QString& p_listenerName)
{
  AbstractListener::enableListener(p_listenerName);
}

bool Adaptor::isListenerEnabled(const QString& p_listenerName) const
{
  QSettings settings;
  return settings.value("Enabled_Listeners/" + p_listenerName,false).toBool();
}

QString Adaptor::currentListener() const
{
  if (instance()->listener() != 0){
    return instance()->listener()->name();
  }
  
  return QString::null;
}

Adaptor::~Adaptor()
{

}

#include "adaptor.moc"