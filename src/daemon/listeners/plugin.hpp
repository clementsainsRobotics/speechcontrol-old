/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) 2013  Jacky Alcine <me@jalcine.me>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/


#ifndef SPEECHCONTROL_PLUGINS_ABSTRACTPLUGIN_HPP
#define SPEECHCONTROL_PLUGINS_ABSTRACTPLUGIN_HPP

#include <QUrl>
#include <QObject>
#include <QSettings>

namespace SpeechControl {
namespace Listeners {
class AbstractListener;
class AbstractPlugin : public QObject
{
  Q_OBJECT
public:
  explicit AbstractPlugin(QObject* parent = 0);
  virtual AbstractListener* listener() const = 0;
  virtual QSettings* settings() const = 0;
  static QUrl settingsPath(const QString& p_listenerName);
  virtual ~AbstractPlugin();
};

}

}

#endif // SPEECHCONTROL_PLUGINS_ABSTRACTPLUGIN_HPP
