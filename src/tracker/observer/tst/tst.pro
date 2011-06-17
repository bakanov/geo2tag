include(../../../../config.pri)

INCLUDEPATH += \
               . \
               ../../../common/inc \
               ../../../maps/inc \
               ../../../json/inc \
               ../../ui/ \
               ../../../http_requests/inc \
               ../../../service/inc

HEADERS += tokenInObserver_test.h \
            ../../../http_requests/inc/LoginQuery.h \
            ../../../http_requests/inc/RSSFeedQuery.h \
            ../../../service/inc/DbSession.h \
            ../../../service/inc/TimeSlotInternal.h \
            ../../../service/inc/QueryExecutor.h \
           ../../../service/inc/UserInternal.h \
           ../../../service/inc/DataMarkInternal.h \
           ../../../service/inc/ChannelInternal.h \
           ../../../service/inc/UpdateThread.h
SOURCES += main.cpp \
           ../../../http_requests/src/LoginQuery.cpp \
           ../../../http_requests/src/RSSFeedQuery.cpp \
          ../../../service/src/DbSession.cpp \
          ../../../service/src/TimeSlotInternal.cpp \
          ../../../service/src/QueryExecutor.cpp \
          ../../../service/src/UserInternal.cpp \
          ../../../service/src/DataMarkInternal.cpp \
          ../../../service/src/ChannelInternal.cpp \
          ../../../service/src/UpdateThread.cpp \
    tokenInObserver_test.cpp

CONFIG   += qtestlib

TEMPLATE = app
QT += network
QT += sql
LIBS += -lmaps -lqjson -lcommon -lwikigpsHttp -lwikigpsJson -lpq -lfcgi
QT += testlib
#QMAKE_LFLAGS += -L../../../../lib
TARGET = test.suite
