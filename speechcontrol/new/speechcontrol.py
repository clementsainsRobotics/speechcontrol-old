#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys
import dbus
import argparse

from dbus.mainloop.qt import DBusQtMainLoop
from PyQt4.QtGui import QApplication


parser = argparse.ArgumentParser()
parser.add_argument("-c", "--config", help="configuration file to use")
# parser.add_argument("--wsupport", action="store_true", help="enable Wintermute support")
args = parser.parse_args()

# WINTERMUTE_SUPPORT = args.wsupport
DEFAULT_CONFIG="/usr/share/speechcontrol/config/default.conf"

# Try to load Wintermute support (Agent class, etc.)
# if WINTERMUTE_SUPPORT:
# 	try:
# 		from wintermute.members import Agent
# 	except:
# 		print("[I] Wintermute support not found.")
# 		WINTERMUTE_SUPPORT = False
# else:
# 	print("[I] Running as a standalone application.")

def read_configuration(file=DEFAULT_CONFIG):
	pass

def run():
	# Establish D-Bus
	# Instantiate every important class
	# Run!
	app = QApplication(sys.argv)
	DBusQtMainLoop(set_as_default=True)
	bus = dbus.SystemBus()
	sys.exit(app.exec_())

if __name__ == "__main__":
	read_configuration(args.config)

	run()