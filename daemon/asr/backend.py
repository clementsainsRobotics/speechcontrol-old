import gi
gi.require_version('Gst', '1.0')

from gi.repository import GObject, Gst
GObject.threads_init()
Gst.init(None)

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

class NativePocketSphinx:
    def __init__(self):
        pass

"""
A wrapper backend supporting the choice of the two above ones.
Availability of each will depend on their state of implementation.

For now, the case is that GStreamer does not work for us becuase there is not
a PocketSphinx plug-in for the 1.0 version.
Alternative approach is being implemented based on using PocketSphinx Python
bindings. It should at least support singular utterance recognition using user's
microphone.
"""
class PocketSphinx:
    def __init__(self):
        pass