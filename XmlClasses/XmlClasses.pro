QT = core

CONFIG += c++17
TEMPLATE = lib
DEFINES += XML_CLASSES_LIBRARY

DESTDIR = $$PWD/lib/XmlClasses

CONFIG(debug, debug |release) {
    TARGET = XmlClassesd
}
else {
    TARGET = XmlClasses
}

# message($$PWD/xmldocument.h $$DESTDIR/)
QMAKE_POST_LINK += powershell -command "copy $$PWD/xmldocument.h $$DESTDIR/"           $$escape_expand(\\n\\t)
QMAKE_POST_LINK += powershell -command "copy $$PWD/xmlobject.h $$DESTDIR/"             $$escape_expand(\\n\\t)
QMAKE_POST_LINK += powershell -command "copy $$PWD/xmlprocessInstruction.h $$DESTDIR/" $$escape_expand(\\n\\t)
QMAKE_POST_LINK += powershell -command "copy $$PWD/xmlvalue.h $$DESTDIR/"              $$escape_expand(\\n\\t)

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

SOURCES += \
    xmldocument.cpp \
    xmlobject.cpp \
    xmlprocessInstruction.cpp \
    xmlvalue.cpp

HEADERS += \
    XmlClassesGlobal.h \
    xmldocument.h \
    xmlobject.h \
    xmlprocessInstruction.h \
    xmlvalue.h
