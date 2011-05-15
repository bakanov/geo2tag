#ifndef CHANNELACTION_H
#define CHANNELACTION_H

#include "QMultiMap"
#include "QMap"
#include "QPair"
#include "QSharedPointer"
#include "User.h"
#include "Channel.h"
#include "Actions.h"

class ChannelActions: public QObject
{
    Q_OBJECT

    qlonglong m_user;
    qlonglong m_channel;
    int m_action;

public:
    ChannelActions(qlonglong user, qlonglong channel, int action);

    //void setUser(qlonglong user);
    qlonglong getUser()const;

    //void setChannel(qlonglong channel);
    qlonglong getChannel()const;

    //void setAction(int action);
    int getAction()const;

    virtual ~ChannelActions();


};
typedef QMap< QPair<QSharedPointer<User>, QSharedPointer<Channel> >, QSharedPointer<Actions> > ChannelAccess;
//typedef QMap<QPair<user, channel>>action> ChannelAccess;
#endif // CHANNELACTION_H
