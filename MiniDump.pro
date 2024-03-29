QT += widgets

TEMPLATE = lib
DEFINES += MINIDUMP_LIBRARY

CONFIG += c++11

## 调试模式
#DEFINES += LIBRARY_UNEXPORT
contains(DEFINES, LIBRARY_UNEXPORT) {
    TEMPLATE = app
}

## 自定义变量
PROJECT_CATALOG_ROOT        = $$absolute_path($$PWD)
PROJECT_OUTPUT_CATALOG_ROOT = $$absolute_path($$OUT_PWD/..)

TARGET = MiniDump
DLLDESTDIR = $$PROJECT_OUTPUT_CATALOG_ROOT/bin/

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

## 引入外部资源
#include($$PWD/demo/demo.pri)

SOURCES += \
    $$PWD/MiniDump.cpp \
    $$PWD/main.cpp

HEADERS += \
    $$PWD/MiniDump.h \
    $$PWD/MiniDumpDefine.h \
    $$PWD/MiniDumpExport.h

DISTFILES +=


