#include <sstream>
#include <syslog.h>
#include <string.h>
#include <fcgi_stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <QDebug>
#include "server.h"

//#include "AvailableListJsonQuery.h"
//#include "SubscribedListJsonQuery.h"
//#include "SubscribeQuery.h"
//#include "ApplyMarkJsonQuery.h"
//#include "ApplyChannelJsonQuery.h"
//#include "RssFeedJsonQuery.h"
//#include "UnknownJsonQuery.h"
//#include "UnsubscribeJsonQuery.h"
//#include "LoginJsonQuery.h"
//#include "DynamicCastFailure.h"
//#include "ApplyUserJsonQuery.h"

#define LISTENSOCK_FILENO 0
#define LISTENSOCK_FLAGS 0

Server::Server()
{
    int err = FCGX_Init(); // call before Accept in multithreaded apps

//    m_factory.reg<AvailableList>(AVAILABLE_LIST);
//    m_factory.reg<SubscribedList>(SUBSCRIBED_LIST);
//    m_factory.reg<SubscribeQuery>(SUBSCRIBE);
//    m_factory.reg<ApplyMarkJsonQuery>(APPLYMARK);
//    m_factory.reg<ApplyChannelJsonQuery>(APPLYCHANNEL);
//    m_factory.reg<ApplyUserJsonQuery>(APPLYUSER);
//    m_factory.reg<RssFeedJsonQuery>(RSSFEED);
//    m_factory.reg<UnsubscribeJsonQuery>(UNSUBSCRIBE);
//    m_factory.reg<LoginJsonQuery>(LOGIN);
//    m_factory.reg<UnknownJsonQuery>(UNKNOWN);

    if (err)
    {
        std::ostringstream s;
        s << "FCGX_Init failed: " << err;
        syslog(LOG_INFO, s.str().c_str());
    }

    err = FCGX_InitRequest(&m_cgi,LISTENSOCK_FILENO, LISTENSOCK_FLAGS);
    if (err)
    {
        std::ostringstream s;
        s << "FCGX_InitRequest failed: " << err;
        syslog(LOG_INFO, s.str().c_str());
    }
}


QByteArray Server::process(const QString& query, const QByteArray &data)
{
      QByteArray answer;

      answer.append("Status: 200 OK\r\nContent-Type: text/html\r\n\r\n");

//    /*
//     * We are a FastCGI module so we just need write our result to the standart output.
//     */
//    Stream s(m_cgi.out);

//    QString str=q.getStream().str();
//    QStringstream ss(str);
//    // syslog(LOG_INFO,ss.str().c_str());

//    QSharedPointer<IJsonQuery> query=m_factory.getJsonQuery(q,ss);
//    try
//    {
//        query->process();
//        s << "Status: 200 OK\r\nContent-Type: text/html\r\n\r\n";
//        s << (*query);
//    }
//    catch (const CExceptionSource& e)
//    {
//        syslog(LOG_INFO,"Dynamic Cast Failure. Line %i, file %s",e.getLine(),e.getSource());
//        s << "Status: 500 Internal Server Error\r\nContent-Type: text/html\r\n\r\n Error applying mark.";
//    }
      return answer;
}

void Server::extractIncomingData(const FCGX_Request& request, QString& queryString, QByteArray& queryBody)
{
    queryString.clear();
    queryBody.clear();
    queryString = FCGX_GetParam("QUERY_STRING", m_cgi.envp);
    for(;;)
    {
      char ch = FCGX_GetChar(request.in);
      if(ch != -1)
         queryBody.append(ch);
      else
         break;
    }
}

void Server::run()
{
    syslog(LOG_INFO,"Starting server thread...");
    for(;;)
    {
        int err = FCGX_Accept_r(&m_cgi);
        if (err)
        {
            syslog(LOG_INFO, "FCGX_Accept_r stopped: %d", err);
            break;
        }
        QString queryString;
        QByteArray queryBody, response;
        extractIncomingData(m_cgi,queryString,queryBody);
        response = process(queryString, queryBody);
        int written = FCGX_PutStr(response.data(), response.size(), m_cgi.out);
        if(written != response.size())
        {
            qDebug() << "some data was loast during writing to the pipe";
        }
        FCGX_Finish_r(&m_cgi);
    }
}

void Server::serve()
{
    start();
}

Server::~Server()
{
    wait();
    FCGX_ShutdownPending();
}
