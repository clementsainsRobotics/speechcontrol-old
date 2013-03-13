import sys

def setup():
    sys.path.append("../")

def teardown():
    pass

def backend_test():
    from asr.backend import NativePocketSphinx
    b = NativePocketSphinx()

