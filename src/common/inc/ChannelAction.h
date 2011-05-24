#ifndef CHANNELACTION_H
#define CHANNELACTION_H

#include "QMap"
#include "QPair"
#include "ConcurrentVector.h"

class ChannelPrivileges: public QObject
{
  Q_OBJECT

    QMap<QPair<qlonglong,qlonglong>,int> m_data;

  public:
    static const qlonglong DEFAULT_PRIVILEGES = 0;

    virtual qlonglong getId() const;

    void setPrivileges(qlonglong user, qlonglong channel, int actions);

    bool isAllowed(qlonglong user, qlonglong channel, int actions);

};

typedef ConcurrentVector<ChannelPrivileges> ChannelActions;
#endif                                  // CHANNELACTION_H
