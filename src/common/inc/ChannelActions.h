#ifndef CHANNELACTIONS_H
#define CHANNELACTIONS_H


#include "ConcurrentVector.h"

class ChannelActions: public QObject
{
    Q_OBJECT
    qlonglong m_user;
    qlonglong m_channel;
    int m_access;


protected:
    ChannelActions(const qlonglong user, const qlonglong channel, const int access);

public:

    qlonglong getUser()const;
    qlonglong getChannel()const;
    int getAccess()const;

    void setUser(const qlonglong user);
    void setChannel(const qlonglong channel);
    void setAccess(const int access);


    virtual ~ChannelActions();




};
//typedef ConcurrentVector<ChannelActions>ChannelActions;



#endif // CHANNELACTIONS_H
