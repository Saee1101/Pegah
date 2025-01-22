QT -= gui

TEMPLATE = lib
DEFINES += PREFORM_DES_DLL_LIBRARY

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    preform_des_dll.cpp\
        head_defect.cpp \
        oval_measurement.cpp \
        post_pro.cpp \
        pre_process.cpp \
        ring_defect.cpp \

HEADERS += \
    preform_des_dll_global.h \
    preform_des_dll.h\
    head_defect.h \
    oval_measurement.h \
    post_pro.h \
    pre_process.h \
    ring_defect.h \

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

  #includes
  INCLUDEPATH   += "$$(HALCONROOT)/include"
  INCLUDEPATH   += "$$(HALCONROOT)/include/halconcpp"

  #libs
  QMAKE_LIBDIR  += "$$(HALCONROOT)/lib/$$(HALCONARCH)"
  unix:LIBS     += -lhalconcpp -lhalcon -lXext -lX11 -ldl -lpthread
  win32:LIBS    += "$$(HALCONROOT)/lib/$$(HALCONARCH)/halconcpp.lib" \
                   "$$(HALCONROOT)/lib/$$(HALCONARCH)/halcon.lib"\
                   "$$(HALCONROOT)/lib/$$(HALCONARCH)/hdevenginecpp.lib"
