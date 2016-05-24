#-------------------------------------------------
#
# Project created by QtCreator 2016-05-24T11:36:35
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QScreenshot
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    AboutDialog.cpp

HEADERS  += MainWindow.h \
    AboutDialog.h

FORMS    += MainWindow.ui \
    AboutDialog.ui

RESOURCES += \
    resources.qrc
