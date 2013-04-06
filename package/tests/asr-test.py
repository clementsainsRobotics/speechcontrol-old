import sys

def setup():
    sys.path.append('..')

def asr_test():
    from speechcontrol.recognition import AsrFacility
    a = AsrFacility()
    print("*** Listening for one utterance")
    utt = a.requestUtterance()
    print("*** Recognized text:", utt)

    assert(utt != "")
