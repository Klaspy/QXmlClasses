cmake_minimum_required(VERSION 3.16)

project(libXmlClasses LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

add_library(xmlclasses

    XmlClassesGlobal.h
    xmldocument.h           xmldocument.cpp
    xmlobject.h             xmlobject.cpp
    xmlprocessInstruction.h xmlprocessInstruction.cpp
    xmlvalue.h              xmlvalue.cpp
)

target_link_libraries(xmlclasses PRIVATE Qt${QT_VERSION_MAJOR}::Core)

target_compile_definitions(xmlclasses PRIVATE XML_CLASSES_LIBRARY)

target_include_directories(xmlclasses PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

include(GNUInstallDirs)
install(TARGETS xmlclasses
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
