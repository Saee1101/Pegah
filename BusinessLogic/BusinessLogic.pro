QT += core sql serialport serialbus
QT -= gui

TEMPLATE = lib
DEFINES += BUSINESSLOGIC_LIBRARY

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    # ../Connections/Connections.cpp \
    BusinessLogic.cpp



HEADERS += \
    # ../Connections/Connections.h \
    BusinessLogic_global.h \
    BusinessLogic.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build/Entities/release/ -lEntities
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build/Entities/debug/ -lEntities

INCLUDEPATH += $$PWD/../Entities
DEPENDPATH += $$PWD/../Entities

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build/Connections/release/ -lConnections
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build/Connections/debug/ -lConnections

INCLUDEPATH += $$PWD/../Connections
DEPENDPATH += $$PWD/../Connections
# win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../AI/preform_des_dll/build-preform_des_dll-Desktop_Qt_5_14_0_MSVC2017_64bit-Release/release/ -lpreform_des_dll
# else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../AI/preform_des_dll/build-preform_des_dll-Desktop_Qt_5_14_0_MSVC2017_64bit-Release/debug/ -lpreform_des_dll

# INCLUDEPATH += $$PWD/../AI/preform_des_dll/preform_des_dll
# DEPENDPATH += $$PWD/../AI/preform_des_dll/preform_des_dll

# win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../AI/preform_light_1/build-preform_light-Desktop_Qt_5_14_0_MSVC2017_64bit-Release/release/ -lpreform_light
# else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../AI/preform_light_1/build-preform_light-Desktop_Qt_5_14_0_MSVC2017_64bit-Release/debug/ -lpreform_light

# INCLUDEPATH += $$PWD/../AI/preform_light_1/preform_light
# DEPENDPATH += $$PWD/../AI/preform_light_1/preform_light


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
