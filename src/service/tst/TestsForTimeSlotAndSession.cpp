#include "TestsForTimeSlotAndSession.h"

namespace Test
{

  TestsForTimeSlotAndSession::TestsForTimeSlotAndSession(QObject *parent) : QObject(parent), m_db(common::DbObjectsCollection::getInstance())
  {
    m_db.forceUpdate();
  }

  TestsForTimeSlotAndSession::~TestsForTimeSlotAndSession()
  {
    QSqlDatabase database = QSqlDatabase::addDatabase("QPSQL");
    database.setHostName("localhost");
    database.setDatabaseName("geo2tag");
    database.setUserName("geo2tag");
    database.setPassword("geo2tag");

    bool result = database.open();
    if(!result)
    {
      syslog(LOG_INFO, "connection error %s",database.lastError().text().toStdString().c_str());
      return;
    }

    QSqlQuery deleteChannelQuery(database);
    syslog(LOG_INFO,"preparing sql query for deletting channel");
    deleteChannelQuery.prepare("DELETE FROM channel WHERE name='Test Time Slot channel';");

    database.transaction();

    result=deleteChannelQuery.exec();
    if(!result)
    {
      syslog(LOG_INFO,"Rollback for DeleteChannel sql query");
      database.rollback();
    }
    else
      syslog(LOG_INFO,"Commit for DeleteChannel sql query - delete from table channel");

    database.commit();

    QSqlQuery deleteMark(database);
    syslog(LOG_INFO,"preparing sql query for deletting mark");
    deleteMark.prepare("DELETE FROM tag WHERE id= :id;");
    deleteMark.bindValue(":id", m_markId);

    database.transaction();

    result=deleteMark.exec();
    if(!result)
    {
      syslog(LOG_INFO,"Rollback for DeleteMark sql query");
      database.rollback();
    }
    else
      syslog(LOG_INFO,"Commit for DeleteMark sql query - delete from table tag");

    database.commit();

    database.close();
  }

  void TestsForTimeSlotAndSession::login()
  {
    QByteArray requestLoginByte;
    requestLoginByte.append(requestLogin);

    QString reply = QString(m_db.process("login", requestLoginByte).data());
    m_db.forceUpdate();

    int pos = reply.indexOf("{");
    reply.remove(0, pos);

    QStringList list = reply.split('"');
    QString token = list.at(3);
    m_token = token;

    QString replyLoginCorrect = replyLoginBegin + token +replyLoginEnd;
    QCOMPARE(0,reply.compare(replyLoginCorrect));
  }

  void TestsForTimeSlotAndSession::addChannel()
  {
    QString request = requestBegin + m_token + requestAddChannelEnd;
    QByteArray requestByte;
    requestByte.append(request);

    QString reply = QString(m_db.process("addChannel", requestByte).data());
    m_db.forceUpdate();

    int pos = reply.indexOf("{");
    reply.remove(0, pos);

    QCOMPARE(0,reply.compare(replyAddChannelCorrect));
  }

  void TestsForTimeSlotAndSession::getTimeSlot()
  {
    QString request = requestBegin + m_token + requestGetTimeSlotEnd;
    QByteArray requestByte;
    requestByte.append(request);

    QString reply = QString(m_db.process("getTimeSlot", requestByte).data());
    m_db.forceUpdate();

    int pos = reply.indexOf("{");
    reply.remove(0, pos);

    QCOMPARE(0,reply.compare(replyGetTimeSlotCorrect));
  }

  void TestsForTimeSlotAndSession::getTimeSlotWrongToken()
  {
    QString request = requestBegin + wrongToken + requestGetTimeSlotEnd;
    QByteArray requestByte;
    requestByte.append(request);

    QString reply = QString(m_db.process("getTimeSlot", requestByte).data());
    m_db.forceUpdate();

    int pos = reply.indexOf("{");
    reply.remove(0, pos);

    QCOMPARE(0,reply.compare(replyWrongToken));
  }

  void TestsForTimeSlotAndSession::getTimeSlotWrongChannel()
  {
    QString request = requestBegin + m_token + requestGetTimeSlotWrongChannelEnd;
    QByteArray requestByte;
    requestByte.append(request);

    QString reply = QString(m_db.process("getTimeSlot", requestByte).data());
    m_db.forceUpdate();

    int pos = reply.indexOf("{");
    reply.remove(0, pos);

    QCOMPARE(0,reply.compare(replyWrongChannel));
  }

