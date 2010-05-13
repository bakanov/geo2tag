#ifndef OBSERVER_H
#define OBSERVER_H

#include <QDialog>
#include "ui_ObserverForm.h"
#include "defs.h"
#include "RSSFeedQuery.h"
#include "LoginQuery.h"
class Observer : public QDialog
{
    Q_OBJECT;
    Ui::Form           m_ui;
    QVector<MarkInfo>  m_data;
    CHandlePtr<common::DataMarks> m_marks;
    GUI::RSSFeedQuery  *rssFeedQuery;
    GUI::LoginQuery *loginQuery;
public:

    Observer();

signals:
    void dataUpdated();
    void dataMarksGotten(CHandlePtr<common::DataMarks>& marks);
public slots:
    void tokenRecieved(QString status,QString auth_token);
    void updateData(CHandlePtr<common::DataMarks>& marks);
    void buttonPushed();
    void updateView();
    void updateList();
    void doRequest();
    void usersSelected(const QString & text);
};

#endif // OBSERVER_H
