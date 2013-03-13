# GStreamer imports
import gi
gi.require_version('Gst', '1.0')

from gi.repository import GObject, Gst
GObject.threads_init()
Gst.init(None)

# SpeechDaemon imports
import logging

from .pocketsphinx import PocketSphinx
from PyQt4 import QtCore

from PyQt4.QtCore import QObject

from os import getenv
# from sii import SC_SHARE_PATH, SC_CONFIG_PATH
SC_SHARE_PATH = getenv('HOME') + '/.sii/share/speechcontrol'
SC_CONFIG_PATH = getenv('HOME') + '/.sii/config/speechcontrol'

class GstPocketSphinx:
    def __init__(self):
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

    #Signals the state of support - currently not working
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
class NativePocketSphinx(QObject):
    recognizedToFile = QtCore.pyqtSignal(str)

    def __init__(self):
        super().__init__()

        logging.info("Initializing PocketSphinx backend")
        self.ps = PocketSphinx()
        logging.debug("Initializing PocketSphinx decoder")
        self.ps.initializeDecoder()
        logging.debug("Initializing audio recording")
        self.ps.initializeAudio()

    def recognizeFromMicrophone(self, sinkFileName):
        self.ps.recognizeFromMicrophone(sinkFileName)
        self.recognizedToFile.emit(sinkFileName)

    # This should return an iterator for n file names following some schema
    def fileNamesRange(self, n):
        pass

    #TODO: Write a solution for continuous recognition
    # Location of written files (and naming schema) should be governed by
    # a configuration manager
    # This will probably need a separate thread (QThread to be used)
    def startContinuousRecognition(self):
        logging.info("Starting continuous speech recognition")
        logging.warning("Implementation not ready")

        continuousSinkFileNameBase = SC_SHARE_PATH + '/contrecog/utts/hyp'
        # We don't want infinite loop so let's say 1000 utterances
        for i in range(1000):
            self.recognizeFromMicrophone(continuousSinkFileNameBase + str(i))

    def stopContinuousRecognition(self):
        pass

    @classmethod
    def supported():
        return True
