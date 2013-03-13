cdef extern from "continuous.h":
    ctypedef struct mic_recognizer_t

cdef extern from "continuous.c":
    mic_recognizer_t* mic_recognizer_new()

    mic_recognizer_t* initialize_decoder(mic_recognizer_t *)
    mic_recognizer_t* initialize_audio(mic_recognizer_t *)

    void recognize_from_microphone(mic_recognizer_t *, char *)

    void shutdown_audio(mic_recognizer_t *)
    void shutdown_decoder(mic_recognizer_t *)
    void shutdown_recognizer(mic_recognizer_t *)

