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

#include <QDir>
#include <QStringList>
#include "listener.hpp"
#include "global.hpp"

using SpeechControl::AbstractListener;
using SpeechControl::AbstractListenerList;

AbstractListener::AbstractListener(QObject* parent): QObject(parent), settings(0)
{
  loadSettings();
}

void AbstractListener::loadSettings()
{
  QString path = SPCHCNTRL_LISTENERS_PATH;
  path += "/" + name() + ".spec";
  settings = new QSettings(path);
}

AbstractListenerList AbstractListener::listeners()
{
  QDir dir (SPCHCNTRL_LISTENERS_PATH);
  dir.setFilter (QDir::Files | QDir::Readable | QDir::NoSymLinks);
  dir.setNameFilters (QString ("*.spec").split (" "));
  dir.setSorting (QDir::Name);
  QStringList listenerNames = dir.entryList().replaceInStrings (".spec", "");
  return AbstractListenerList();
}

QStringList AbstractListener::listenerNames()
{
  QStringList names;
  foreach (AbstractListener* listener, listeners()){
    names << listener->name();
  }
  
  return names;
}

AbstractListener* AbstractListener::obtain(QString& listenerName)
{
  return 0; // for now.
}

bool AbstractListener::disableListener(QString& listenerName)
{
  AbstractListener* listener = AbstractListener::obtain(listenerName);
  listener->disable();
}

bool AbstractListener::enableListener(QString& listenerName)
{
  AbstractListener* listener = AbstractListener::obtain(listenerName);
  listener->enable();
}

void AbstractListener::disable()
{
  if (active()){
    stop();
  }
  
  settings->setValue("Listener/Enabled",false);
}

void AbstractListener::enable()
{
  settings->setValue("Listener/Enabled",true);
}

AbstractListener::~AbstractListener()
{

}