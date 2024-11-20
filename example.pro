QT = core

CONFIG += c++17

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

SOURCES += \
    XmlClasses/xmldocument.cpp \
    XmlClasses/xmlobject.cpp \
    XmlClasses/xmlprocessInstruction.cpp \
    XmlClasses/xmlvalue.cpp \
    main.cpp

HEADERS += \
    XmlClasses/xmldocument.h \
    XmlClasses/xmlobject.h \
    XmlClasses/xmlprocessInstruction.h \
    XmlClasses/xmlvalue.h

RESOURCES += \
    example.qrc
