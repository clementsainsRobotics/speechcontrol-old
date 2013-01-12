from qt cimport *

cdef extern from "<lib/acousticmodel.hpp>" namespace "SpeechControl":
    cdef cppclass C_AcousticModel "SpeechControl::AcousticModel":
        void setParameter(QString, QVariant)
        void setParameters(QVariantMap)

        void mergeParameters(QVariantMap)

        QVariant parameter(QString)
        QMap[QString, QVariant] parameters()

        int sampleRate()

        QString path()

        bint isValid()
        bint isSystem()
        bint isUser()

        QString name()

        void load(QString)

        C_AcousticModel* clone()

cdef extern from "<lib/acousticmodel.hpp>" namespace "SpeechControl::AcousticModel":
    QList[C_AcousticModel] models()

cdef extern from "<lib/languagemodel.hpp>" namespace "SpeechControl":
    cdef cppclass C_LanguageModel "SpeechControl::LanguageModel":
        bint isSystem()
        bint isUser()

        QString name()

cdef extern from "<lib/languagemodel.hpp>" namespace "SpeechControl::LanguageModel":
    C_LanguageModel* fromDirectory(QDir)

cdef extern from "<lib/decoder.hpp>" namespace "SpeechControl":
    cdef cppclass C_Decoder "SpeechControl::Decoder":
        C_LanguageModel* languageModel()
        C_AcousticModel* acousticModel()

        void setLanguageModel(QString)
        void setLanguageModel(C_LanguageModel *)

        void setAcousticModel(QString)
        void setAcousticModel(C_AcousticModel *)

cdef extern from "<lib/dictionary.hpp>" namespace "SpeechControl":
    cdef cppclass C_Dictionary "SpeechControl::Dictionary":
        C_Dictionary(QString)

cdef extern from "<lib/dictionary.hpp>" namespace "SpeechControl::Dictionary":
    C_Dictionary* obtain(QString)
    C_Dictionary* obtainFromPath(QString)
    C_Dictionary* create(QList[QString], QString)

cdef extern from "<lib/noisedictionary.hpp>" namespace "SpeechControl":
    cdef cppclass C_NoiseDictionary "SpeechControl::NoiseDictionary":
        C_NoiseDictionary(QObject=*)

cdef extern from "<lib/noisedictionary.hpp>" namespace "SpeechControl::NoiseDictionary":
    C_NoiseDictionary* fromFile(QFile *)
