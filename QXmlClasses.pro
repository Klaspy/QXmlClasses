QT = core

CONFIG += c++17

TEMPLATE = subdirs
SUBDIRS += \
    XmlClasses \
    example

example.depends = XmlClasses

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
