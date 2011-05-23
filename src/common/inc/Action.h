#ifndef ACTION_H
#define ACTION_H

#include "ConcurrentVector.h"


class Action: public QObject
{
    Q_OBJECT

    int m_mask;        //!< bit mask 1 - 'subscribe', 2 - 'unsubscribe'
    QString m_description;  //!< 4 - 'write', 8 - 'read', 16 - 'create'



public:
    Action(int mask, const QString & description);

    virtual qlonglong getId() const;

    int getMask()const;
    void setMask(int mask);

    const QString& getDescription()const;
    void setDescription(const QString & description);


    virtual ~Action();

};
typedef ConcurrentVector<Action> Actions;


#endif // ACTION_H
