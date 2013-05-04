from PyQt4 import QtCore, QtDBus
from PyQt4.QtDBus import QDBusMessage, QDBusConnection

DBUS_SERVICE = "org.sii.speechcontrol"
DBUS_OBJECT_PATH = "/SpeechRecognizer"
DBUS_INTERFACE = "org.sii.speechcontrol.SpeechRecognition"

class AsrFacility(QtCore.QObject):
    def __init__(self):
        super().__init__()
        self.recogIface = QtDBus.QDBusInterface(DBUS_SERVICE, DBUS_OBJECT_PATH,
            DBUS_INTERFACE, QtDBus.QDBusConnection.sessionBus(), self)

    def requestUtterance(self):
        """Request one utterance from SpeechControl

            [UNIMPLEMENTED] This call is a blocking one, use it if you need the text immediately.
        """
        self.recogIface.call("oneUtterance")
        raise NotImplementedError
        return ""

    def requestUtteranceAsync(self):
        """Request one utterance from SpeechControl

            This call is asynchronous, to use it one has to connect the interface's signal
            'utteranceReady' to a slot responsible for handling the text.
        """
        self.recogIface.asyncCall("oneUtterance")

    def addReceiver(self, recv):
        """Add a callback to receive any further recognized utterances

            Note: you may need to make the callback a proper Qt slot by using
            pyqtSlot decorator.
        """
        self.recogIface.connection().connect(DBUS_SERVICE,
                                             DBUS_OBJECT_PATH,
                                             DBUS_INTERFACE,
                                             "utteranceReady",
                                             recv)
