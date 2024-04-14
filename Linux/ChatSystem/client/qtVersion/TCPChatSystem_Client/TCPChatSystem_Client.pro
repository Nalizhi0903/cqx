QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    chatdialog.cpp \
    chatmsg.cpp \
    json/json_reader.cpp \
    json/json_value.cpp \
    json/json_writer.cpp \
    main.cpp \
    msgqueue.cpp \
    mythread.cpp \
    registerdialog.cpp \
    tcpsvr.cpp \
    widget.cpp

HEADERS += \
    chatdialog.h \
    chatmsg.h \
    json/allocator.h \
    json/assertions.h \
    json/config.h \
    json/forwards.h \
    json/json.h \
    json/json_features.h \
    json/json_tool.h \
    json/json_valueiterator.inl \
    json/reader.h \
    json/value.h \
    json/version.h \
    json/writer.h \
    msgqueue.h \
    mythread.h \
    registerdialog.h \
    tcpsvr.h \
    widget.h

FORMS += \
    chatdialog.ui \
    registerdialog.ui \
    widget.ui

TRANSLATIONS += \
    TCPChatSystem_Client_zh_CN.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \ \
    json/CMakeLists.txt

