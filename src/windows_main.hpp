 /**
  * This file is part of SpeechControl
  *
  * Copyright 2011 Jacky Alcine <jacky.alcine@thesii.org>
  *
  * SpeechControl is free software; you can redistribute it and/or modify
  * it under the terms of the GNU Library General Public License as
  * published by the Free Software Foundation; either version 2 of the
  * License, or (at your option) any later version.
  *
  * SpeechControl is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  * GNU General Public License for more details.
  *
  * You should have received a copy of the GNU General Public
  * License along with SpeechControl; if not, write to the
  * Free Software Foundation, Inc.,
  * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
  */

#ifndef MAIN_HPP
#define MAIN_HPP

#include <QObject>
#include <QMainWindow>

namespace Ui {
    class MainWindow;
}

namespace SpeechControl {
    class User;
    namespace Windows {
        class Main : public QMainWindow {
            Q_OBJECT
        public:
            explicit Main();
            ~Main();

        private slots:
            void tabChanged(const int& );
            void on_radioButtonDictation_toggled(bool checked);
            void on_radioButtonControl_toggled(bool checked);
            void on_checkBoxAutoStart_toggled(bool checked);
            void toggleTraining(bool);
            void buildMenus();
            void loadUser(const User&);
            void doSwitchBooks();
            void doSaveProgress();
            void doSaveProgressAs();
            void doRestoreBackup();
            void doMakeBackup();
            void doShowBackups();
            void doSwitchUsers();
            void doCreateUserWizard();
            void doAddWord();
            void doRemoveWord();
            void doViewWord();

            void on_pushButtonTestMic_clicked();

        private:
            Ui::MainWindow* m_ui;
        };
    }
}

#endif // MAIN_HPP