  void TestsForTimeSlotAndSession::setTimeSlot()
  {
    QString request = requestBegin + m_token + requestSetTimeSlotEnd;
    QByteArray requestByte;
    requestByte.append(request);

    QString reply = QString(m_db.process("setTimeSlot", requestByte).data());
    m_db.forceUpdate();

    int pos = reply.indexOf("{");
    reply.remove(0, pos);

    QCOMPARE(0,reply.compare(replySetTimeSlotCorrect));
  }
  void TestsForTimeSlotAndSession::getTimeSlotAfterSet()
  {
    QString request = requestBegin + m_token + requestGetTimeSlotEnd;
    QByteArray requestByte;
    requestByte.append(request);

    QString reply = QString(m_db.process("getTimeSlot", requestByte).data());
    m_db.forceUpdate();

    int pos = reply.indexOf("{");
    reply.remove(0, pos);

    QCOMPARE(0,reply.compare(replyGetTimeSlotAfterSetCorrect));
  }

  void TestsForTimeSlotAndSession::setTimeSlotWrongToken()
  {
    QString request = requestBegin + wrongToken + requestSetTimeSlotEnd;
    QByteArray requestByte;
    requestByte.append(request);

    QString reply = QString(m_db.process("setTimeSlot", requestByte).data());
    m_db.forceUpdate();

    int pos = reply.indexOf("{");
    reply.remove(0, pos);

    QCOMPARE(0,reply.compare(replyWrongToken));
  }

  void TestsForTimeSlotAndSession::setTimeSlotWrongChannel()
  {
    QString request = requestBegin + m_token + requestSetTimeSlotWrongChannelEnd;
    QByteArray requestByte;
    requestByte.append(request);

    QString reply = QString(m_db.process("setTimeSlot", requestByte).data());
    m_db.forceUpdate();

    int pos = reply.indexOf("{");
    reply.remove(0, pos);

    QCOMPARE(0,reply.compare(replyWrongChannel));
  }

  void TestsForTimeSlotAndSession::setDefaultTimeSlot()
  {
    QString request = requestBegin + m_token + requestSetDefaultTimeSlotEnd;
    QByteArray requestByte;
    requestByte.append(request);

    QString reply = QString(m_db.process("setDefaultTimeSlot", requestByte).data());
    m_db.forceUpdate();

    int pos = reply.indexOf("{");
    reply.remove(0, pos);

    QCOMPARE(0,reply.compare(replySetDefaultTimeSlotCorrect));
    getTimeSlot();                      //to check that after setDefaultTimeSlot time slot of channel really has default value
  }

  void TestsForTimeSlotAndSession::setDefaultTimeSlotWrongToken()
  {
    QString request = requestBegin + wrongToken + requestSetDefaultTimeSlotEnd;
    QByteArray requestByte;
    requestByte.append(request);

    QString reply = QString(m_db.process("setDefaultTimeSlot", requestByte).data());
    m_db.forceUpdate();

    int pos = reply.indexOf("{");
    reply.remove(0, pos);

    QCOMPARE(0,reply.compare(replyWrongToken));
  }

  void TestsForTimeSlotAndSession::setDefaultTimeSlotWrongChannel()
  {
    QString request = requestBegin + m_token + requestSetDefaultTimeSlotWrongChannelEnd;
    QByteArray requestByte;
    requestByte.append(request);

    QString reply = QString(m_db.process("setDefaultTimeSlot", requestByte).data());
    m_db.forceUpdate();

    int pos = reply.indexOf("{");
    reply.remove(0, pos);

    QCOMPARE(0,reply.compare(replyWrongChannel));
  }

  void TestsForTimeSlotAndSession::setDefaultTimeSlotIfAlreadyDefault()
  {
    QString request = requestBegin + m_token + requestSetDefaultTimeSlotEnd;
    QByteArray requestByte;
    requestByte.append(request);

    QString reply = QString(m_db.process("setDefaultTimeSlot", requestByte).data());
    m_db.forceUpdate();

    int pos = reply.indexOf("{");
    reply.remove(0, pos);

    QCOMPARE(0,reply.compare(replySetDefaultTimeSlotIfAlreadyDefault));
  }

