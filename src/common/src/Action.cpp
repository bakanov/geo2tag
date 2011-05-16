#include "Action.h"

Action::Action(int mask, const QString & action):
        m_mask(mask),
        m_action(action)
{
}

qlonglong Action::getId() const
{
  // Database is not contain 0 in sequences, see scripts/base.sql
  return 0;
}

int Action::getMask()const
{
    return m_mask;
}

/*void Action::setMask(int mask)
{
    m_mask(mask);
}*/

/*void Action::setAction(const QString & action)
{
    m_action(action);
}*/

const QString& Action::getAction()const
{
    return m_action;
}

Action::~Action()
{
}

