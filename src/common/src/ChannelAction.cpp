#include "ChannelAction.h"

ChannelActions::ChannelActions(qlonglong user, qlonglong channel, int action):
        m_user(user),
        m_channel(channel),
        m_action(action)
{
}

void ChannelActions::setUser(qlonglong user)
{
    m_user(user);
}

qlonglong ChannelActions::getUser()const
{
    return m_user;
}

void ChannelActions::setChannel(qlonglong channel)
{
    m_channel(channel);
}

qlonglong ChannelActions::getChannel()const
{
    return m_channel;
}

void ChannelActions::setAction(int action)
{
    m_action(action);
}

int ChannelActions::getAction()const
{
    return action;
}

ChannelActions::~ChannelActions()
{
}

