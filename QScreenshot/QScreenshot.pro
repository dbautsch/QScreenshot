#-------------------------------------------------
#
# Project created by QtCreator 2016-05-24T11:36:35
#
#-------------------------------------------------

QT       += core gui


gcc:QMAKE_CXXFLAGS += -std=c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QScreenshot
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    AboutDialog.cpp \
    ScreenshotCreator.cpp \
    PictureInfoDialog.cpp \
    PicturePreviewWidget.cpp \
    SettingsDialog.cpp \
    CaptureRectDrawer.cpp \
    ScreenRectDialog.cpp

HEADERS  += MainWindow.h \
    AboutDialog.h \
    ScreenshotCreator.h \
    PictureInfoDialog.h \
    PicturePreviewWidget.h \
    SettingsDialog.h \
    CaptureRectDrawer.h \
    ScreenRectDialog.h \
    ImageUploader.h \
    ImageUploaders/ImageUploader.h \
    ImageUploaders/ImageUploadercpp

FORMS    += MainWindow.ui \
    AboutDialog.ui \
    PictureInfoDialog.ui \
    SettingsDialog.ui \
    ScreenRectDialog.ui

RESOURCES += \
    resources.qrc
