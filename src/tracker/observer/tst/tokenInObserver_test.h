#include <QtCore/QString>
#include <QtTest/QtTest>
#include <QtSql>
#include "../../../http_requests/inc/LoginQuery.h"
#include "../../../http_requests/inc/RSSFeedQuery.h"
#include "../../../service/inc/DbSession.h"

namespace Test
{
const QString loginRequest = "{\"login\":\"Kirill\",\"password\":\"test\"}";
const QString requestBegin = "{\"auth_token\":\"";
const QString requestEnd = "\", \"latitude\":30.0, \"longitude\":60.0, \"radius\":30.0}";
const QString correctReplyPart = "\"status\" : \"Ok\", \"status_description\" : \"feed has been generated\"";
const QString wrongReplyPart = "\"status\" : \"Error\", \"status_description\" : \"Wrong authentification key\"";
const QString wrongToken = "wrongToken";
class tokenInObserver_test : public QObject
{
    Q_OBJECT
    common::DbObjectsCollection&  m_db;
    QString m_token;
public:
    tokenInObserver_test(QObject *parent = NULL);


    ~tokenInObserver_test();
private slots:
    void testFeedRequestWithCorrectToken();
    void testFeedRequestWithWrongToken();


};
}
