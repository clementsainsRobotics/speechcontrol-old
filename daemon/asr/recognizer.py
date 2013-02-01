import gi
gi.require_version('Gst', '0.10') # PocketSphinx has a plug-in for GStraemer 0.10 only - breakage is to be expected :/

from gi.repository import Gst
from PyQt4 import QtCore, QtDBus

from .backend import PocketSphinx

class SpeechRecognizer(QtCore.QObject):
    def __init__(self):
        super().__init__()
        self.backend = PocketSphinx()

    def oneUtterance(self):
        pass

    def oneUtteranceTo(self, receiver, method, errMethod):
        pass

