GOOGLETEST_DIR = source/google
include(gtest_dependency.pri)

TEMPLATE = app
QT = core widgets
CONFIG += console c++14
CONFIG -= app_bundle
DEFINES += UNIT_TEST

INCLUDEPATH += \
    source \
    source/google \
    ../linguist_executor/source \

SOURCES += \
    ../linguist_executor/source/proparser.cpp \
    source/printto.cpp \
    source/tst_proparser.cpp \

HEADERS += \
   ../linguist_executor/source/proparser.h \
   source/printto.h
