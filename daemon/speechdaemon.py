#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import sys
import os
import time
import atexit
import signal
import logging
import argparse

from PyQt4 import QtCore, QtDBus
from PyQt4.QtDBus import QDBusConnection

from asr.recognizer import SpeechRecognizer, RecognizerAdaptor

parser = argparse.ArgumentParser()
parser.add_argument('--loglevel',
    choices=["DEBUG", "INFO", "WARNING", "ERROR", "CRITICAL"],
    default="INFO",
    help='set logging level')

args = parser.parse_args()

def getLogLevel():
    if args.loglevel == "DEBUG":
        return logging.DEBUG
    elif args.loglevel == "INFO":
        return logging.INFO
    elif args.loglevel == "WARNING":
        return logging.WARNING
    elif args.loglevel == "ERROR":
        return logging.ERROR
    elif args.loglevel == "CRITICAL":
        return logging.CRITICAL
    return None

class Daemon:
    """A generic daemon class.

    Usage: subclass the Daemon class and override the run() method."""

    def __init__(self, pidfile):
        self.pidfile = pidfile

    def daemonize(self):
        """Deamonize class. UNIX double fork mechanism."""

        try:
            pid = os.fork()
            if pid > 0:
                # exit first parent
                sys.exit(0)
        except OSError as err:
            sys.stderr.write('fork #1 failed: {0}\n'.format(err))
            sys.exit(1)

        # decouple from parent environment
        os.chdir('/')
        os.setsid()
        os.umask(0)

        # do second fork
        try:
            pid = os.fork()
            if pid > 0:

                # exit from second parent
                sys.exit(0)
        except OSError as err:
            sys.stderr.write('fork #2 failed: {0}\n'.format(err))
            sys.exit(1)

        # redirect standard file descriptors
        sys.stdout.flush()
        sys.stderr.flush()
        si = open(os.devnull, 'r')
        so = open(os.devnull, 'a+')
        se = open(os.devnull, 'a+')

        os.dup2(si.fileno(), sys.stdin.fileno())
        os.dup2(so.fileno(), sys.stdout.fileno())
        os.dup2(se.fileno(), sys.stderr.fileno())

        # write pidfile
        atexit.register(self.delpid)

        pid = str(os.getpid())
        with open(self.pidfile, 'w+') as f:
            f.write(pid + '\n')

    def delpid(self):
        os.remove(self.pidfile)

    def start(self):
        """Start the daemon."""

        # Check for a pidfile to see if the daemon already runs
        try:
            with open(self.pidfile, 'r') as pf:

                pid = int(pf.read().strip())
        except IOError:
            pid = None

        if pid:
            message = "pidfile {0} already exist. " + \
                "Daemon already running?\n"
            sys.stderr.write(message.format(self.pidfile))
            sys.exit(1)

        # Start the daemon
        self.daemonize()
        self.run()

    def stop(self):
        """Stop the daemon."""

        # Get the pid from the pidfile
        try:
            with open(self.pidfile, 'r') as pf:
                pid = int(pf.read().strip())
        except IOError:
            pid = None

        if not pid:
            message = "pidfile {0} does not exist. " + \
                "Daemon not running?\n"
            sys.stderr.write(message.format(self.pidfile))
            return  # not an error in a restart

        # Try killing the daemon process
        try:
            while 1:
                os.kill(pid, signal.SIGTERM)
                time.sleep(0.1)
        except OSError as err:
            e = str(err.args)
            if e.find("No such process") > 0:
                if os.path.exists(self.pidfile):
                    os.remove(self.pidfile)
            else:
                print (str(err.args))
                sys.exit(1)

    def restart(self):
        """Restart the daemon."""
        self.stop()
        self.start()

    def run(self):
        """You should override this method when you subclass Daemon.

        It will be called after the process has been daemonized by
        start() or restart()."""

class SpeechDaemon(Daemon):
    def run(self):
        # Instantiate all classes, adaptors and register interfaces

        app = QtCore.QCoreApplication(sys.argv)
        logging.debug("QCoreApplication initialized")

        self.speechRecognizer = SpeechRecognizer()
        self.recogAdaptor = RecognizerAdaptor(self.speechRecognizer)

        connection = QtDBus.QDBusConnection.sessionBus()
        connection.registerObject("/SpeechRecognizer", self.speechRecognizer)
        connection.registerService("org.sii.speechcontrol")
        logging.info("D-Bus service established")

        logging.info("Entering Qt main loop")
        rc = app.exec_()

if __name__ == "__main__":
    logging.basicConfig(filename="/tmp/speechdaemon.log", level=getLogLevel())
    logging.info("SpeechDaemon starts up")

    daemon = SpeechDaemon("/tmp/speechdaemon.pid")
    daemon.start()
