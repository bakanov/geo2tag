#include "ChannelActions.h"


ChannelActions::ChannelActions(const qlonglong user, const qlonglong channel, const int access):
    m_user(user),
    m_channel(channel),
    m_access(access)
    {
    }



const qlonglong ChannelActions::getUserID()const
{
    return m_user;
}

const qlonglong ChannelActions::getChannelID()const
{
    return m_channel;
}

const int ChannelActions::getAccess()const
{
    return m_access;
}

void ChannelActions::setUserID(qlonglong user)
{
    m_user = user;
}

void ChannelActions::setChannelID(qlonglong channel)
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


