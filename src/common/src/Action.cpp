#include "Action.h"

Action::Action(int mask, const QString & description):
        m_mask(mask),
        m_description(description)
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

void Action::setMask(int mask)
{
    m_mask = mask;
}

void Action::setDescription(const QString & description)
{
    m_description = description;
}

const QString& Action::getDescription()const
{
    return m_description;
}

Action::~Action()
{
}