  void TestsForTimeSlotAndSession::addNewMark()
  {
    QString request = requestBegin + m_token + requestAddNewMarkEnd;
    QByteArray requestByte;
    requestByte.append(request);

    QString reply = QString(m_db.process("apply", requestByte).data());
    m_db.forceUpdate();

    int pos = reply.indexOf("{");
    reply.remove(0, pos);

    QStringList list = reply.split(' ');
    QString markId = list.at(3);
    markId.remove(QChar(','));
    m_markId = markId;

    QString replyCorrect = replyAddNewMarkBegin + markId +replyAddNewMarkEnd;
    QCOMPARE(0,reply.compare(replyCorrect));
  }

  void TestsForTimeSlotAndSession::getTimeSlotMark()
  {
    QString request = requestBegin + m_token + requestGetTimeSlotMarkEnd + m_markId+"}";
    QByteArray requestByte;
    requestByte.append(request);

    QString reply = QString(m_db.process("getTimeSlotMark", requestByte).data());
    m_db.forceUpdate();

    int pos = reply.indexOf("{");
    reply.remove(0, pos);

    QCOMPARE(0,reply.compare(replyGetTimeSlotCorrect));
  }

  void TestsForTimeSlotAndSession::getTimeSlotMarkWrongToken()
  {
    QString request = requestBegin + wrongToken + requestGetTimeSlotMarkEnd + m_markId+"}";
    QByteArray requestByte;
    requestByte.append(request);

    QString reply = QString(m_db.process("getTimeSlotMark", requestByte).data());
    m_db.forceUpdate();

    int pos = reply.indexOf("{");
    reply.remove(0, pos);

    QCOMPARE(0,reply.compare(replyWrongToken));
  }

  void TestsForTimeSlotAndSession::getTimeSlotMarkWrongMarkId()
  {
    int wrongMarkIdInt = m_markId.toInt() + 1;
    QString wrongMarkId = QString::number(wrongMarkIdInt);
    QString request = requestBegin + m_token + requestGetTimeSlotMarkEnd + wrongMarkId +"}";
    QByteArray requestByte;
    requestByte.append(request);

    QString reply = QString(m_db.process("getTimeSlotMark", requestByte).data());
    m_db.forceUpdate();

    int pos = reply.indexOf("{");
    reply.remove(0, pos);

    QCOMPARE(0,reply.compare(replyWrongMarkId));
  }

  void TestsForTimeSlotAndSession::setTimeSlotMark()
  {
    QString request = requestBegin + m_token + requestGetTimeSlotMarkEnd + m_markId + requestSetTimeSlotMarkEnd;
    QByteArray requestByte;
    requestByte.append(request);

    QString reply = QString(m_db.process("setTimeSlotMark", requestByte).data());
    m_db.forceUpdate();

    int pos = reply.indexOf("{");
    reply.remove(0, pos);

    QCOMPARE(0,reply.compare(replySetTimeSlotMarkCorrect));
  }

  void TestsForTimeSlotAndSession::getTimeSlotMarkAfterSet()
  {
    QString request = requestBegin + m_token + requestGetTimeSlotMarkEnd + m_markId+"}";
    QByteArray requestByte;
    requestByte.append(request);

    QString reply = QString(m_db.process("getTimeSlotMark", requestByte).data());
    m_db.forceUpdate();

    int pos = reply.indexOf("{");
    reply.remove(0, pos);

    QCOMPARE(0,reply.compare(replyGetTimeSlotAfterSetCorrect));
  }

  void TestsForTimeSlotAndSession::setTimeSlotMarkWrongToken()
  {
    QString request = requestBegin + wrongToken + requestGetTimeSlotMarkEnd + m_markId + requestSetTimeSlotMarkEnd;
    QByteArray requestByte;
    requestByte.append(request);

    QString reply = QString(m_db.process("setTimeSlotMark", requestByte).data());
    m_db.forceUpdate();

    int pos = reply.indexOf("{");
    reply.remove(0, pos);

    QCOMPARE(0,reply.compare(replyWrongToken));
  }

