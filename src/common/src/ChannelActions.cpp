#include "ChannelActions.h"


ChannelActions::ChannelActions(const qlonglong user, const qlonglong channel, const int access):
    m_user(user),
    m_channel(channel),
    m_access(access)
    {
    }



qlonglong ChannelActions::getUser()const
{
    return m_user;
}

qlonglong ChannelActions::getChannel()const
{
    return m_channel;
}

int ChannelActions::getAccess()const
{
    return m_access;
}

void ChannelActions::setUser(qlonglong user)
{
    m_user = user;
}

void ChannelActions::setChannel(qlonglong channel)
{
    m_channel = channel;
}

void ChannelActions::setAccess(int access)
{
    m_access = access;
}



ChannelActions::~ChannelActions()
{

}


