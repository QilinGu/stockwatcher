#-------------------------------------------------
#
# Project created by QtCreator 2016-05-16T18:21:35
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = stockwatcher
TEMPLATE = app


SOURCES += main.cpp\
        login.cpp \
    mainwindow.cpp \
    articlewidget.cpp \
    stockwidget.cpp \
    intakewidget.cpp \
    outputwidget.cpp

HEADERS  += login.h \
    mainwindow.h \
    articlewidget.h \
    stockwidget.h \
    intakewidget.h \
    outputwidget.h

FORMS    += \
    mainwindow.ui \
    login.ui

RESOURCES += \
    resources.qrc
