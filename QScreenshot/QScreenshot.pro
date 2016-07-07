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

LIBS += -lssl
LIBS += -lcrypto

# please uncomment this to enable some simple unit tests
#DEFINES += WANT_SOME_TESTS


SOURCES += main.cpp\
        MainWindow.cpp \
    AboutDialog.cpp \
    ScreenshotCreator.cpp \
    PictureInfoDialog.cpp \
    PicturePreviewWidget.cpp \
    SettingsDialog.cpp \
    CaptureRectDrawer.cpp \
    ScreenRectDialog.cpp \
    ImageUploaders/ImageUploader.cpp \
    SignInDialog.cpp \
    PasswordsManagerDialog.cpp \
    ImageUploaders/ImageShackUploader.cpp \
    PasswordsShelter.cpp \
    ImageUploaders/PostImageOrgUploader.cpp \
    SecretPassphraseDialog.cpp

HEADERS  += MainWindow.h \
    AboutDialog.h \
    ScreenshotCreator.h \
    PictureInfoDialog.h \
    PicturePreviewWidget.h \
    SettingsDialog.h \
    CaptureRectDrawer.h \
    ScreenRectDialog.h \
    ImageUploaders/ImageUploader.h \
    SignInDialog.h \
    PasswordsManagerDialog.h \
    ImageUploaders/ImageShackUploader.h \
    PasswordsShelter.h \
    ImageUploaders/PostImageOrgUploader.h \
    SecretPassphraseDialog.h

FORMS    += MainWindow.ui \
    AboutDialog.ui \
    PictureInfoDialog.ui \
    SettingsDialog.ui \
    ScreenRectDialog.ui \
    SignInDialog.ui \
    PasswordsManagerDialog.ui \
    SecretPassphraseDialog.ui

RESOURCES += \
    resources.qrc
