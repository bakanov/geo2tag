#ifndef CHANNELACTION_H
#define CHANNELACTION_H

#include "QMap"
#include "QPair"
#include "ConcurrentVector.h"


class ChannelAction: public QObject
{
    Q_OBJECT

    qlonglong m_user;
    qlonglong m_channel;
    int m_action;

public:
    ChannelAction(qlonglong user, qlonglong channel, int action);

    virtual qlonglong getId() const;

    void setUser(qlonglong user);
    qlonglong getUser()const;

    void setChannel(qlonglong channel);
    qlonglong getChannel()const;

    void setAction(int action);
    int getAction()const;

    virtual ~ChannelAction();


};
typedef ConcurrentVector<QMap<QPair<qlonglong,qlonglong>,int> > ChannelActions;




#endif // CHANNELACTION_H
