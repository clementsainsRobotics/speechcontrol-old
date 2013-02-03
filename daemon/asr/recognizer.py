from PyQt4 import QtCore, QtDBus

from .backend import PocketSphinx

DBUS_INTROSPECTION_XML = """
  <interface name="org.sii.speechcontrol.recognition">
  </interface>
"""

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
    QtCore.Q_CLASSINFO("D-Bus Introspection", DBUS_INTROSPECTION_XML)

    def __init__(self, parent):
       super().__init__(parent)
