#include "ChannelActionsInternal.h"
#include "DbSession.h"
#include "DynamicCastFailure.h"
#include <syslog.h>




        DbChannelActions(qlonglong id,
                const qlonglong &user_id,
                const qlonglong &channel_id,
                const int &action):
        ChannelActions(user_id, channel_id, action), m_id(id)
        {
        }

        qlonglong DbChannelActions:: getId() const
        {
            return m_id;
        }

        void DbChannelActions:: setId(qlonglong id)
        {
            m_id = id;
        }

        DbChannelActions::~DbChannelActions()
        {
        }

