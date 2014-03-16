#-------------------------------------------------
#
# Project created by QtCreator 2013-07-02T22:42:55
#
#-------------------------------------------------

QT       += core gui widgets  webkit webkitwidgets network

CONFIG+=static

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = menri-sub
TEMPLATE = app
!win32: LIBS += -lz
win32 {
    # workaround for qdatetime.h macro bug
    DEFINES += NOMINMAX
}

SOURCES += main.cpp\
        mainwindow.cpp \
    codeeditor.cpp \
    highlighter.cpp \
    PixmapWidget.cpp \
    visor.cpp \
    imageloader.cpp \
    imagesmodel.cpp \
    imagesview.cpp \
    manejozip.cpp \
    tipoarchivo.cpp \
    guizip.cpp \
    configuraciones.cpp



HEADERS  += mainwindow.h \
    codeeditor.h \
    highlighter.h \
    PixmapWidget.h \
    visor.h \
    imageloader.h \
    imagesmodel.h \
    imagesview.h \
    manejozip.h \
    tipoarchivo.h \
    guizip.h \
    configuraciones.h


RESOURCES += \
    recursos.qrc

FORMS += \
    visor.ui \
    guizip.ui \
    configuraciones.ui

OTHER_FILES += \
    Menri-sub.txt

RC_FILE = iconos\app_icon.rc

OBJECTS_DIR = .obj
MOC_DIR = .moc

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../librerias/quazip/release/ -lquazip
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../librerias/quazip/debug/ -lquazip
else:unix: LIBS += -L$$OUT_PWD/../librerias/quazip/ -lquazip

INCLUDEPATH += $$PWD/../librerias/quazip
DEPENDPATH += $$PWD/../librerias/quazip
HEADERS +=


