#include "ChannelActionInternal.h"

DbChannelAction(qlonglong id,
  qlonglong user_id, qlonglong channel_id,
  int action):
m_id(id),
ChannelAction(user_id, channel_id, action)
{
}

qlonglong DbChannelAction::getId() const
{
    return m_id;
}

void DbChannelAction::setId(qlonglong id)
{
    m_id(id);
}

virtual DbChannelAction::~DbChannelAction();
