QT       += core gui sql network
QT += charts serialport serialbus printsupport
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
DEFINES +=QT_DEPRECATED_WARNINGS
RC_ICONS=ICON.ico
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
QXLSX_PARENTPATH=./         # current QXlsx path is . (. means curret directory)
QXLSX_HEADERPATH=./header/  # current QXlsx header path is ./header/
QXLSX_SOURCEPATH=./source/  # current QXlsx source path is ./source/
include(./QXlsx.pri)
SOURCES += \
    APIController.cpp \
    MainWindow.cpp \
    ShamciToMiladi.cpp \
    ShamsiDateEdit.cpp \
    debuggerclass.cpp \
    gallery.cpp \
    halconqtwindow.cpp \
    halconqtwindow.cpp \
    main.cpp \
    newplotclass.cpp \
    pieview.cpp \
    qcustomplot.cpp

HEADERS += \
    APIController.h \
    MainWindow.h \
    ShamciToMiladi.h \
    ShamsiDateEdit.h \
    debuggerclass.h \
    gallery.h \
    halconqtwindow.h \
    halconqtwindow.h \
    newplotclass.h \
    pieview.h \
    qcustomplot.h

FORMS += \
    MainWindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build/BusinessLogic/release/ -lBusinessLogic
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build/BusinessLogic/debug/ -lBusinessLogic
INCLUDEPATH += $$PWD/../BusinessLogic
DEPENDPATH += $$PWD/../BusinessLogic

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build/Connections/release/ -lConnections
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build/Connections/debug/ -lConnections

INCLUDEPATH += $$PWD/../Connections
DEPENDPATH += $$PWD/../Connections


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

RESOURCES += \
    Images.qrc

