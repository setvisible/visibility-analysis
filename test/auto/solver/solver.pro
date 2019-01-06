#isEmpty(TEMPLATE):TEMPLATE=app
TARGET       = tst_solver
CONFIG      += testcase
QT           = core testlib
SOURCES     += tst_solver.cpp

# Include:
INCLUDEPATH += ../../../include

# Resources:
include($$PWD/../../../VisibilityAnalysis_config.pri)
include($$PWD/../../../3rd/3rd.pri)

# Dependancies:
include( $$PWD/../../../src/core/core.pri )

