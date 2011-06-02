
TEMPLATE = app
TARGET = test.suite 
DEPENDPATH += .
INCLUDEPATH += . ../inc/ \
    ../../common/inc/ \
    ../../json/inc/

# Input
HEADERS += TestsForTimeSlotAndSession.h\
    ../inc/TimeSlotInternal.h \
    ../inc/QueryExecutor.h \
    ../inc/DbSession.h \
    ../../common/inc/DataMarks.h \
    ../../common/inc/DataChannel.h \
    ../../common/inc/ConcurrentVector.h \
    ../../common/inc/Channel.h \
    ../../common/inc/Session.h \
    ../../json/inc/UnsubscribeChannelResponse.h \
    ../../json/inc/UnsubscribeChannelRequestJSON.h \
    ../../json/inc/SubscribedChannelsResponseJSON.h \
    ../../json/inc/SubscribedChannelsRequestJSON.h \
    ../../json/inc/SubscribeChannelResponseJSON.h \
    ../../json/inc/SubscribeChannelJSON.h \
    ../../json/inc/SetTimeSlotResponseJSON.h \
    ../../json/inc/SetTimeSlotRequestJSON.h \
    ../../json/inc/SetTimeSlotMarkResponseJSON.h \
    ../../json/inc/SetTimeSlotMarkRequestJSON.h \
    ../../json/inc/SetDefaultTimeSlotResponseJSON.h \
    ../../json/inc/SetDefaultTimeSlotRequestJSON.h \
    ../../json/inc/SetDefaultTimeSlotMarkResponseJSON.h \
    ../../json/inc/SetDefaultTimeSlotMarkRequestJSON.h \
    ../../json/inc/RSSFeedRequestJSON.h \
    ../../json/inc/RSSFeedJSON.h \
    ../../json/inc/RSSFeedSessionRequestJSON.h \
    ../../json/inc/RSSFeedSessionResponseJSON.h \
    ../../json/inc/LoginResponseJSON.h \
    ../../json/inc/LoginRequestJSON.h \
    ../../json/inc/JsonUser.h \
    ../../json/inc/JsonTimeSlot.h \
    ../../json/inc/JsonSerializer.h \
    ../../json/inc/JsonDataMark.h \
    ../../json/inc/JsonChannel.h \
    ../../json/inc/JsonSession.h \
    ../../json/inc/GetTimeSlotResponseJSON.h \
    ../../json/inc/GetTimeSlotRequestJSON.h \
    ../../json/inc/GetTimeSlotMarkResponseJSON.h \
    ../../json/inc/GetTimeSlotMarkRequestJSON.h \
    ../../json/inc/DefaultResponseJSON.h \
    ../../json/inc/ChannelListJSON.h \
    ../../json/inc/AddUserResponseJSON.h \
    ../../json/inc/AddUserRequestJSON.h \
    ../../json/inc/AddNewMarkResponseJSON.h \
    ../../json/inc/AddNewMarkRequestJSON.h \
    ../../json/inc/AddChannelResponseJSON.h \
    ../../json/inc/AddChannelRequestJSON.h \
    ../../json/inc/GetSessionPointRequestJSON.h \
    ../../json/inc/GetSessionPointResponseJSON.h \
    ../../json/inc/SetSessionPointRequestJSON.h \
    ../../json/inc/SetSessionPointResponseJSON.h \
    ../../json/inc/SetDefaultSessionPointRequestJSON.h \
    ../../json/inc/SetDefaultSessionPointResponseJSON.h \
    ../../common/inc/User.h \
    ../../common/inc/TimeSlot.h \
    ../inc/UserInternal.h \
    ../inc/UpdateThread.h \
    ../inc/DataMarkInternal.h \
    ../inc/ChannelInternal.h

SOURCES += main.cpp \
    ../src/TimeSlotInternal.cpp \
    ../src/QueryExecutor.cpp \
    ../src/DbSession.cpp \
    ../../common/src/TimeSlot.cpp \
    ../../common/src/User.cpp \
    ../../common/src/defines.cpp \
    ../../common/src/DataMarks.cpp \
    ../../common/src/Channel.cpp \
    ../../common/src/Session.cpp \
    ../src/UserInternal.cpp \
    ../src/DataMarkInternal.cpp \
    ../src/ChannelInternal.cpp \
    ../src/UpdateThread.cpp \
    ../../json/src/JsonSerializer.cpp \
    ../../json/src/LoginResponseJSON.cpp \
    ../../json/src/LoginRequestJSON.cpp \
    ../../json/src/JsonUser.cpp \
    ../../json/src/JsonTimeSlot.cpp \
    ../../json/src/JsonDataMark.cpp \
    ../../json/src/JsonChannel.cpp \
    ../../json/src/JsonSession.cpp \
    ../../json/src/GetTimeSlotResponseJSON.cpp \
    ../../json/src/GetTimeSlotRequestJSON.cpp \
    ../../json/src/GetTimeSlotMarkResponseJSON.cpp \
    ../../json/src/GetTimeSlotMarkRequestJSON.cpp \
    ../../json/src/DefaultResponseJSON.cpp \
    ../../json/src/ChannelListJSON.cpp \
    ../../json/src/AddNewMarkResponseJSON.cpp \
    ../../json/src/AddNewMarkRequestJSON.cpp \
    ../../json/src/AddChannelRequestJSON.cpp \
    ../../json/src/SubscribedChannelsRequestJSON.cpp \
    ../../json/src/SubscribeChannelJSON.cpp \
    ../../json/src/SetTimeSlotRequestJSON.cpp \
    ../../json/src/SetTimeSlotMarkRequestJSON.cpp \
    ../../json/src/GetSessionPointRequestJSON.cpp \
    ../../json/src/GetSessionPointResponseJSON.cpp \
    ../../json/src/SetSessionPointRequestJSON.cpp \
    ../../json/src/RSSFeedRequestJSON.cpp \
    ../../json/src/RSSFeedJSON.cpp \
    TestsForTimeSlotAndSession.cpp

QT += testlib
QT += sql
LIBS += -lqjson
