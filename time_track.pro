#-------------------------------------------------
#
# Project created by QtCreator 2019-06-30T18:04:26
#
#-------------------------------------------------

QT       += core gui sql printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = time_track
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dbcreator.cpp \
    table.cpp \
    tableiomapper.cpp \
    viewcatalogform.cpp \
    qupdateableview.cpp \
    reportform.cpp

HEADERS  += mainwindow.h \
    dbcreator.h \
    table.h \
    tableiomapper.h \
    viewcatalogform.h \
    qupdateableview.h \
    reportform.h

FORMS    += mainwindow.ui \
    viewcatalogform.ui \
    reportform.ui

RESOURCES += \
    time_track.qrc
