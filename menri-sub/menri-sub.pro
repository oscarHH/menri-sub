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
    editor/codeeditor.cpp \
    editor/highlighter.cpp \
    visor/PixmapWidget.cpp \
    visor/visor.cpp \
    visor/imageloader.cpp \
    visor/imagesmodel.cpp \
    visor/imagesview.cpp \
    herramientas/ManejoComprimido/manejozip.cpp \
    herramientas/ManejoComprimido/tipoarchivo.cpp \
    herramientas/ManejoComprimido/guizip.cpp \
    configuracion/configuraciones.cpp \
    editor/manejodearchivostxt.cpp \
    promocion/like.cpp \
    promocion/evento_qlabel.cpp



HEADERS  += mainwindow.h \
    editor/codeeditor.h \
    editor/highlighter.h \
    visor/PixmapWidget.h \
    visor/visor.h \
    visor/imageloader.h \
    visor/imagesmodel.h \
    visor/imagesview.h \
    herramientas/ManejoComprimido/manejozip.h \
    herramientas/ManejoComprimido/tipoarchivo.h \
    herramientas/ManejoComprimido/guizip.h \
    configuracion/configuraciones.h \
    editor/manejodearchivostxt.h \
    promocion/like.h \
    promocion/evento_qlabel.h


RESOURCES += \
    recursos.qrc

FORMS += \
    visor/visor.ui \
    herramientas/ManejoComprimido/guizip.ui \
    configuracion/configuraciones.ui \
    promocion/like.ui

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


