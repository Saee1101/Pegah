TEMPLATE = subdirs
# RC_ICONS=ICON.ico
SUBDIRS +=$$PWD/Entities \
          $$PWD/Connections \
          $$PWD/BusinessLogic \
          $$PWD/Presentation




QMAKE_CXXFLAGS += -std=gun++17

INCLUDEPATH   += "$$(HALCONROOT)/include"
INCLUDEPATH   += "$$(HALCONROOT)/include/halconcpp"

#libs
QMAKE_LIBDIR  += "$$(HALCONROOT)/lib/$$(HALCONARCH)"
unix:LIBS     += -lhalconcpp -lhalcon -lXext -lX11 -ldl -lpthread
win32:LIBS    += "$$(HALCONROOT)/lib/$$(HALCONARCH)/halconcpp.lib" \
                 "$$(HALCONROOT)/lib/$$(HALCONARCH)/halcon.lib"\
                 "$$(HALCONROOT)/lib/$$(HALCONARCH)/hdevenginecpp.lib"

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../preform_header_dll/build-preform_light-Desktop_Qt_5_14_0_MSVC2017_64bit-Release/release/ -lpreform_light
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../preform_header_dll/build-preform_light-Desktop_Qt_5_14_0_MSVC2017_64bit-Release/debug/ -lpreform_light

INCLUDEPATH += $$PWD/../../preform_header_dll/light
DEPENDPATH += $$PWD/../../preform_header_dll/light

