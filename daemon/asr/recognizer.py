import logging
logger = logging.getLogger(__name__)

from PyQt4 import QtCore, QtDBus
from PyQt4.QtCore import pyqtSlot

from .backend import AsrBackend, NativePocketSphinx
from os import getenv

SC_SHARE_PATH = getenv('HOME') + '/.sii/share/speechcontrol'
DBUS_INTROSPECTION_XML = """
    <interface name="org.sii.speechcontrol.SpeechRecognition">
        <signal name="utteranceReady">
            <arg type="s" />
        </signal>
        <method name="oneUtterance">
            <arg name="hyp" type="s" direction="out" />
        </method>
        <method name="startContinuousRecognition">
        </method>
        <method name="stopContinuousRecognition">
        </method>
    </interface>
"""

class SpeechRecognizer(QtCore.QObject):
    def __init__(self):
        super().__init__()

        #TODO: Check availability of all backends and choose the default one
        #       using configuration defaults
        self.supportedBackends = [b for b in AsrBackend.__subclasses__() if b.supported()]
        if len(self.supportedBackends) == 0:
            raise RuntimeError("No speech recognition backends available!")
        self.backend = NativePocketSphinx() # self.config['defaultBackend']()
        self.uttid = 1

    def oneUtterance(self):
        self.backend.recognizeFromMicrophone(SC_SHARE_PATH + '/utts/hyp' + str(self.uttid))
        self.uttid += 1

    # TODO: Decide if this one is really necessary
    def oneUtteranceTo(self, receiver, method, errMethod):
        pass

    def startContinuousRecognition(self):
        self.backend.startContinuousRecognition()

    def stopContinuousRecognition(self):
        self.backend.stopContinuousRecognition()

    # TODO: Play with QTimer here
    def continuousRecognitionFor(self, time):
        pass

    def getUttid(self):
        return self.uttid

class RecognizerAdaptor(QtDBus.QDBusAbstractAdaptor):

    QtCore.Q_CLASSINFO("D-Bus Interface", "org.sii.speechcontrol.SpeechRecognition")
    QtCore.Q_CLASSINFO("D-Bus Introspection", DBUS_INTROSPECTION_XML)

    utteranceReady = QtCore.pyqtSignal(str)

    def __init__(self, parent):
        super().__init__(parent)
        parent.backend.recognizedToFile.connect(self.utteranceWritten)

    @pyqtSlot()
    def oneUtterance(self):
        logger.debug("One utterance requested")
        self.parent().oneUtterance()

    @pyqtSlot(str)
    def utteranceWritten(self, fileName):
        logger.debug("Utterance written to file " + fileName)
        with open(fileName) as f:
            uttid = f.readline().strip()
            hyp   = f.readline().strip()

            logger.debug("Recognized " + hyp)
            self.utteranceReady.emit(hyp)

