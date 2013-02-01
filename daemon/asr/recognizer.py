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

class RecognizerAdaptor(QtDBus.QDBusAbstractAdaptor):

	QtCore.Q_CLASSINFO("D-Bus Interface", "org.sii.speechcontrol.recognition")
    QtCore.Q_CLASSINFO("D-Bus Introspection", ''
            '  <interface name="org.sii.speechcontrol.recognition">\n'
            '  </interface>\n'
            '')

	def __init__(self, parent):
		super().__init__(parent)
