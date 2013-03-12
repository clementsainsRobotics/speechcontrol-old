from PyQt4 import QtCore, QtDBus
from PyQt4.QtCore import pyqtSlot

from .backend import NativePocketSphinx

DBUS_INTROSPECTION_XML = """
  <interface name="org.sii.speechcontrol.recognition">
  </interface>
"""

class SpeechRecognizer(QtCore.QObject):
    def __init__(self):
        super().__init__()
        self.backend = NativePocketSphinx()
        self.backend.recognizedToFile.connect(self.utteranceReady)
        self.uttid = 1

    def oneUtterance(self):
        self.backend.recognizeFromMicrophone(SC_SHARE_PATH + '/utts/hyp' + str(self.uttid))

    def oneUtteranceTo(self, receiver, method, errMethod):
        pass

    def startContinuousRecognition(self):
        pass

    def stopContinuousRecognition(self):
        pass

    def continuousRecognitionFor(self, time):
        pass

    # This should open the file with recognized speech and do any needed postprocessing.
    # It is preferable to implement everything such that a client gets a string
    # through D-Bus and does not n need to open any files.
    @pyqtSlot(str)
    def utteranceReady(self, sinkFileName):
        pass

class RecognizerAdaptor(QtDBus.QDBusAbstractAdaptor):

    QtCore.Q_CLASSINFO("D-Bus Interface", "org.sii.speechcontrol.recognition")
    QtCore.Q_CLASSINFO("D-Bus Introspection", DBUS_INTROSPECTION_XML)

    def __init__(self, parent):
       super().__init__(parent)
