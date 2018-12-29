#-------------------------------------------------
# Project created by QtCreator
#-------------------------------------------------
TEMPLATE = app
TARGET   = editor
QT      += core gui
QT      += xml
QT      += opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG  += no_keyword

# QT += c++11
QMAKE_CXXFLAGS += -std=c++11

lessThan(QT_VERSION, 5.0) {
    warning("prefere to build it with Qt 5.0")
}

#-------------------------------------------------
# DEFINES
#-------------------------------------------------
DEFINES += WITH_SELECTION_PROCESSING


#-------------------------------------------------
# DEPENDENCIES
#-------------------------------------------------
include($$PWD/../3rd/3rd.pri)


#-------------------------------------------------
# VERSION
#-------------------------------------------------
VERSION_FILENAME = $$PWD/../version

!exists( $${VERSION_FILENAME} ) {
    error( "Cannot find version file \"$${VERSION_FILENAME}\"" )
}

APP_VERSION = "$$cat($$VERSION_FILENAME)"
DEFINES += APP_VERSION=\\\"$$APP_VERSION\\\"


#-------------------------------------------------
# INCLUDE
#-------------------------------------------------
INCLUDEPATH += $$PWD/../include/


#-------------------------------------------------
# SOURCES
#-------------------------------------------------
include($$PWD/widgets/widgets.pri)

HEADERS += \
    $$PWD/builddefs.h \
    $$PWD/globals.h \
    $$PWD/version.h

SOURCES += \
    $$PWD/main.cpp


#-------------------------------------------------
# RESOURCES
#-------------------------------------------------
RESOURCES += $$PWD/resources.qrc

win32|unix {
    RC_FILE += $$PWD/resources_win.rc
}


#-------------------------------------------------
# BUILD OPTIONS
#-------------------------------------------------

# Rem: On Ubuntu, directories starting with '.' are hidden by default
win32{
    MOC_DIR =      ./.moc
    OBJECTS_DIR =  ./.obj
    UI_DIR =       ./.ui
}else{
    MOC_DIR =      ./_moc
    OBJECTS_DIR =  ./_obj
    UI_DIR =       ./_ui
}

#-------------------------------------------------
# OUTPUT
#-------------------------------------------------
DESTDIR = $${OUT_PWD}/../visibility_install


#-------------------------------------------------
# INSTALL
#-------------------------------------------------
# instructions for 'make install'
unix {
    target.path = /usr/lib
    INSTALLS += target
}

