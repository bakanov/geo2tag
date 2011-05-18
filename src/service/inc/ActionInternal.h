#ifndef ACTIONINTERNAL_H
#define ACTIONINTERNAL_H

#include "Action.h"

class DbAction:public Action
{
    qlonglong m_id;

    public:
      DbAction(qlonglong id,
        int mask,
        QString &name);

      qlonglong getId() const;

      void setId(qlonglong id);

      virtual ~DbAction();

}

#endif // ACTIONINTERNAL_H
