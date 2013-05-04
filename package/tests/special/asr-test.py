import sys
from time import sleep
from PyQt4 import QtCore
from PyQt4.QtCore import pyqtSlot, QObject, QCoreApplication

sys.path.append('../..')
from speechcontrol.recognition import AsrFacility

class Receiver(QObject):
    def __init__(self):
        super().__init__()
        self.utt = ""
        self.app = QCoreApplication(sys.argv)

        self.a = AsrFacility()
        self.a.addReceiver(self.callback)
        self.a.requestUtteranceAsync()

    @pyqtSlot(str)
    def callback(self, utt):
        print("*** Recognized text:", utt)
        self.utt = utt
        self.app.exit()

def asr_test():
    r = Receiver()

    return r.app.exec_()

asr_test()
