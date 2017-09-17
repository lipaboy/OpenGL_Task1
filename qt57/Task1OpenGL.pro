QT += core
QT -= gui

CONFIG += c++11

TARGET = qt57
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++11 -lglut -lGL -lGEW -lGLU
LIBS += -lglut -lGL -lGLEW -lGLU

SOURCES += \
    ../Sources/main.cpp \
    ../Sources/task1/funcs.cpp

HEADERS += \
    ../Sources/task1/task1.h
