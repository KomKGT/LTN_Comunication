!include( ../qmodbus.pri ) {
    error( "Couldn't find the qmodbus.pri file!" )
}



TARGET = test_tcp

FORMS += \
    device04_dialog.ui \
    feedrate_dialog.ui

HEADERS += \
    device04_dialog.h \
    feedrate_dialog.h \
    feedrate_value.h

SOURCES += \
    device04_dialog.cpp \
    feedrate_dialog.cpp \
    feedrate_value.cpp

RESOURCES += \
    Icon.qrc

