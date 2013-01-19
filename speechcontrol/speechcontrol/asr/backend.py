import pygst
pygst.require('0.10')
import gst

class PocketSphinx:
    def __init__(self):
        self.pipeline = gst.parse_launch('autoaudiosrc ! audioconvert ! audioresample '
                                         + '! vader name=vad auto-threshold=true '
                                         + '! pocketsphinx name=asr ! fakesink')
        asr = self.pipeline.get_by_name('asr')
        asr.connect('partial_result', self.partial_result)
        asr.connect('result', self.result)
        asr.set_property('configured', True)

        bus = self.pipeline.get_bus()
        bus.add_signal_watch()
        bus.connect('message::application', self.application_message)

        self.pipeline.set_state(gst.STATE_PAUSED)

    def partial_result(self):
        pass

    def result(self):
        pass

    def application_message(self):
        pass
