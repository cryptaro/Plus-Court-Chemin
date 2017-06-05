#-------------------------------------------------
#
# Project created by QtCreator 2017-05-13T22:52:12
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PlusCourtChemin
TEMPLATE = app

INCLUDEPATH += include/

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        src/ihm/mainwindow.cpp \
    src/topology/grid.cpp \
    src/ihm/gridview.cpp \
    src/topology/node.cpp \
    src/topology/priorityfile.cpp

HEADERS  += include/ihm/mainwindow.h \
    include/topology/grid.h \
    include/ihm/gridview.h \
    include/topology/node.h \
    include/topology/priorityfile.h

FORMS    += ui/mainwindow.ui \
