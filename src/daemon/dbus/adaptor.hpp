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

#ifndef SPEECHCONTROL_DAEMON_DBUS_ADAPTOR_HPP
#define SPEECHCONTROL_DAEMON_DBUS_ADAPTOR_HPP

#include <QDBusAbstractAdaptor>

namespace SpeechControl {
 namespace Daemon {

 class Instance;

  namespace Dbus {
   
   /**
    * @class Adaptor
    * @namespace SpeechControl::Daemon::Dbus
    * 
    * This adaptor serves as the single adaptor required for communication in
    * order to handle the speech recognition services of SpeechControl.
    */
   class Adaptor : public QDBusAbstractAdaptor
   {
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "org.thesii.SpeechControl.Daemon")
    
    public:
     Adaptor(Instance* p_instance);
     virtual ~Adaptor();

    public slots:
      Q_NOREPLY void startListening();
      Q_NOREPLY void stopListening();
      bool isListening() const;
      QStringList listeners() const;
      
    signals:
      void stoppedListening();
      void startedListening();
      
    private:
     Instance* instance() const;
   };
  }
 }
}

#endif // SPEECHCONTROL_DAEMON_DBUS_ADAPTOR_HPP
