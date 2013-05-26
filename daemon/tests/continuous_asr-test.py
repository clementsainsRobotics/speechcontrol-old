import sys
import time

from sys import argv
from PyQt4.QtCore import QCoreApplication

def setup():
    sys.path.append("../")

def teardown():
    pass

def continuous_recognition_test():
    from asr.backend import NativePocketSphinx

    app = QCoreApplication(argv)
    b = NativePocketSphinx()
    b.startContinuousRecognition()
    time.sleep(60)
    b.stopContinuousRecognition()

