cdef class AcousticModel:
    cdef C_AcousticModel *cSelf

    def __cinit__(self):
        self.cSelf = new C_AcousticModel()

    def __dealloc__(self):
        del self.cSelf

    def setParameter(self, char *name, char *value):
        self.cSelf.setParameter(QString(name), QVariant(value))
