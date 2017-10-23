greaterThan(QT_MAJOR_VERSION, 5)

QT += core gui widgets
CONFIG += c++14

TARGET = qt_reader
TEMPLATE = app

SOURCES += \
    main.cpp \
    wizard.cpp \
    reader.cpp

HEADERS += \
    wizard.h \
    reader.h

FORMS +=
