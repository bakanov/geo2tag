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

namespace
{
  const QString wrongToken = "wrongToken";
  const QString requestBegin = "{\"auth_token\":\"";
  const QString replyWrongToken = "{ \"status\" : \"Error\", \"status_description\" : \"Wrong authentification key\" }";
  const QString replyWrongChannel = "{ \"status\" : \"Error\", \"status_description\" : \"Wrong channel's' name!\" }";
  const QString replyWrongMarkId = "{ \"status\" : \"Error\", \"status_description\" : \"Wrong mark id!\" }";

  const QString requestLogin = "{\"login\":\"Kirill\",\"password\":\"test\"}";
  const QString replyLoginBegin = "{ \"auth_token\" : \"";
  const QString replyLoginEnd = "\", \"status\" : \"Ok\", \"status_description\" : \"Authorization was successful\" }";

  const QString requestAddChannelEnd = "\", \"name\":\"Test Time Slot channel\", \"description\":\"Test Time Slot channel\", \"url\":\"http://osll.spb.ru/\", \"activeRadius\":3000}";
  const QString replyAddChannelCorrect = "{ \"status\" : \"Ok\", \"status_description\" : \"Channel added\" }";

  const QString requestGetTimeSlotEnd = "\",\"channel\":\"Test Time Slot channel\"}";
  const QString requestGetTimeSlotWrongChannelEnd = "\",\"channel\":\"There is no such channel\"}";
  const QString replyGetTimeSlotCorrect = "{ \"timeSlot\" : 525600 }";
  const QString replyGetTimeSlotAfterSetCorrect = "{ \"timeSlot\" : 10080 }";

  const QString requestSetTimeSlotEnd = "\",\"channel\":\"Test Time Slot channel\",\"timeSlot\":10080}";
  const QString requestSetTimeSlotWrongChannelEnd = "\",\"channel\":\"There is no such channel\",\"timeSlot\":10080}";
  const QString replySetTimeSlotCorrect = "{ \"status\" : \"Ok\", \"status_description\" : \"Time slot for channel is set\" }";

  const QString requestSetDefaultTimeSlotEnd = "\",\"channel\":\"Test Time Slot channel\"}";
  const QString requestSetDefaultTimeSlotWrongChannelEnd = "\",\"channel\":\"There is no such channel\"}";
  const QString replySetDefaultTimeSlotCorrect = "{ \"status\" : \"Ok\", \"status_description\" : \"Now the channel has default time slot value\" }";
  const QString replySetDefaultTimeSlotIfAlreadyDefault = "{ \"status\" : \"Ok\", \"status_description\" : \"The channel already has default time slot value\" }";

  const QString requestAddNewMarkEnd = "\", \"channel\" : \"Test Time Slot channel\", \"description\" : \"test tag\", \"latitude\" : 61.2,\"link\" : \"unknown\", \"longitude\" : 31.0, \"time\" : \"02 06 2011 15:33:47.630\", \"title\" : \"tag\" }";
  const QString replyAddNewMarkBegin = "{ \"mark_id\" : ";
  const QString replyAddNewMarkEnd = ", \"status\" : \"Ok\", \"status_description\" : \"Tag has been added\" }";

  const QString requestGetTimeSlotMarkEnd = "\",\"mark_id\":";

  const QString requestSetTimeSlotMarkEnd = ",\"timeSlot\":10080}";
  const QString replySetTimeSlotMarkCorrect = "{ \"status\" : \"Ok\", \"status_description\" : \"Time slot for tag is set\" }";

  const QString replySetDefaultTimeSlotMarkCorrect = "{ \"status\" : \"Ok\", \"status_description\" : \"Now the tag has default time slot value\" }";
  const QString replySetDefaultTimeSlotMarkIfAlreadyDefault = "{ \"status\" : \"Ok\", \"status_description\" : \"The tag already has default time slot value\" }";

  const QString replyGetSessionPointCorrectBegin = "{ \"latitude\" : 60.0, \"longitude\" : 30.0, \"radius\" : 20037.8, \"time\" : \"";
  const QString replyGetSessionPointCorrectEnd = "\", \"timeSlot\" : 525600 }";
  const QString replyGetSessionPointAfterSetNotCurrentTime = "{ \"latitude\" : 55.5, \"longitude\" : 37.6, \"radius\" : 10.0, \"time\" : \"2010-09-01T09:00:47\", \"timeSlot\" : 1051200 }";
  const QString replyGetSessionPointAfterSetCurrentTimeBegin = "{ \"latitude\" : 55.5, \"longitude\" : 37.6, \"radius\" : 10.0, \"time\" : \"";
  const QString replyGetSessionPointAfterSetCurrentTimeEnd = "\", \"timeSlot\" : 1051200 }";

  const QString requestSetSessionPointNotCurrentTime = "\",\"latitude\" : 55.5, \"longitude\" : 37.6, \"time\" : \"01 09 2010 09:00:47.630\", \"timeSlot\":1051200, \"radius\":10, \"isCurrentTime\":0}";
  const QString replySetSessionPointCorrect = "{ \"status\" : \"Ok\", \"status_description\" : \"Data for session is set\" }";
  const QString requestSetSessionPointCurrentTime = "\",\"latitude\" : 55.5, \"longitude\" : 37.6, \"time\" : \"01 09 2010 09:00:47.630\", \"timeSlot\":1051200, \"radius\":10, \"isCurrentTime\":1}";

  const QString replySetDefaultSessionPointCorrect = "{ \"status\" : \"Ok\", \"status_description\" : \"Now data for session have default values\" }";
}


namespace Test
{
  class TestsForTimeSlotAndSession : public QObject
  {
    Q_OBJECT;

    common::DbObjectsCollection&  m_db;
    QString m_token;
    QString m_markId;

    public:

      TestsForTimeSlotAndSession(QObject *parent = NULL);
      ~TestsForTimeSlotAndSession();

    private slots:

      void login();

      void addChannel();

      void getTimeSlot();
      void getTimeSlotWrongToken();
      void getTimeSlotWrongChannel();

      void setTimeSlot();
      void getTimeSlotAfterSet();
      void setTimeSlotWrongToken();
      void setTimeSlotWrongChannel();

      void setDefaultTimeSlot();
      void setDefaultTimeSlotWrongToken();
      void setDefaultTimeSlotWrongChannel();
      void setDefaultTimeSlotIfAlreadyDefault();

      void addNewMark();

      void getTimeSlotMark();
      void getTimeSlotMarkWrongToken();
      void getTimeSlotMarkWrongMarkId();

      void setTimeSlotMark();
      void getTimeSlotMarkAfterSet();
      void setTimeSlotMarkWrongToken();
      void setTimeSlotMarkWrongMarkId();

      void setDefaultTimeSlotMark();
      void setDefaultTimeSlotMarkWrongToken();
      void setDefaultTimeSlotMarkWrongMarkId();
      void setDefaultTimeSlotMarkIfAlreadyDefault();

      void getSessionPoint();

      void setSessionPointNotCurrentTime();
      void getSessionPointAfterSetNotCurrentTime();
      void setSessionPointCurrentTime();
      void getSessionPointAfterSetCurrentTime();
      void setSessionPointWrongToken();

      void setDefaultSessionPoint();
      void setDefaultSessionPointWrongToken();

  };                                    // class AddChannel_Test

}                                       // end of namespace Test
