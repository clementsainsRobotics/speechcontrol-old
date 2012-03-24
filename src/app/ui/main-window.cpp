/***
 * This file is part of SpeechControl
 *
 * Copyright 2011 SpeechControl Developers <spchcntrl-devel@thesii.org>
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

#include <QFile>
#include <QUuid>
#include <QDebug>
#include <QVariant>
#include <QSettings>
#include <QProcess>
#include <QErrorMessage>
#include <QMessageBox>
#include <QPushButton>
#include <QTableWidget>
#include <QCloseEvent>
#include <QMenu>

#include <lib/abstractaudiosource.hpp>

#include "core.hpp"
#include "indicator.hpp"
#include "dictation/agent.hpp"
#include "desktopcontrol/agent.hpp"
#include "sessions/session.hpp"
#include "sessions/content.hpp"
#include "uimain-window.hpp"
#include "uitraining-dialog.hpp"
#include "uisettings-dialog.hpp"
#include "uicontent-manager.hpp"
#include "uisession-manager.hpp"
#include "uiabout-dialog.hpp"
#include "uiquickstart-wizard.hpp"
#include "uimicsetup-wizard.hpp"
#include "uicontents-wizard.hpp"
#include "uiadapt-wizard.hpp"
#include "ui_main-window.h"

using namespace SpeechControl;
using namespace SpeechControl::Windows;
using namespace SpeechControl::Wizards;
using namespace SpeechControl::Windows::Managers;

using SpeechControl::Windows::Main;

/// @todo Add icons to the QActions.
Main::Main() : m_ui (new Ui::MainWindow), m_prgStatusbar (0)
{
    m_ui->setupUi (this);
    m_ui->retranslateUi (this);
    m_prgStatusbar = new QProgressBar (this);

    // Do a bit of cleanup on the status bar.
    m_ui->statusBar->addPermanentWidget (m_prgStatusbar);
    m_prgStatusbar->setMaximum (100);
    setProgress (0.0);

    // Update icons.
    m_ui->actionQuit->setIcon (QIcon::fromTheme ("application-exit"));
    m_ui->actionAboutSpeechControl->setIcon (QIcon (":/logo/sc"));
    m_ui->actionReportBug->setIcon (QIcon::fromTheme ("tools-report-bug"));
    m_ui->actionOptions->setIcon (QIcon::fromTheme ("configure"));
    m_ui->actionWizardMicrophone->setIcon (QIcon::fromTheme ("audio-input-microphone"));
    m_ui->menuDictation->setIcon (QIcon::fromTheme ("audio-input-microphone"));
    m_ui->menuDesktopControl->setIcon (QIcon::fromTheme ("audio-headset"));
    m_ui->actionWizardContent->setIcon (QIcon::fromTheme ("x-office-document"));
    m_ui->actionWizardAdaption->setIcon (QIcon::fromTheme ("configure"));
    m_ui->actionDesktopControlCommands->setIcon (QIcon::fromTheme ("view-list-text"));
    m_ui->actionStartTraining->setIcon (QIcon::fromTheme ("system-run"));
    m_ui->actionHelp->setIcon (QIcon::fromTheme ("help"));

    // Update the actions and buttons.
    connect (DesktopControl::Agent::instance(), SIGNAL (stateChanged (ActivityState)), this, SLOT (desktopControlStateChanged()));
    connect (Dictation::Agent::instance(), SIGNAL (stateChanged (ActivityState)), this, SLOT (dictationStateChanged()));
    desktopControlStateChanged();
    dictationStateChanged();
    on_actionDesktopControlActive_triggered (DesktopControl::Agent::instance()->isActive());
    on_actionDictationActive_triggered (Dictation::Agent::instance()->isActive());

    // Greet the user :)
    setStatusMessage (tr ("Welcome to %1, speech recognition for Linux.").arg (QApplication::applicationName()), 4000);
}

void Main::closeEvent (QCloseEvent* p_closeEvent)
{
    qDebug() << "[Windows::Main::hide()] Is indicator visible?" << Indicator::instance()->isVisible();

    if (Indicator::instance()->isVisible()) {
        QErrorMessage* l_msg = new QErrorMessage (this);
        l_msg->setModal (true);
        l_msg->setWindowTitle (tr ("Hidden From View"));
        l_msg->showMessage (tr ("SpeechControl has been hidden into the system's tray."
                                "You can restore it by clicking the menu and selecting 'Restore'."), "HiddenToTray");
        p_closeEvent->ignore();
        this->hide();
    }
    else {
        if (QMessageBox::Yes == QMessageBox::question (this, "Confirm Quit", "Are you sure you want to quit SpeechControl?", QMessageBox::Yes | QMessageBox::No)) {
            p_closeEvent->accept();
            QApplication::quit();
        }
        else {
            p_closeEvent->ignore();
        }
    }

    if (Core::configuration ("MainWindow/RememberState").toBool()) {
        Core::setConfiguration ("MainWindow/Geometry", saveGeometry());
        Core::setConfiguration ("MainWindow/State", saveState());

        if (Indicator::instance()->isVisible())
            Core::setConfiguration ("MainWindow/Visible", isVisible());
        else
            Core::setConfiguration ("MainWindow/Visible", true);
    }
}

void Main::open()
{
    if (DeviceAudioSource::allDevices().empty()) {
        QErrorMessage* l_msg = new QErrorMessage (this);
        l_msg->setModal (true);
        l_msg->setWindowTitle (tr ("No Microphones Found"));
        l_msg->showMessage (tr ("No microphones were found on your system. Please ensure that you have one installed and detectable by "
                                "the audio system and make sure that <b>%1</b> is installed on your system.").arg ("gstreamer-plugins-good"),
                            "NoMicrophonesFoundOnStart");
    }

    updateWindow();

    if (Core::configuration ("MainWindow/RememberState").toBool()) {
        restoreGeometry (Core::configuration ("MainWindow/Geometry").toByteArray());
        restoreGeometry (Core::configuration ("MainWindow/State").toByteArray());
        const bool isIndicatorVisible = Indicator::instance()->isVisible() && Core::configuration ("MainWindow/Visible").toBool() == true;

        if (isIndicatorVisible || !Indicator::instance()->isVisible())
            QMainWindow::show();
        else
            QMainWindow::hide();
    }
    else {
        QMainWindow::show();
    }
}

void Main::setStatusMessage (const QString& p_message , const int p_timeout)
{
    m_ui->statusBar->showMessage (p_message, p_timeout);
}

void Main::desktopControlStateChanged()
{
    switch (DesktopControl::Agent::instance()->state()) {
    case AbstractAgent::ActivityState::Enabled:
        setStatusMessage (tr ("Desktop control activated."));
        break;
    case AbstractAgent::ActivityState::Disabled:
        setStatusMessage (tr ("Desktop control deactivated."));
        break;
    default:
        break;
    }
}

void Main::dictationStateChanged()
{
    switch (Dictation::Agent::instance()->state()) {
    case AbstractAgent::ActivityState::Enabled:
        setStatusMessage (tr ("Dictation activated."));
        break;
    case AbstractAgent::ActivityState::Disabled:
        setStatusMessage (tr ("Dictation deactivated."));
        break;
    default:
        break;
    }
}

/// @todo Instead of this constant ticking, use signals to update this code.
void Main::updateText()
{
    m_ui->lblSessions->setText (QString::number (Session::allSessions().count()));
    m_ui->lblContent->setText (QString::number (Content::allContents().count()));
    m_ui->lblAccuracy->setText ("N/A");
    m_ui->lblSpeechIndex->setText ("N/A");
}

void Main::updateUi()
{
    // update desktop control & dictation buttons.
    const bool dictationActive = Dictation::Agent::instance()->isActive();
    const bool dictationEnabled = Dictation::Agent::instance()->isEnabled();
    const bool desktopControlActive = DesktopControl::Agent::instance()->isActive();
    const bool desktopControlEnabled = DesktopControl::Agent::instance()->isEnabled();

    m_ui->btnDsktpCntrl->setEnabled (desktopControlEnabled);
    m_ui->actionDesktopControlActive->setEnabled (desktopControlEnabled);

    if (desktopControlEnabled) {
        m_ui->btnDctn->setChecked (dictationActive);
        m_ui->btnDctn->setIcon ( ( (dictationActive) ? QIcon::fromTheme ("media-record") : QIcon::fromTheme ("media-playback-pause")));
    }

    m_ui->btnDctn->setEnabled (dictationEnabled);
    m_ui->actionDictationActive->setEnabled (dictationEnabled);

    if (dictationEnabled) {
        m_ui->btnDsktpCntrl->setChecked (desktopControlActive);
        m_ui->btnDsktpCntrl->setIcon ( (desktopControlActive ? QIcon::fromTheme ("media-record") : QIcon::fromTheme ("media-playback-pause")));
    }

    m_ui->btnAdapt->setEnabled(!Session::completedSessions().isEmpty());
}


void Main::setProgress (const double p_progress)
{
    const int l_val = (int) (p_progress * 100);

    if (l_val == 0 || l_val == 100) {
        m_prgStatusbar->hide();
    }
    else {
        m_prgStatusbar->show();
        m_prgStatusbar->setValue (l_val);
    }
}

void Main::on_actionDesktopControlOptions_triggered()
{
    Settings::displayPane ("dsktpcntrl");
    updateWindow();
}

void Main::on_actionOptions_triggered()
{
    Settings::displayPane ("gnrl");
    updateWindow();
}

void Main::on_actionAdaptModels_triggered()
{
    AdaptWizard* wiz = new AdaptWizard (this);
    wiz->exec();
    updateWindow();
}

void Main::on_actionStartTraining_triggered ()
{
    Session* session = SessionManager::pickSession();

    updateWindow();
    if (session && session->isValid() && !session->isCompleted()) {
        TrainingDialog::startTraining (session);
        setStatusMessage (tr ("Training session \"%1\"").arg (session->content()->title()) , 3000);
    }

    updateWindow();
}

/// @todo Allow configuration option to show specific notifications to prevent noise.
void Main::on_actionDesktopControlActive_triggered (bool p_checked)
{
    if (p_checked && Dictation::Agent::instance()->isActive())
        return;

    DesktopControl::Agent::instance()->setState (p_checked ? SpeechControl::AbstractAgent::Enabled : SpeechControl::AbstractAgent::Disabled);
    setStatusMessage ( (p_checked ? tr ("Desktop control activated.") : tr ("Desktop control deactivated.")) , 3000);
    updateWindow();
}

/// @todo Allow configuration option to show specific notifications to prevent noise.
void Main::on_actionDictationActive_triggered (const bool p_checked)
{
    if (p_checked && DesktopControl::Agent::instance()->isActive())
        return;

    Dictation::Agent::instance()->setState ( (p_checked) ? SpeechControl::AbstractAgent::Enabled : SpeechControl::AbstractAgent::Disabled);
    setStatusMessage ( ( (p_checked) ? tr ("Dictation activated.") : tr ("Dictation deactivated."))  , 3000);
    updateWindow();
}

void Main::updateWindow()
{
    updateUi();
    updateText();
}

void Main::on_actionAboutQt_triggered()
{
    QApplication::aboutQt();
}

void Main::on_actionAboutSpeechControl_triggered()
{
    AboutDialog l_dlg (this);
    l_dlg.exec();
}

void Main::on_actionPluginOptions_triggered()
{
    Settings::displayPane ("plgns");
    updateWindow();
}

void Main::on_actionTrainingOptions_triggered()
{
    Settings::displayPane ("trnng");
    updateWindow();
}

void Main::on_actionDictationOptions_triggered()
{
    Settings::displayPane ("dctn");
    updateWindow();
}

void Main::on_actionWizardMicrophone_triggered()
{
    MicrophoneSetup wiz (this);
    wiz.exec();
    updateWindow();
}

void Main::on_actionWizardContent_triggered()
{
    ContentWizard wiz (this);
    wiz.exec();
    updateWindow();
}

/// @todo Build the Voxforge Wizard.
void Main::on_actionWizardVoxForge_triggered()
{
}

void Main::on_actionWizardQuickStart_triggered()
{
    QuickStart* wiz = new QuickStart;
    wiz->exec();
    updateWindow();
}

void Main::on_actionReportBug_triggered()
{
    QProcess::startDetached ("x-www-browser", (QStringList() << "http://tasks.thesii.org/reporting-bugs"));
}

void Main::on_actionHelp_triggered()
{
    QProcess::startDetached ("x-www-browser", (QStringList() << "http://thesii.org/wiki/SpeechControl/UserGuides"));
}

void Main::on_actionWizardAdaption_triggered()
{
    AdaptWizard* wiz = new AdaptWizard (this);
    wiz->exec();
    updateWindow();
}

Main::~Main()
{
    delete m_ui;
}

#include "main-window.moc"
// kate: indent-mode cstyle; indent-width 4; replace-tabs on;
