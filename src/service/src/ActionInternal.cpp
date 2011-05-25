#include "ActionInternal.h"

DbAction::DbAction(qlonglong id,
int mask,
const QString &description):
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

DbAction::~DbAction()
{
}

