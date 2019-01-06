# GMP

INCLUDEPATH += $$GMP_INCLUDE_DIR

LIBS += -L$${GMP_LIB_DIR}
LIBS += -lgmp \
        -lgmpxx
