!include( ../qmodbus.pri ) {
    error( "Couldn't find the qmodbus.pri file!" )
}



TARGET = test_tcp

FORMS += \
    device04_dialog.ui

HEADERS += \
    device04_dialog.h

SOURCES += \
    device04_dialog.cpp

