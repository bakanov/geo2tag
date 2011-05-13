#ifndef CHANNELACTIONSINTERNAL_H
#define CHANNELACTIONSINTERNAL_H

#include "ChannelActions.h"

    class DbChannelActions: public ChannelActions
    {
        qlonglong m_id;

    public:
        DbChannelActions(qlonglong id,
                const qlonglong &user_id,
                const qlonglong &channel_id,
                const int &action);

        qlonglong getId() const;

        void setId(qlonglong id);

        virtual ~DbChannelActions();
    };

#endif // CHANNELACTIONSINTERNAL_H
