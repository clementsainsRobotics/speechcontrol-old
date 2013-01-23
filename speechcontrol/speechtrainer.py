#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import sys
import argparse

import gi
gi.require_version('Gst', '0.10')
from gi.repository import Gst

from dbus.mainloop.qt import DBusQtMainLoop
from PyQt4 import QtDBus
from PyQt4.QtDBus import QDBusConnection
from PyQt4.QtGui import QApplication

from app import App


# parser.add_argument("--wsupport", action="store_true", help="enable Wintermute support")
parser = argparse.ArgumentParser()
parser.add_argument("-c", "--config", help="configuration file to use")
parser.add_argument("-a", "--asr", help="automatic speech recognition backend to use",
                    choices=["pocketsphinx"])
args = parser.parse_args()

DEFAULT_CONFIG = "/usr/share/speechcontrol/config/default.conf"
DEFAULT_ASR = "pocketsphinx"

# Try to load Wintermute support (Agent class, etc.)
# if WINTERMUTE_SUPPORT:
#       try:
#               from wintermute.members import Agent
#       except:
#               print("[I] Wintermute support not found.")
#               WINTERMUTE_SUPPORT = False
# else:
#       print("[I] Running as a standalone application.")


def read_configuration(file=DEFAULT_CONFIG):
        pass


def run():
    # Establish D-Bus
    # Instantiate every important class
    # Run!
    app = App(sys.argv)
    app.set_asr_backend(DEFAULT_ASR)

    DBusQtMainLoop(set_as_default=True)
    bus = QDBusConnection.sessionBus()

    sys.exit(app.exec_())

if __name__ == "__main__":
    read_configuration(args.config)

    # Overwrite config by command-line arguments
    if args.asr:
        DEFAULT_ASR = args.asr

    run()
