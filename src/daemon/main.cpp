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

#include <QCoreApplication>
#include "global.hpp"
#include "instance.hpp"

using SpeechControl::Daemon::Instance;

int main(int argc, char** argv){
 // Lemme get a QCoreApplication for 200.
 QCoreApplication* app = new QCoreApplication(argc,argv);
 
 // Now, grab that instance one time!
 Instance* instance = new Instance();
 
 // Who's your momma?!
 instance->setParent(app);
 
 qDebug() << "Starting up D-Bus...";
 
 instance->initializeDbus();
 
 qDebug() << "D-Bus should be started.";
 
 return app->exec();
}
