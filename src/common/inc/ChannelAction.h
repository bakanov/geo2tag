#ifndef CHANNELACTION_H
#define CHANNELACTION_H

#include "QMap"
#include "QPair"
#include "User.h"
#include "Channel.h"
#include "Action.h"

class ChannelAction: public QObject
{
    Q_OBJECT

    qlonglong m_user;
    qlonglong m_channel;
    int m_action;

public:
    ChannelAction(qlonglong user, qlonglong channel, int action);

    virtual qlonglong getId() const;

    //void setUser(qlonglong user);
    qlonglong getUser()const;

    //void setChannel(qlonglong channel);
    qlonglong getChannel()const;

    //void setAction(int action);
    int getAction()const;

    virtual ~ChannelAction();


};


//typedef QMap<QPair<User, Channel>, Action> ChannelActions;

#endif // CHANNELACTION_H
