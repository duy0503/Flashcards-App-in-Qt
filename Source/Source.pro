#-------------------------------------------------
#
# Project created by QtCreator 2016-02-10T22:10:55
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Source
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    deck.cpp \
    flashcard.cpp \
    carddisplay.cpp

HEADERS  += mainwindow.h \
    deck.h \
    carddisplay.h \
    flashcard.h

FORMS    += mainwindow.ui \
    flashcard.ui

DISTFILES += \
    FlashcardForm.ui.qml \
    Flashcard.qml
