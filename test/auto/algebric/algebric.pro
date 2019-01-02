#isEmpty(TEMPLATE):TEMPLATE=app
TARGET       = tst_algebric
CONFIG      += testcase
QT           = core testlib
SOURCES     += tst_algebric.cpp

# Include:
INCLUDEPATH += ../../../include

# Resources:
include($$PWD/../../../VisibilityAnalysis_config.pri)
include($$PWD/../../../3rd/3rd.pri)

