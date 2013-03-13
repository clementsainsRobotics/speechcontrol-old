import sys

def setup():
    sys.path.append("../")

def teardown():
    pass

def recognizer_test():
    from asr.recognizer import SpeechRecognizer
    recog = SpeechRecognizer()
    recog.oneUtterance()
