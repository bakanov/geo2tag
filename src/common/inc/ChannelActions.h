#ifndef CHANNELACTIONS_H
#define CHANNELACTIONS_H


#include "ConcurrentVector.h"

class ChannelActions: public QObject
{
    Q_OBJECT
    qlonglong m_user;
    qlonglong m_channel;
    int m_access;// ? bool 1-subscribe, 0-unsubscribe


protected:
    ChannelActions(const qlonglong, const qlonglong, const int);

public:

    //virtual qlonglong getId() const = 0;

    const qlonglong getUserID()const;
    const qlonglong getChannelID()const;
    const int getAccess()const;

    void setUserID(qlonglong user);
    void setChannelID(qlonglong channel);
    void setAccess(int access);


    virtual ~ChannelActions();




};
typedef ConcurrentVector<ChannelActions>ChannelActions;



#endif // CHANNELACTIONS_H
