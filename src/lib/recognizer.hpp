/***
 *  This file is part of SpeechControl.
 *
 *  Copyright (C) 2012 Jacky Alcine <jacky.alcine@thesii.org>
 *
 *  SpeechControl is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Library General Public
 *  License as published by the Free Software Foundation; either
 *  version 2 of the License, or (at your option) any later version.
 *
 *  SpeechControl is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Library General Public License for more details.
 *
 *  You should have received a copy of the GNU Library General Public License
 *  along with SpeechControl .  If not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */


#ifndef SPEECHCONTROL_DESYNTHESIZER_HPP
#define SPEECHCONTROL_DESYNTHESIZER_HPP

#include <QObject>
#include <QByteArray>
#include <QDataStream>
#include <QTemporaryFile>
#include <agent.hpp>

namespace SpeechControl {
 class Recognizer : public QObject {
  Q_OBJECT
  private:
   QTemporaryFile* file;
   static QList<RecognizingAgent*> agentList;

  public:
   enum States {
    Unknown = 0x000,
    Active  = 0x001
   };

   Recognizer(QObject* parent = 0);
   virtual ~Recognizer();
   void setAudioSource(QByteArray& data);
   virtual void start();
   virtual void stop();
   static void registerAgent(RecognizingAgent* agent);
   static QList<RecognizingAgent*> agents();

  signals:
   void stateChanged(Recognizer::States state);
   void recognitionCompleted();
   void recognitionProducedText(QString text);
   void recognitionFailed();
 };
}

#endif