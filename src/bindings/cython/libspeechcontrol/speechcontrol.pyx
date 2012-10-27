cdef class AcousticModel:
    cdef C_AcousticModel *cSelf

    def __cinit__(self):
        self.cSelf = new C_AcousticModel()

    def __dealloc__(self):
        del self.cSelf

    def setParameter(self, char *name, char *value):
        self.cSelf.setParameter(QString(name), QVariant(value))

cdef class LanguageModel:
    cdef C_LanguageModel *cSelf

    def __cinit__(self):
        self.cSelf = new C_LanguageModel()

    def __dealloc__(self):
        del self.cSelf

cdef class Decoder:
    cdef C_Decoder *cSelf

    def __cinit__(self):
        self.cSelf = new C_Decoder()

    def __dealloc(self):
        del self.cSelf

    def setAcousticModel(self, char *path):
        self.cSelf.setAcousticModel(QString(path))

    def setLanguageModel(self, char *path):
        self.cSelf.setLanguageModel(QString(path))

    def setAcousticModel(self, AcousticModel model):
        self.cSelf.setAcousticModel(model.cSelf)

    def setLanguageModel(self, LanguageModel model):
        self.cSelf.setLanguageModel(model.cSelf)
