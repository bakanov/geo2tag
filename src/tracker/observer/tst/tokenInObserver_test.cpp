#include "tokenInObserver_test.h"


namespace Test {
tokenInObserver_test::tokenInObserver_test(QObject *parent):QObject(parent), m_db(common::DbObjectsCollection::getInstance())
{

    m_db.forceUpdate();
    QByteArray logRequest;
    logRequest.append(loginRequest);


    QString reply = QString(m_db.process("login", logRequest).data());
    m_db.forceUpdate();

    int pos = reply.indexOf("{");
    reply.remove(0, pos);

    QStringList list = reply.split('"');
    QString token = list.at(3);
    m_token = token;
    qDebug()<<"TOKEN="<<token;

}

tokenInObserver_test::~tokenInObserver_test()
{

}

void tokenInObserver_test::testRequest()
{
    QByteArray rssFeedRequest;
    rssFeedRequest.append(requestBegin+m_token+requestEnd);
    QString reply = QString(m_db.process("rss", rssFeedRequest).data());
    //m_db.forceUpdate();
    int posBegin = reply.lastIndexOf("status");
    posBegin = reply.lastIndexOf(":",posBegin);
    int posEnd = reply.lastIndexOf(",",posBegin);
    reply.remove(0,posBegin+2);
    reply.remove(posEnd-1, reply.length()-posEnd);
    qDebug()<<reply;
    QCOMPARE(0,reply.compare("Ok"));
}

}
