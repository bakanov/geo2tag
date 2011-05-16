#ifndef ACTION_H
#define ACTION_H

#include "ConcurrentVector.h"


class Action: public QObject
{
    Q_OBJECT

    int m_mask;        //!< bit mask 1 - 'subscribe', 2 - 'unsubscribe'
    QString m_action;  //!< 4 - 'write', 8 - 'read', 16 - 'create'



public:
    Action(int mask, const QString & action);

    virtual qlonglong getId() const;

    int getMask()const;
    //void setMask(int mask);

    //void setAction(const QString & action);
    const QString& getAction()const;

    virtual ~Action();

};
typedef ConcurrentVector<Action> Actions;


#endif // ACTION_H
