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

#    @staticmethod
#    def fromDirectory(char *path):
#        cdef C_LanguageModel *newModel
        #newModel = fromDirectory(QDir(QString(path))) <<< This line crashes Cython o.O
#        wrapper = LanguageModel()

#        del wrapper.cSelf # A little bit ugly but should work.
#        wrapper.cSelf = newModel
#        return wrapper

cdef class Dictionary:
    cdef C_Dictionary *cSelf

    def __cinit__(self):
        self.cSelf = new C_Dictionary(QString("")) # Probably not correct, it must be
                                                   # investigated.

    def __dealloc__(self):
        del self.cSelf

    @staticmethod
    def obtain(char *_id): # 'id' is reserved
        cdef C_Dictionary *newDict
        newDict = obtain(QString(_id))
        wrapper = Dictionary()

        del wrapper.cSelf # A little bit ugly but should work.
        wrapper.cSelf = newDict
        return wrapper

    @staticmethod
    def obtainFromPath(char *path):
        cdef C_Dictionary *newDict
        newDict = obtainFromPath(QString(path))
        wrapper = Dictionary()

        del wrapper.cSelf # A little bit ugly but should work.
        wrapper.cSelf = newDict
        return wrapper

#cdef class NoiseDictionary:
#    cdef C_NoiseDictionary *cSelf
#
#    def __cinit__(self):
#        self.cSelf = new C_NoiseDictionary()
#
#    def __dealloc__(self):
#        del self.cSelf

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
