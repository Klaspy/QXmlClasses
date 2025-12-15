QT = core

CONFIG += c++17
TARGET = Example

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

SOURCES += \
    main.cpp

RESOURCES += \
    example.qrc

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../lib/XmlClasses/lib/ -lXmlClasses
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../lib/XmlClasses/lib/ -lXmlClassesd
else:unix:!macx: LIBS += -L$$PWD/../lib/XmlClasses/lib/ -lXmlClasses

INCLUDEPATH += $$PWD/../lib/XmlClasses/include
DEPENDPATH += $$PWD/../lib/XmlClasses/include
