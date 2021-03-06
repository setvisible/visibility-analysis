#-------------------------------------------------
# Project created by QtCreator
#-------------------------------------------------
TEMPLATE = app
TARGET   = editor
QT      += core gui

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


#-------------------------------------------------
# DEPENDENCIES
#-------------------------------------------------
include($$PWD/../VisibilityAnalysis_config.pri)
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
include($$PWD/core/core.pri)
include($$PWD/dialogs/dialogs.pri)
include($$PWD/utils/utils.pri)
include($$PWD/widgets/widgets.pri)

HEADERS += \
    $$PWD/about.h \
    $$PWD/builddefs.h \
    $$PWD/globals.h \
    $$PWD/mainwindow.h \
    $$PWD/version.h

SOURCES += \
    $$PWD/mainwindow.cpp \
    $$PWD/main.cpp


FORMS += \
    $$PWD/mainwindow.ui


#-------------------------------------------------
# RESOURCES
#-------------------------------------------------
RESOURCES += $$PWD/resources.qrc
RESOURCES += $$PWD/examples/examples.qrc

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
# Remark:
# =======
# Eventually, in your favorite IDE, replace build chain command
#   'make'
# by
#   'make install'
#
# It will install the DLLs, documentation, data, etc.
# that are required to execute the application.
#

# instructions for 'make install'

# install Qt binaries (for Windows only)
# This is a hack for 'windeployqt'
win32{
    CONFIG(debug,debug|release){
        libs_qt_to_copy.files += $$[QT_INSTALL_PLUGINS]/platforms/qminimald.dll
        libs_qt_to_copy.files += $$[QT_INSTALL_PLUGINS]/platforms/qwindowsd.dll
        libs_qt_to_copy.path = $${DESTDIR}/platforms
        INSTALLS += libs_qt_to_copy
    }else{
        libs_qt_to_copy.files += $$[QT_INSTALL_PLUGINS]/platforms/qminimal.dll
        libs_qt_to_copy.files += $$[QT_INSTALL_PLUGINS]/platforms/qwindows.dll
        libs_qt_to_copy.path = $${DESTDIR}/platforms
        INSTALLS += libs_qt_to_copy
    }
}

# install BOOST binaries
libs_boost_to_copy.files += $${Boost_BIN_DIR}/libboost_thread-mgw53-mt-1_61.dll
libs_boost_to_copy.files += $${Boost_BIN_DIR}/libboost_system-mgw53-mt-1_61.dll
libs_boost_to_copy.path = $${DESTDIR}
INSTALLS += libs_boost_to_copy

# install CGAL binaries
libs_cgal_to_copy.files += $${CGAL_BIN_DIR}/*.dll
libs_cgal_to_copy.path = $${DESTDIR}
INSTALLS += libs_cgal_to_copy

# install GMP binaries
libs_gmp_to_copy.files += $${GMP_BIN_DIR}/*.dll
libs_gmp_to_copy.path = $${DESTDIR}
INSTALLS += libs_gmp_to_copy

# install MPFR binaries
libs_mpfr_to_copy.files += $${MPFR_BIN_DIR}/*.dll
libs_mpfr_to_copy.path = $${DESTDIR}
INSTALLS += libs_mpfr_to_copy