  void TestsForTimeSlotAndSession::setTimeSlotMarkWrongMarkId()
  {
    int wrongMarkIdInt = m_markId.toInt() + 1;
    QString wrongMarkId = QString::number(wrongMarkIdInt);
    QString request = requestBegin + m_token + requestGetTimeSlotMarkEnd + wrongMarkId + requestSetTimeSlotMarkEnd;
    QByteArray requestByte;
    requestByte.append(request);

    QString reply = QString(m_db.process("setTimeSlotMark", requestByte).data());
    m_db.forceUpdate();

    int pos = reply.indexOf("{");
    reply.remove(0, pos);

    QCOMPARE(0,reply.compare(replyWrongMarkId));
  }

  void TestsForTimeSlotAndSession::setDefaultTimeSlotMark()
  {
    QString request = requestBegin + m_token + requestGetTimeSlotMarkEnd + m_markId+"}";
    QByteArray requestByte;
    requestByte.append(request);

    QString reply = QString(m_db.process("setDefaultTimeSlotMark", requestByte).data());
    m_db.forceUpdate();

    int pos = reply.indexOf("{");
    reply.remove(0, pos);

    QCOMPARE(0,reply.compare(replySetDefaultTimeSlotMarkCorrect));
    getTimeSlotMark();                  //to check that after setDefaultTimeSlotMark time slot of mark really has default value
  }

  void TestsForTimeSlotAndSession::setDefaultTimeSlotMarkWrongToken()
  {
    QString request = requestBegin + wrongToken + requestGetTimeSlotMarkEnd + m_markId+"}";
    QByteArray requestByte;
    requestByte.append(request);

    QString reply = QString(m_db.process("setDefaultTimeSlotMark", requestByte).data());
    m_db.forceUpdate();

    int pos = reply.indexOf("{");
    reply.remove(0, pos);

    QCOMPARE(0,reply.compare(replyWrongToken));
  }

  void TestsForTimeSlotAndSession::setDefaultTimeSlotMarkWrongMarkId()
  {
    int wrongMarkIdInt = m_markId.toInt() + 1;
    QString wrongMarkId = QString::number(wrongMarkIdInt);
    QString request = requestBegin + m_token + requestGetTimeSlotMarkEnd + wrongMarkId +"}";
    QByteArray requestByte;
    requestByte.append(request);

    QString reply = QString(m_db.process("setDefaultTimeSlotMark", requestByte).data());
    m_db.forceUpdate();

    int pos = reply.indexOf("{");
    reply.remove(0, pos);

    QCOMPARE(0,reply.compare(replyWrongMarkId));
  }

  void TestsForTimeSlotAndSession::setDefaultTimeSlotMarkIfAlreadyDefault()
  {
    QString request = requestBegin + m_token + requestGetTimeSlotMarkEnd + m_markId+"}";
    QByteArray requestByte;
    requestByte.append(request);

    QString reply = QString(m_db.process("setDefaultTimeSlotMark", requestByte).data());
    m_db.forceUpdate();

    int pos = reply.indexOf("{");
    reply.remove(0, pos);

    QCOMPARE(0,reply.compare(replySetDefaultTimeSlotMarkIfAlreadyDefault));
  }

  void TestsForTimeSlotAndSession::getSessionPoint()
  {
    QString request = requestBegin + m_token + requestGetTimeSlotMarkEnd + m_markId + "}";
    QByteArray requestByte;
    requestByte.append(request);

    QString reply = QString(m_db.process("getSessionPoint", requestByte).data());
    m_db.forceUpdate();

    int pos = reply.indexOf("{");
    reply.remove(0, pos);

    int index = 0;
    int number = 0;
    while (!(number == 5))
    {
      index = reply.indexOf(":", index+1);
      ++number;
    }
    reply.remove(index+2,4);

    QString currentDateTime = QDateTime::currentDateTime().toUTC().toString(Qt::ISODate);
    currentDateTime.remove(currentDateTime.size() - 4, 4);
    QString replyCorrect =replyGetSessionPointCorrectBegin + currentDateTime + replyGetSessionPointCorrectEnd ;

    QCOMPARE(0,reply.compare(replyCorrect));
  }

