QT = core

CONFIG += c++17
TEMPLATE = lib
DEFINES += XML_CLASSES_LIBRARY

DESTDIR = $$PWD/../lib/XmlClasses/lib

CONFIG(debug, debug |release) {
    TARGET = XmlClassesd
}
else {
    TARGET = XmlClasses
}

WINPWD = $$PWD
win32:WINPWD ~= s,/,\\,g
WININCLUDE = $$DESTDIR/../include
win32:WININCLUDE ~= s,/,\\,g

# message($$PWD/xmldocument.h $$DESTDIR/)
win32 {
QMAKE_POST_LINK += if not exist $$quote($$WINPWD\..\lib) $$QMAKE_MKDIR $$quote($$WINPWD\..\lib) $$escape_expand(\\n\\t)
QMAKE_POST_LINK += if not exist $$quote($$WINPWD\..\lib\XmlClasses) $$QMAKE_MKDIR $$quote($$WINPWD\..\lib\XmlClasses) $$escape_expand(\\n\\t)
QMAKE_POST_LINK += if not exist $$quote($$WINPWD\..\lib\XmlClasses\include) $$QMAKE_MKDIR $$quote($$WINPWD\..\lib\XmlClasses\include) $$escape_expand(\\n\\t)
QMAKE_POST_LINK += $$QMAKE_COPY $$quote($$WINPWD\xmldocument.h) $$quote($$WININCLUDE) $$escape_expand(\\n\\t)
QMAKE_POST_LINK += $$QMAKE_COPY $$quote($$WINPWD\xmlobject.h) $$quote($$WININCLUDE) $$escape_expand(\\n\\t)
QMAKE_POST_LINK += $$QMAKE_COPY $$quote($$WINPWD\xmlprocessInstruction.h) $$quote($$WININCLUDE) $$escape_expand(\\n\\t)
QMAKE_POST_LINK += $$QMAKE_COPY $$quote($$WINPWD\xmlvalue.h) $$quote($$WININCLUDE) $$escape_expand(\\n\\t)
QMAKE_POST_LINK += $$QMAKE_COPY $$quote($$WINPWD\XmlClasses) $$quote($$WININCLUDE) $$escape_expand(\\n\\t)
}
else {
QMAKE_POST_LINK += $$QMAKE_MKDIR $$quote($$WINPWD//..//lib) $$escape_expand(\\n\\t)
QMAKE_POST_LINK += $$QMAKE_MKDIR $$quote($$WINPWD/../lib/XmlClasses) $$escape_expand(\\n\\t)
QMAKE_POST_LINK += $$QMAKE_MKDIR $$quote($$WINPWD/../lib/XmlClasses/include) $$escape_expand(\\n\\t)
QMAKE_POST_LINK += $$QMAKE_COPY $$quote($$WINPWD/xmldocument.h) $$quote($$WININCLUDE) $$escape_expand(\\n\\t)
QMAKE_POST_LINK += $$QMAKE_COPY $$quote($$WINPWD/xmlobject.h) $$quote($$WININCLUDE) $$escape_expand(\\n\\t)
QMAKE_POST_LINK += $$QMAKE_COPY $$quote($$WINPWD/xmlprocessInstruction.h) $$quote($$WININCLUDE) $$escape_expand(\\n\\t)
QMAKE_POST_LINK += $$QMAKE_COPY $$quote($$WINPWD/xmlvalue.h) $$quote($$WININCLUDE) $$escape_expand(\\n\\t)
QMAKE_POST_LINK += $$QMAKE_COPY $$quote($$WINPWD/XmlClasses) $$quote($$WININCLUDE) $$escape_expand(\\n\\t)
}

message($$QMAKE_POST_LINK)

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
