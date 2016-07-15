#-------------------------------------------------
#
# Project created by QtCreator 2016-03-14T01:18:33
#
#-------------------------------------------------

QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = SpinalCord
TEMPLATE = app


SOURCES += main.cpp\
        spinalcord.cpp \
        qcustomplot.cpp

HEADERS  += spinalcord.h \
            qcustomplot.h

FORMS    += spinalcord.ui