DISTFILES += \
    Tivanex - App Ui - Preform/Bg/Bg.png \
    Tivanex - App Ui - Preform/New SET-01.svg \
    Tivanex - App Ui - Preform/Thumbs.db \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 1-1 Login popup/Admin.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 1-1 Login popup/Group 187.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 1-1 Login popup/Group 268.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 1-1 Login popup/Group 269.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 1-1 Login popup/Group 440.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 1-1 Login popup/Group 441.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 1-1 Login popup/Layer 1.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 1-1 Login popup/Lock.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 1-1 Login popup/Password_.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 1-1 Login popup/Rectangle 198.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 1-1 Login popup/Rectangle 199.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 1-1 Login popup/Rectangle 333.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 1-1 Login popup/User.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 1-1 Login popup/Username_.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 1-1 Login popup/secure1450111.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 1-1 Power/Group 387-1.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 1-1 Power/Group 387.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 1-1 Power/Group 488.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 1-1 Power/Group 488.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 1-1 Power/Group 489.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 1-1 Power/Group 489.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 1-1 Power/Shot down.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 1-1 Power/reset.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 1-1 edited/Danger.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 1-1 edited/Group 168.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 1-1 edited/Group 187-1.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 1-1 edited/Group 187.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 1-1 edited/Group 188-1.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 1-1 edited/Group 188.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 1-1 edited/Group 299.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 1-1 edited/Group 316.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 1-1 edited/Group 323.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 1-1 edited/Group 324.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 1-1 edited/Group 379.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 1-1 edited/Group 380.png \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 1-1 edited/Group 380.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 1-1 edited/Group 381.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 1-1 edited/Group 382.png \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 1-1 edited/Group 382.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 1-1 edited/Group 384.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 1-1 edited/Group 385.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 1-1 edited/Group 386.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 1-1 edited/Group 387.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 1-1 edited/Group 388.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 1-1 edited/Group 389.png \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 1-1 edited/Group 389.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 1-1 edited/Group 390.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 1-1 edited/Group 434.png \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 1-1 edited/Group 435.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 1-1 edited/Help.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 1-1 edited/Manitor.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 1-1 edited/Rectangle 58.png \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 1-1 edited/Setting.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 1-1 edited/Settings.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 1-1 edited/Squircle.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 1-1 edited/Statistic.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 1-1 edited/Vector 212.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 1-1 edited/Vector 44.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 1-2/00.00-1.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 1-2/00.00.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 1-2/Group 188.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 1-2/Group 192.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 1-2/Group 218.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 1-2/Group 224.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 1-2/Group 386.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 1-2/Group 387.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 1-2/Group 388.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 1-2/Up-1.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 1-2/Up-2.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 1-2/Up-3.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 1-2/Up.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 1-3/Camera_.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 1-3/Divider_.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 1-3/Exposuer_.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 1-3/Focus_.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 1-3/Group 188.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 1-3/Group 386.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 1-3/Group 387.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 1-3/Group 388.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 1-3/OFF-1.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 1-3/OFF-2.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 1-3/OFF-3.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 1-3/OFF-4.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 1-3/OFF-5.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 1-3/OFF-6.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 1-3/OFF.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 1-3/PLC_.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 1-3/Reverse out round.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 1-3/Subtract-1.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 1-3/Subtract.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 1-3/UPS_.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 1-3/Vector 207.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 1-3/Vector 208.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 1-3/Vector 209.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 1-3/Vector 210.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 1-3/Vector 211.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 1-3/White indicator_.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 1-3/feed jack_.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-1/00.00-1.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-1/00.00-2.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-1/00.00.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-1/Delay.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-1/Feed Jack.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-1/Group 168.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-1/Group 192-1.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-1/Group 192-2.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-1/Group 192.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-1/Group 219-1.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-1/Group 219.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-1/Group 220-1.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-1/Group 220.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-1/Group 222.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-1/Group 353.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-1/Group 389.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-1/Group 390.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-1/Group 391.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-1/Group 392.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-1/Group 393.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-1/Group 394.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-1/Group 395.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-1/Group 396.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-1/Layer 1.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-1/Manitor.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-1/Rectangle 190.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-1/Rectangle 192.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-1/Rectangle 194.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-1/Rectangle 195.png \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-1/Rectangle 195.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-1/Rectangle 333.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-1/Rectangle 64.png \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-1/Rectangle 64.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-1/Reject Jack.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-1/Reverse.png \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-1/Reverse.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-1/Setting.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-1/Settings.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-1/Speed.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-1/Star wheel setting.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-1/Statistic.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-1/Time.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-1/Union.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-1/Up-1.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-1/Up-2.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-1/Up-3.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-1/Up-4.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-1/Up-5.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-1/Up.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-1/Vector 213.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-2-1/Camera Preview.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-2-1/Gallery.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-2-1/Group 340.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-2-1/Group 341.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-2-1/Group 342.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-2-1/Group 343.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-2-1/Group 344.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-2-1/Group 345.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-2-1/Group 347.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-2-1/Group 348.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-2-1/Group 397.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-2-1/Group 398.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-2-1/Group 399.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-2-1/Group 400.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-2-1/Group 401.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-2-1/Group 402.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-2-1/Group 403.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-2-1/Image-1.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-2-1/Image-2.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-2-1/Image-3.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-2-1/Image-4.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-2-1/Image-5.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-2-1/Image-6.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-2-1/Image-7.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-2-1/Image.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-2-1/Layer 1.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-2-1/Rectangle 197.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-2-1/Rectangle 206.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-2-1/Rectangle 207.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-2-1/Rectangle 208.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-2-1/Sample Image.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-2-1/Vector 199.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-2-1/Vector 200.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-2-1/Vector 207.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-2-1/Vector 208.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-2-1/Vector 209.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-2-1/Vector 210.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-2-1/Vector 211.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-2-1/White indicator_.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-2-2/Group 192.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-2-2/Group 404.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-2-2/Group 405.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-2-2/Group 406.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-2-2/Group 407.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-2-2/Group 408.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-2-2/Group 409.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-2-2/Rectangle 200.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-2-2/Squircle-1.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-2-2/Squircle.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-2-2/Up.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-2-2/Vector 199.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-2-2/Vector 206.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-3/Tivanex - App Ui 04 - Page 2-3/00.00-1.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-3/Tivanex - App Ui 04 - Page 2-3/00.00-2.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-3/Tivanex - App Ui 04 - Page 2-3/00.00-3.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-3/Tivanex - App Ui 04 - Page 2-3/00.00.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-3/Tivanex - App Ui 04 - Page 2-3/Group 192-1.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-3/Tivanex - App Ui 04 - Page 2-3/Group 192.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-3/Tivanex - App Ui 04 - Page 2-3/Group 266.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-3/Tivanex - App Ui 04 - Page 2-3/Group 267.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-3/Tivanex - App Ui 04 - Page 2-3/Group 355.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-3/Tivanex - App Ui 04 - Page 2-3/Group 359.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-3/Tivanex - App Ui 04 - Page 2-3/Group 367-1.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-3/Tivanex - App Ui 04 - Page 2-3/Group 367-2.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-3/Tivanex - App Ui 04 - Page 2-3/Group 367.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-3/Tivanex - App Ui 04 - Page 2-3/Group 368-1.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-3/Tivanex - App Ui 04 - Page 2-3/Group 368.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-3/Tivanex - App Ui 04 - Page 2-3/Group 374.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-3/Tivanex - App Ui 04 - Page 2-3/Group 410.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-3/Tivanex - App Ui 04 - Page 2-3/Group 411.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-3/Tivanex - App Ui 04 - Page 2-3/Group 412.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-3/Tivanex - App Ui 04 - Page 2-3/Group 413.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-3/Tivanex - App Ui 04 - Page 2-3/Head defect_.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-3/Tivanex - App Ui 04 - Page 2-3/Layer 1.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-3/Tivanex - App Ui 04 - Page 2-3/OFF-1.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-3/Tivanex - App Ui 04 - Page 2-3/OFF-2.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-3/Tivanex - App Ui 04 - Page 2-3/OFF-3.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-3/Tivanex - App Ui 04 - Page 2-3/OFF.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-3/Tivanex - App Ui 04 - Page 2-3/ON-1.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-3/Tivanex - App Ui 04 - Page 2-3/ON-2.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-3/Tivanex - App Ui 04 - Page 2-3/ON-3.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-3/Tivanex - App Ui 04 - Page 2-3/ON.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-3/Tivanex - App Ui 04 - Page 2-3/Oval Max_.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-3/Tivanex - App Ui 04 - Page 2-3/Oval Min_.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-3/Tivanex - App Ui 04 - Page 2-3/Rectangle 334-1.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-3/Tivanex - App Ui 04 - Page 2-3/Rectangle 334.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-3/Tivanex - App Ui 04 - Page 2-3/Ringdefect_.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-3/Tivanex - App Ui 04 - Page 2-3/Up-1.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-3/Tivanex - App Ui 04 - Page 2-3/Up-2.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-3/Tivanex - App Ui 04 - Page 2-3/Up-3.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-3/Tivanex - App Ui 04 - Page 2-3/Up-4.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-3/Tivanex - App Ui 04 - Page 2-3/Up-5.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-3/Tivanex - App Ui 04 - Page 2-3/Up-6.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-3/Tivanex - App Ui 04 - Page 2-3/Up-7.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-3/Tivanex - App Ui 04 - Page 2-3/Up.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-4/Access level.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-4/Admin-1.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-4/Admin.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-4/Change Password.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-4/Group 267.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-4/Group 268-1.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-4/Group 268.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-4/Group 269-1.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-4/Group 269.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-4/Group 275.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-4/Group 292.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-4/Group 293.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-4/Group 414.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-4/Group 415.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-4/Group 416.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-4/Group 417.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-4/Group 418.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-4/Group 419.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-4/Group 420.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-4/Group 421.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-4/Layer 1.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-4/Lock-1.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-4/Lock.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-4/New user.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-4/Password_-1.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-4/Password_.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-4/Rectangle 197.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-4/Rectangle 198.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-4/Rectangle 64.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-4/User-1.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-4/User.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-4/Username.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-4/ValidationPassword_-1.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-4/ValidationPassword_.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-4/secure145011.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-4/secure1450111-2.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-4/secure1450111111.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-4/secure145011111111-3.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 3/2000-1.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 3/2000.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 3/From_.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 3/Group 168.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 3/Group 187.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 3/Group 268.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 3/Group 269.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 3/Group 299.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 3/Group 353.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 3/Group 424.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 3/Group 425.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 3/Image-1.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 3/Image-2.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 3/Image-3.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 3/Image-4.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 3/Image-5.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 3/Image-6.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 3/Image.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 3/Manitor.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 3/Rectangle 64.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 3/Reject Images.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 3/Setting.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 3/Settings.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 3/Statistic.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 3/To_.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 3/Union.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 3/Up-1.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 3/Up-2.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 3/Up-3.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 3/Up.svg \
    Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 3/Vector 213.svg
