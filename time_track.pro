#-------------------------------------------------
#
# Project created by QtCreator 2019-06-30T18:04:26
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = time_track
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dbcreator.cpp \
    table.cpp

HEADERS  += mainwindow.h \
    dbcreator.h \
    table.h

FORMS    += mainwindow.ui

RESOURCES += \
    time_track.qrc
