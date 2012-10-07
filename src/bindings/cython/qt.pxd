cdef extern from "<QString>":
    cdef cppclass QString:
        QString()
        QString(QObject*)

cdef extern from "<QList>":
    cdef cppclass QList[T]:
        QList()