  void TestsForTimeSlotAndSession::setSessionPointNotCurrentTime()
  {
    QString request = requestBegin + m_token + requestSetSessionPointNotCurrentTime;
    QByteArray requestByte;
    requestByte.append(request);

    QString reply = QString(m_db.process("setSessionPoint", requestByte).data());
    m_db.forceUpdate();

    int pos = reply.indexOf("{");
    reply.remove(0, pos);

    QCOMPARE(0,reply.compare(replySetSessionPointCorrect));
  }

  void TestsForTimeSlotAndSession::getSessionPointAfterSetNotCurrentTime()
  {
    QString request = requestBegin + m_token + requestGetTimeSlotMarkEnd + m_markId + "}";
    QByteArray requestByte;
    requestByte.append(request);

    QString reply = QString(m_db.process("getSessionPoint", requestByte).data());
    m_db.forceUpdate();

    int pos = reply.indexOf("{");
    reply.remove(0, pos);

    QCOMPARE(0,reply.compare(replyGetSessionPointAfterSetNotCurrentTime));
  }

  void TestsForTimeSlotAndSession::setSessionPointCurrentTime()
  {
    QString request = requestBegin + m_token + requestSetSessionPointCurrentTime;
    QByteArray requestByte;
    requestByte.append(request);

    QString reply = QString(m_db.process("setSessionPoint", requestByte).data());
    m_db.forceUpdate();

    int pos = reply.indexOf("{");
    reply.remove(0, pos);

    QCOMPARE(0,reply.compare(replySetSessionPointCorrect));
  }

  void TestsForTimeSlotAndSession::getSessionPointAfterSetCurrentTime()
  {
    QString request = requestBegin + m_token + requestGetTimeSlotMarkEnd + m_markId + "}";
    QByteArray requestByte;
    requestByte.append(request);

    QString reply = QString(m_db.process("getSessionPoint", requestByte).data());
    m_db.forceUpdate();

    int pos = reply.indexOf("{");
    reply.remove(0, pos);

    int index = 0;
    int number = 0;
    while (!(number == 5))
    {
      index = reply.indexOf(":", index+1);
      ++number;
    }
    reply.remove(index+2,4);

    QString currentDateTime = QDateTime::currentDateTime().toUTC().toString(Qt::ISODate);
    currentDateTime.remove(currentDateTime.size() - 4, 4);
    QString replyCorrect =replyGetSessionPointAfterSetCurrentTimeBegin + currentDateTime + replyGetSessionPointAfterSetCurrentTimeEnd ;

    QCOMPARE(0,reply.compare(replyCorrect));
  }

  void TestsForTimeSlotAndSession::setSessionPointWrongToken()
  {
    QString request = requestBegin + wrongToken + requestSetSessionPointNotCurrentTime;
    QByteArray requestByte;
    requestByte.append(request);

    QString reply = QString(m_db.process("setSessionPoint", requestByte).data());
    m_db.forceUpdate();

    int pos = reply.indexOf("{");
    reply.remove(0, pos);

    QCOMPARE(0,reply.compare(replyWrongToken));
  }

  void TestsForTimeSlotAndSession::setDefaultSessionPoint()
  {
    QString request = requestBegin + m_token + "\"}";
    QByteArray requestByte;
    requestByte.append(request);

    QString reply = QString(m_db.process("setDefaultSessionPoint", requestByte).data());
    m_db.forceUpdate();

    int pos = reply.indexOf("{");
    reply.remove(0, pos);

    QCOMPARE(0,reply.compare(replySetDefaultSessionPointCorrect));
    getSessionPoint();                  //to check that after setDefaultSessionPoint parameters for session are default
  }

  void TestsForTimeSlotAndSession::setDefaultSessionPointWrongToken()
  {
    QString request = requestBegin + wrongToken + "\"}";
    QByteArray requestByte;
    requestByte.append(request);

    QString reply = QString(m_db.process("setDefaultSessionPoint", requestByte).data());
    m_db.forceUpdate();

    int pos = reply.indexOf("{");
    reply.remove(0, pos);

    QCOMPARE(0,reply.compare(replyWrongToken));
  }

}
