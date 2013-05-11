import logging

cdef class PocketSphinx:
    cdef mic_recognizer_t *r
    cdef public bint decoderReady, audioReady

    def __cinit__(self):
        self.r = mic_recognizer_new()

    def __dealloc__(self):
        if self.audioReady:
            shutdown_audio(self.r)
        if self.decoderReady:
            shutdown_decoder(self.r)
        shutdown_recognizer(self.r)

    def __init__(self):
        self.decoderReady = False
        self.audioReady = False

    def initializeDecoder(self):
        print ("*** Initializing decoder")
        initialize_decoder(self.r)
        self.decoderReady = True

    def initializeAudio(self):
        print ("*** Initializing audio")
        initialize_audio(self.r)
        self.audioReady = True

    def shutdownAudio(self):
        if self.audioReady:
            print("*** Shutting down audio")
            shutdown_audio(self.r)

    def shutdownDecoder(self):
        if self.decoderReady:
            print("*** Shutting down decoder")
            shutdown_decoder(self.r)

    def recognizeFromMicrophone(self, sinkFile):
        logging.debug("*** Recognizing from microphone")
        bSinkFile = sinkFile.encode("ascii")

        if self.decoderReady and self.audioReady:
            recognize_from_microphone(self.r, bSinkFile)
        else:
            logging.warning("*** Decoder or audio device not ready")
