#include "ActionInternal.h"

DbAction::DbAction(qlonglong id,
  int mask,
  QString &name):
Action(mask, name), m_id(id)
{
}

qlonglong DbAction::getId() const
{
    return m_id;
}

void DbAction::setId(qlonglong id)
{
    m_id(id);
}

virtual DbAction::~DbAction()
{
}
