from abc import ABCMeta, abstractmethod
# GStreamer imports
import gi
gi.require_version('Gst', '1.0')

from gi.repository import GObject, Gst
GObject.threads_init()
Gst.init(None)

# SpeechDaemon imports
import logging
logger = logging.getLogger(__name__)

from .pocketsphinx import PocketSphinx
from PyQt4 import QtCore

from PyQt4.QtCore import QObject, QThread, pyqtSlot

from os import getenv
#TODO: create global SII Python module containing information about our projects
# from sii import SC_SHARE_PATH, SC_CONFIG_PATH
SC_SHARE_PATH = getenv('HOME') + '/.sii/share/speechcontrol'
SC_CONFIG_PATH = getenv('HOME') + '/.sii/config/speechcontrol'

class RecognitionBackend(QObject, metaclass=ABCMeta):
    def __init__(self):
        super().__init__()

    @abstractmethod
    def recognizeFromMicrophone(self, sinkFileName):
        raise NotImplementedError("You should use a real backend")

    #TODO: Implement automatic way of checking if a particular backend is usable
    #       on a given system
    @classmethod
    @abstractmethod
    def supported():
        return False

class GstPocketSphinx(RecognitionBackend):
    def __init__(self):
        super().__init__()

        self.pipeline = Gst.parse_launch('autoaudiosrc ! audioconvert ! audioresample '
                                         + '! vader name=vad auto-threshold=true '
                                         + '! pocketsphinx name=asr ! fakesink') # pocketsphinx element is failing
        asr = self.pipeline.get_by_name('asr')
        asr.connect('partial_result', self.partial_result)
        asr.connect('result', self.result)
        asr.set_property('configured', True)

        bus = self.pipeline.get_bus()
        bus.add_signal_watch()
        bus.connect('message::application', self.application_message)

        self.pipeline.set_state(Gst.State.PAUSED)

    def partial_result(self):
        pass

    def result(self):
        pass

    def application_message(self):
        pass

    @classmethod
    def supported():
        return False

"""
For now, the case is that GStreamer does not work for us becuase there is not
a PocketSphinx plug-in for the 1.0 version.
Alternative approach is being implemented based on using PocketSphinx Python
bindings. It should at least support singular utterance recognition using user's
microphone.
"""
class NativePocketSphinx(RecognitionBackend):
    recognizedToFile = QtCore.pyqtSignal(str)

    def __init__(self):
        super().__init__()

        logger.info("Initializing PocketSphinx backend")
        self.ps = PocketSphinx()
        logger.debug("Initializing PocketSphinx decoder")
        self.ps.initializeDecoder()
        logger.debug("Initializing audio recording")
        self.ps.initializeAudio()

        self.contWorker = ContinuousAsrWorker()
        self.workerThread = QThread(self)
        self.workerThread.started.connect(self.contWorker.start)
        self.workerThread.finished.connect(self.contWorker.deleteLater)
        self.contWorker.moveToThread(self.workerThread)

    def recognizeFromMicrophone(self, sinkFileName):
        self.ps.recognizeFromMicrophone(sinkFileName)
        self.recognizedToFile.emit(sinkFileName)

    # This returns an iterator for n file names following some naming schema
    def fileNamesRange(self, n, stem="hyp"):
        for i in range(1, n+1):
            yield stem + str(i)

    #TODO: Write a solution for continuous recognition
    # Location of written files (and naming schema) should be governed by
    # a configuration manager
    # This will probably need a separate thread (QThread to be used)
    # FIXME: We should probably shut down the main PS instance to avoid conflicts
    # between it and the worker
    def startContinuousRecognition(self):
        logger.info("Starting continuous speech recognition")
        self.workerThread.start()

    def stopContinuousRecognition(self):
        logger.info("Stopping continuous speech recognition")
        self.workerThread.quit()

    @classmethod
    def supported():
        return True

"""
This class is meant to be used along with QThread to implement asynchronous,
continuous automatic speech recognition.
Used by NativePocketSphinx.
#FIXME: Not entirely working - fails to save the result to a file
"""
class ContinuousAsrWorker(QObject):
    def __init__(self):
        super().__init__()
        self.ps = None
        self.finish = False

    @pyqtSlot()
    def start(self):
        logger.debug("Continuous ASR worker starts")

        logger.info("Initializing PocketSphinx backend")
        self.ps = PocketSphinx()
        logger.debug("Initializing PocketSphinx decoder")
        self.ps.initializeDecoder()
        logger.debug("Initializing audio recording")
        self.ps.initializeAudio()

        continuousSinkFileNameBase = SC_SHARE_PATH + '/contrecog/utts/hyp'
        i = 1
        while not self.finish:
            self.ps.recognizeFromMicrophone(continuousSinkFileNameBase + str(i))
            i += 1
