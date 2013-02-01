#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import sys
import argparse

import gi
gi.require_version('Gst', '0.10')
from gi.repository import Gst

from PyQt4 import QtCore, QtDBus
from PyQt4.QtDBus import QDBusConnection
from PyQt4.QtGui import QApplication

#from app import App
from speechcontrol.asr import SpeechControl


# parser.add_argument("--wsupport", action="store_true", help="enable Wintermute support")
parser = argparse.ArgumentParser()
parser.add_argument("-c", "--config", help="configuration file to use",
                    default="/usr/share/speechcontrol/config/default.conf")
parser.add_argument("-a", "--asr", help="automatic speech recognition backend to use",
                    choices=["pocketsphinx"], default="pocketsphinx")
args = parser.parse_args()

# Try to load Wintermute support (Agent class, etc.)
# if args.wntrsupport:
#       try:
#               from wintermute.members import Agent
#       except:
#               print("[I] Wintermute support not found.")
#               args.wntrsupport = False
# else:
#       print("[I] Running as a standalone application.")


def read_configuration(file):
        pass


def run():
    # Establish D-Bus
    # Instantiate every important class
    # Run!
    app = QApplication(sys.argv)

    sc = SpeechControl()
    sc.setAsrBackend(args.asr)

    sys.exit(app.exec_())

if __name__ == "__main__":
    read_configuration(args.config)
    run()

