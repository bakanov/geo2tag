#include "ActionInternal.h"

#if 0
DbAction::DbAction(qlonglong id,
int mask,
QString &description):
Action(mask, description), m_id(id)
{
}


qlonglong DbAction::getId() const
{
  return m_id;
}


void DbAction::setId(qlonglong id)
{
  m_id = id;
}


virtual DbAction::~DbAction()
{
}
#endif
