#ifndef UPDATETHREAD_H
#define UPDATETHREAD_H

#include <QtSql>
#include <QThread>
#include <QReadWriteLock>
#include <QMap>
#include "DataMarkInternal.h"
#include "UserInternal.h"
#include "ChannelInternal.h"
#include "DataChannel.h"
#include "TimeSlotInternal.h"
#include "ChannelAction.h"

class UpdateThread: public QThread
{
  Q_OBJECT

    QSharedPointer<Channels>     m_channelsContainer;
  QSharedPointer<DataMarks>    m_tagsContainer;
  QSharedPointer<Users>        m_usersContainer;
  QSharedPointer<TimeSlots>    m_timeSlotsContainer;
  QSharedPointer<DataChannels> m_dataChannelsMap;
  //QSharedPointer<ChannelActions> m_channelActionsContainer; //--!!
  //QMap<QPair<qlonglong,qlonglong>,int> m_channelAccessContainer;

  QSqlDatabase m_database;

  //will be locked when containers is being updated
  QReadWriteLock m_updateLock;

  void loadUsers(Users &);
  void loadTags(DataMarks &);
  void loadChannels(Channels &);
  void loadTimeSlots(TimeSlots &);
  //void loadChannelActions(ChannelActions &); //--!!
  //void loadChannelAccess(ChannelAccess &); //--!!
  void updateReflections(DataMarks&, Users&, Channels&, TimeSlots&);//, ChannelActions&);

  void run();

  public:
    UpdateThread(
      const QSqlDatabase &db,
      const QSharedPointer<DataMarks>& tags,
      const QSharedPointer<Users>& users,
      const QSharedPointer<Channels>& channels,
      const QSharedPointer<TimeSlots>& timeSlots,
      const QSharedPointer<DataChannels>& dataChannelsMap,
      //const QSharedPointer<ChannelActions> &channelActions,
      QObject *parent = 0);

    void lockWriting();

    void unlockWriting();

    signals:

  public slots:

};
// UPDATETHREAD_H
#endif
