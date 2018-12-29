# CGAL

INCLUDEPATH += $$CGAL_INCLUDE_DIR

LIBS += -L$${CGAL_LIB_DIR}
LIBS += -lCGAL \
        -lCGAL_Core \
        -lCGAL_ImageIO \
        -lCGAL_Qt5
