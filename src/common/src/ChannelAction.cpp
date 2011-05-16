#include "ChannelAction.h"

ChannelAction::ChannelAction(qlonglong user, qlonglong channel, int action):
        m_user(user),
        m_channel(channel),
        m_action(action)
{
}

qlonglong ChannelAction::getId() const
{
  // Database is not contain 0 in sequences, see scripts/base.sql
  return 0;
}

/*void ChannelAction::setUser(qlonglong user)
{
    m_user(user);
}*/

qlonglong ChannelAction::getUser()const
{
    return m_user;
}

/*void ChannelAction::setChannel(qlonglong channel)
{
    m_channel(channel);
}*/

qlonglong ChannelAction::getChannel()const
{
    return m_channel;
}

/*void ChannelAction::setAction(int action)
{
    m_action(action);
}*/

int ChannelAction::getAction()const
{
    return m_action;
}

ChannelAction::~ChannelAction()
{
}

