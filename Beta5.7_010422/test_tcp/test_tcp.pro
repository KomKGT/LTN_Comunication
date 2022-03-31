!include( ../qmodbus.pri ) {
    error( "Couldn't find the qmodbus.pri file!" )
}



TARGET = test_tcp

FORMS += \
    device04_dialog.ui \
    feedrate_dialog.ui \
    start_dialog.ui

HEADERS += \
    device04_dialog.h \
    feedrate_dialog.h \
    feedrate_value.h \
    start_dialog.h \
    start_value.h

SOURCES += \
    device04_dialog.cpp \
    feedrate_dialog.cpp \
    feedrate_value.cpp \
    start_dialog.cpp \
    start_value.cpp

RESOURCES += \
    Icon.qrc

