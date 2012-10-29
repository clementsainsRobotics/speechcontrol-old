from libcpp cimport string

cdef extern from "<QObject>":
    cdef cppclass QObject:
        QObject()

cdef extern from "<QString>":
    cdef cppclass QString:
        QString()

        QString(char *)
        QString(string)

cdef extern from "<QList>":
    cdef cppclass QList[T]:
        QList()

cdef extern from "<QMap>":
    cdef cppclass QMap[K, V]:
        QMap()

cdef extern from "<QVariant>":
    cdef cppclass QVariant:
        QVariant(int)
        QVariant(bint)
        QVariant(char *)

        int     toInt()
        bint    toBool()
        QString toString()

#typedef QVariantMap QMap[QString, QVariant]

cdef extern from "<QFile>":
    cdef cppclass QFile:
        QFile(QString)
