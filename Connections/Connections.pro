QT -= gui
QT += core serialport serialbus
TEMPLATE = lib
DEFINES += CONNECTIONS_LIBRARY

CONFIG += c++17 cmdline

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    inspection.cpp \
    Camera_Classes/available_cameras.cpp \
    Camera_Classes/camera_capture.cpp \
    Camera_Classes/camera_live.cpp \
    Camera_Classes/camera_parameter.cpp \
     Camera_Classes/zds_camera_parameter.cpp \
    Connections.cpp \
    Plc_Classes/acmotor.cpp \
    Plc_Classes/jack.cpp \
    Plc_Classes/plcdelta.cpp \
    Plc_Classes/plcmodbusconnect.cpp \
    Plc_Classes/plcmodbusrw.cpp \
    Plc_Classes/steppermotor.cpp \
    calibration.cpp \
    inspection.cpp \
    machine.cpp \
    machinemanager.cpp \
    machinesetting.cpp \
    setting.cpp \

HEADERS += \
    Camera_Classes/available_cameras.h \
    Camera_Classes/camera_capture.h \
    Camera_Classes/camera_live.h \
    Camera_Classes/camera_parameter.h \
    Camera_Classes/zds_camera_parameter.h \
    Connections_global.h \
    Connections.h \
    Plc_Classes/acmotor.h \
    Plc_Classes/jack.h \
    Plc_Classes/plcdelta.h \
    Plc_Classes/plcmodbusconnect.h \
    Plc_Classes/plcmodbusrw.h \
    Plc_Classes/steppermotor.h \
    calibration.h \
    inspection.h \
    machine.h \
    machinemanager.h \
    machinesetting.h \
    plcmodbusconnect.h \
    setting.h \

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target


INCLUDEPATH   += "$$(HALCONROOT)/include"
INCLUDEPATH   += "$$(HALCONROOT)/include/halconcpp"

#libs
QMAKE_LIBDIR  += "$$(HALCONROOT)/lib/$$(HALCONARCH)"
unix:LIBS     += -lhalconcpp -lhalcon -lXext -lX11 -ldl -lpthread
win32:LIBS    += "$$(HALCONROOT)/lib/$$(HALCONARCH)/halconcpp.lib" \
                 "$$(HALCONROOT)/lib/$$(HALCONARCH)/halcon.lib"\
                 "$$(HALCONROOT)/lib/$$(HALCONARCH)/hdevenginecpp.lib"






win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../pet_bottel/build-preform_light-Desktop_Qt_5_14_0_MSVC2017_64bit-Release/release/ -lpreform_light
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../pet_bottel/build-preform_light-Desktop_Qt_5_14_0_MSVC2017_64bit-Release/debug/ -lpreform_light

INCLUDEPATH += $$PWD/../../../pet_bottel/preform_light
DEPENDPATH += $$PWD/../../../pet_bottel/preform_light




win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../pet_bottel/build-preform_des_dll-Desktop_Qt_5_14_0_MSVC2017_64bit-Release/release/ -lpreform_des_dll
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../pet_bottel/build-preform_des_dll-Desktop_Qt_5_14_0_MSVC2017_64bit-Release/debug/ -lpreform_des_dll

INCLUDEPATH += $$PWD/../../../pet_bottel/preform_des_dll
DEPENDPATH += $$PWD/../../../pet_bottel/preform_des_dll
