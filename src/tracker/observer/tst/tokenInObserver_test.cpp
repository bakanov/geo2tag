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

}

tokenInObserver_test::~tokenInObserver_test()
{

}

void tokenInObserver_test::testFeedRequestWithCorrectToken()
{
    QByteArray rssFeedRequest;
    rssFeedRequest.append(requestBegin+m_token+requestEnd);
    QString reply = QString(m_db.process("rss", rssFeedRequest).data());
    int posBegin = reply.indexOf("\"status\" :");
    reply.remove(0,posBegin);
    int posEnd = reply.indexOf(" }",0);
    reply.remove(posEnd, reply.length());
    QCOMPARE(0,reply.compare(correctReplyPart));
}


void tokenInObserver_test::testFeedRequestWithWrongToken()
{
    QByteArray rssFeedRequest;
    rssFeedRequest.append(requestBegin+m_token+wrongToken+requestEnd);
    QString reply = QString(m_db.process("rss", rssFeedRequest).data());
    int posBegin = reply.indexOf("\"status\" :");
    reply.remove(0,posBegin);
    int posEnd = reply.indexOf(" }",0);
    reply.remove(posEnd, reply.length());
    QCOMPARE(0,reply.compare(wrongReplyPart));
}
}
