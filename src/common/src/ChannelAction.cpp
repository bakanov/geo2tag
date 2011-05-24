#include "ChannelAction.h"

qlonglong ChannelPrivileges::getId() const
{
  return DEFAULT_PRIVILEGES;
}


void ChannelPrivileges::setPrivileges(qlonglong user, qlonglong channel, int actions)
{
  m_data[QPair<qlonglong,qlonglong>(user,channel)] = actions;
}

/*bool ChannelPrivileges::isAllowed(qlonglong user, qlonglong channel, int actions)
{


    return false;
}*/
