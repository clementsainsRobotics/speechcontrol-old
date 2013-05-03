import sys

_utt = ""

def setup():
    sys.path.append('..')

def callback(utt):
    print("*** Recognized text:", utt)
    _utt = utt

def asr_test():
    from speechcontrol.recognition import AsrFacility
    a = AsrFacility()
    a.addReceiver(callback)

    print("*** Listening for one utterance")

    assert(_utt != "")
