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
    AboutDialog.cpp \
    ScreenshotCreator.cpp \
    PictureInfoDialog.cpp

HEADERS  += MainWindow.h \
    AboutDialog.h \
    ScreenshotCreator.h \
    PictureInfoDialog.h

FORMS    += MainWindow.ui \
    AboutDialog.ui \
    PictureInfoDialog.ui

RESOURCES += \
    resources.qrc
