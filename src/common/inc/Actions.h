#ifndef ACTIONS_H
#define ACTIONS_H

#include "ConcurrentVector.h"


class Actions: public QObject
{
    Q_OBJECT

    qlonglong m_id;
    QString m_action;

public:
    Actions(qlonglong id, QString & action);


    qlonglong getId()const;
    //void setId(int id);

    //void setAction(QString & action);
    const QString& getAction()const;

    virtual ~Actions();

};
typedef ConcurrentVector<Actions> Action;

#endif // ACTIONS_H
