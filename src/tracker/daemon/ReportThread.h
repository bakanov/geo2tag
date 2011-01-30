#ifndef REPORTTHREAD_H
#define REPORTTHREAD_H

#include <QThread>
#include <QTcpSocket>
#include <QTextStream>

#include "Control.h"

class ControlThread : public QObject
{
    Q_OBJECT

    QTcpSocket *m_client;
    QTextStream *m_device;
    Control *m_daemon;

    typedef void (ControlThread::*ProcessMethod)(void);

    QMap<QString, ProcessMethod> m_processors;

    void processStartQuery();
    void processStopQuery();
    void processLogsQuery();
    void processStatusQuery();

private slots:
    void run();

public:
    ControlThread(QTcpSocket * socket, Control *control, QObject *parent = 0);

signals:

public slots:

};

#endif // REPORTTHREAD_H