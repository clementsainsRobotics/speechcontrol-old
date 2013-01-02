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

#ifndef SPEECHCONTROL_LISTENER_HPP
#define SPEECHCONTROL_LISTENER_HPP

#include <QObject>
#include <QString>
#include <QList>
#include <QSettings>

namespace SpeechControl {
class AbstractListener;

typedef QList<AbstractListener*> AbstractListenerList;


class AbstractListener : public QObject
{

public:
  explicit AbstractListener(QObject* parent = 0);
  virtual ~AbstractListener();
    
  virtual QString name() const = 0;
  virtual bool active() const = 0;
  
  static AbstractListenerList listeners();
  static QStringList listenerNames();
  static bool enableListener(QString& listenerName);
  static bool disableListener(QString& listenerName);
  static AbstractListener* obtain(QString& listenerName);
  
public slots:
  virtual void start() = 0;
  virtual void stop() = 0;

protected:
  virtual void enable();
  virtual void disable();

signals:
  void finishedListening(QString& result);
  void startedListening();
  void stoppedListening();
  
private:
  QSettings* settings;
  void loadSettings();
};

}

#endif // SPEECHCONTROL_LISTENER_HPP
