cdef extern from "<QObject>":
    cdef cppclass QObject:
        QObject()

cdef extern from "<QString>":
    cdef cppclass QString:
        QString()
        QString(QObject*)

        QString(unicode)

cdef extern from "<QList>":
    cdef cppclass QList[T]:
        QList()

cdef extern from "<QMap>":
    cdef cppclass QMap[K, V]:
        QMap()

cdef extern from "<QVariant>":
    cdef cppclass QVariant:
        QVariant(QString)

        QVariant(int)
        QVariant(bint)
        QVariant(unicode)

        QString toString()
        int     toInt()
        bint    toBool()

#typedef QVariantMap QMap[QString, QVariant]
