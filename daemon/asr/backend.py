import gi
gi.require_version('Gst', '0.10') # PocketSphinx has a plug-in for GStraemer 0.10 only - breakage is to be expected :/

from gi.repository import GObject, Gst
GObject.threads_init()
Gst.init(None)

class PocketSphinx:
    def __init__(self):
        self.pipeline = Gst.parse_launch('autoaudiosrc ! audioconvert ! audioresample '
                                         + '! vader name=vad auto-threshold=true '
                                         + '! pocketsphinx name=asr ! fakesink')
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
