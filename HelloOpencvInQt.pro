#-------------------------------------------------
#
# Project created by QtCreator 2016-09-11T20:25:43
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HelloOpencvInQt
TEMPLATE = app

INCLUDEPATH += ./opencv/include \
               ./opencv/include\opencv \
               ./opencv/include\opencv2

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui
