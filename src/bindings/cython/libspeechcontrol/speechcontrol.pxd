cdef extern from "<lib/acousticmodel.hpp>" namespace "SpeechControl":
    cdef cppclass C_AcousticModel:
        void setParameter(QString, QVariant)
        void setParameters(QVariantMap)

        void mergeParameters(QVariantMap)

        QVariant parameter(QString)
        QVariantMap parameters()

        int sampleRate()

        QString path()
        
        bint isValid()
        bint isSystem()
        bint isUser()

        QString name()

        void load(QString)

        C_AcousticModel* clone()

cdef extern from "<lib/acousticmodel.hpp>" namespace "SpeechControl::AcousticModel":
    QList<C_AcousticModel> models()
