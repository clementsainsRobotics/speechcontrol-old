import sys
from time import sleep

def setup():
    sys.path.append("../")

def teardown():
    pass

def backend_test():
    from asr.backend import NativePocketSphinx
    b = NativePocketSphinx()
    sleep(10)

