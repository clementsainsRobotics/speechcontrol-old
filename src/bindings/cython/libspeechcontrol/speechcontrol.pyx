from speechcontrol cimport *

cdef class AcousticModel:
    cdef C_AcousticModel *cSelf

    def __cinit__(self):
        self.cSelf = new C_AcousticModel()

    def __dealloc__(self):
        del self.cSelf

    def setParameter(self, name, value):
        self.cSelf.setParameter(QString(name), QVariant(value))
