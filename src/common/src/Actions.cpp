#include "Actions.h"

Actions::Actions(qlonglong id, QString & action):
        m_id(id),
        m_action(action)
{
}

qlonglong Actions::getId()const
{
    return m_id;
}

/*void Actions::setId(int id)
{
    m_id(id);
}*/

/*void Actions::setAction(QString & action)
{
    m_action(action);
}*/

const QString& Actions::getAction()const
{
    return m_action;
}

Actions::~Actions()
{
}
