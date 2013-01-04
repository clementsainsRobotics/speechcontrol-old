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

#include "listener.hpp"
#include "listeners/plugin.hpp"
#include "listeners/loader.hpp"

using SpeechControl::Listeners::AbstractListener;
using SpeechControl::Listeners::AbstractPlugin;
using SpeechControl::Listeners::Loader;

Loader::Loader(QString& p_listenerName, QObject* parent): QPluginLoader(parent)
{
  QString libraryName(p_listenerName + ".so");
  setFileName(libraryName);
}

AbstractListener* Loader::listenerInstance()
{
  if (!isLoaded()){
    return 0;
  } else {
    QObject* instance = this->instance();
    AbstractPlugin* plugin = qobject_cast<AbstractPlugin*>(instance);
    
    if (instance == 0){
      return 0;
    } else {
      AbstractListener* listener = plugin->listener();
      
      if (listener == 0){
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