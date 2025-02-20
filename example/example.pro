QT = core

CONFIG += c++17

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

SOURCES += \
    main.cpp

RESOURCES += \
    example.qrc

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../XmlClasses/lib/XmlClasses/ -lXmlClasses
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../XmlClasses/lib/XmlClasses/ -lXmlClassesd
else:unix:!macx: LIBS += -L$$PWD/../XmlClasses/ -lXmlClasses

INCLUDEPATH += $$PWD/../XmlClasses
DEPENDPATH += $$PWD/../XmlClasses
