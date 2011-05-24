/*
 * Copyright 2011  Tatiana Trofimova  trotava@gmail.com
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * 3. The name of the author may not be used to endorse or promote
 *    products derived from this software without specific prior written
 *    permission.
 *
 * The advertising clause requiring mention in adverts must never be included.
 */

/*!
 * \file AddChannel_Test.h
 * \brief Test suite for method processAddChannelQuery in class DbSession
 *
 * PROJ: OSLL/geo2tag
 * ----------------------------------------------------------- */

#include <QObject>
#include <QtTest/QtTest>
#include <QSignalSpy>
#include <QDebug>
#include <QtSql>
#include </usr/include/qt4/QtSql/qsql_psql.h>

#include "DbSession.h"
//#include "QueryExecutor.h"

namespace
{
  const QString master_requestLogin = "{\"login\":\"Kirill\",\"password\":\"test\"}";
  const QString master_request = "{\"auth_token\":\"KKKKKKKKKK\", \"name\":\"Test channel9\", \"description\":\"test chanel\", \"url\":\"http://osll.spb.ru/\", \
                         \"activeRadius\":3000}";
  const QString master_reply = "{ \"status\" : \"Ok\", \"status_description\" : \"Channel added\" }";
}


namespace Test
{
  class ChannelAdd_Test : public QObject
  {
    Q_OBJECT;

    common::DbObjectsCollection&  m_db;
    QByteArray requestLoginByte;
    QByteArray requestByte;
    QByteArray replyByte;

    public:

      ChannelAdd_Test(QObject *parent = NULL) : QObject(parent), m_db(common::DbObjectsCollection::getInstance())
      {
        m_db.forceUpdate();
        requestLoginByte.append(master_requestLogin);
        requestByte.append(master_request);
        replyByte.append(master_reply);
      }

      ~ChannelAdd_Test()
      {
      }

    private slots:

      void addChannel()
      {
        m_db.process("login", requestLoginByte);
        QString reply=QString(m_db.process("addChannel", requestByte).data());
        m_db.forceUpdate();

        QCOMPARE(reply,master_reply);
      }

  };                                    // class AddChannel_Test

}                                       // end of namespace Test
