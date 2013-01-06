/*
 * This file is part of SpeechControl.
 *
 * Copyright 2013 Jacky Alcine <jacky.alcine@thesii.org>
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
#include "listener.hpp"
#include "listeners/plugin.hpp"
#include "listeners/loader.hpp"
#include "global.hpp"

using SpeechControl::Listeners::AbstractListener;
using SpeechControl::Listeners::AbstractPlugin;
using SpeechControl::Listeners::Loader;

Loader::Loader(const QString& p_listenerName, QObject* parent): QPluginLoader(parent)
{
  QString libraryName("libspeechcontrol-listener-" + p_listenerName + ".so");
  libraryName.prepend("/");
  libraryName.prepend(SPCHCNTRL_LISTENERS_LIB_PATH);
  qDebug() << "Lib path: " << libraryName;
  setFileName(libraryName);
}

AbstractListener* Loader::listenerInstance()
{
  if (!isLoaded()){
    qDebug() << "Bad library." << this->errorString() << this->fileName();
    return 0;
  } else {
    QObject* instance = this->instance();
    AbstractPlugin* plugin = qobject_cast<AbstractPlugin*>(instance);
    
    if (instance == 0){
      qDebug() << "Instance nil.";
      return 0;
    } else {
      AbstractListener* listener = plugin->listener();
      
      if (listener == 0){
	qDebug() << "Listener nil.";
	return 0;
      } else {
	return listener;
      }
    }
  }
  
  return 0;
}

bool Loader::isLoaded() const
{
  return QPluginLoader::isLoaded();
}

bool Loader::load()
{
  return QPluginLoader::load();
}

Loader::~Loader()
{

}

#include "loader.moc"