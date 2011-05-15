#ifndef CHANNELACTION_H
#define CHANNELACTION_H

#include "User.h"

class ChannelActions: public QObject
{
    Q_OBJECT
    qlonglong m_user;
    qlonglong m_channel;
    int m_action;

public:
    ChannelActions(qlonglong user, qlonglong channel, int action);

    void setUser(qlonglong user);
    const qlonglong getUser()const;

    void setChannel(qlonglong channel);
    const qlonglong getChannel()const;

    void setAction(int action);
    const int getAction()const;

    virtual ~ChannelActions();


};

#endif // CHANNELACTION_H
