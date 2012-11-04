project(SpeechControlDecoders)

option(WITH_DECODER_POCKETSPHINX  "Adds support for CMU's PocketSphinx in SpeechControl." OFF)
option(WITH_DECODER_GOOGLE_SPEECH "Adds support for Google's web speech recogntion platform in SpeechControl." OFF)
option(WITH_DECODER_JULIUS        "Adds support for the Julius decoder in SpeechControl.")