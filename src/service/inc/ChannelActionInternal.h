#ifndef CHANNELACTIONINTERNAL_H
#define CHANNELACTIONINTERNAL_H


#include "ChannelAction.h"

class DbChannelAction:public ChannelAction
{
    qlonglong m_id;

    public:
      DbChannelAction(qlonglong id,
        qlonglong user_id, qlonglong channel_id,
        int action);

      qlonglong getId() const;

      void setId(qlonglong id);

      virtual ~DbChannelAction();

};


#endif // CHANNELACTIONINTERNAL_H
