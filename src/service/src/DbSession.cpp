/*
 * Copyright 2010  OSLL osll@osll.spb.ru
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
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
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
/*! ---------------------------------------------------------------
 *
 *
 * \file DbSession.cpp
 * \brief DbSession implementation
 *
 * File description
 *
 * PROJ: OSLL/geoblog
 * ---------------------------------------------------------------- */

#include <syslog.h>
#include "DbSession.h"

#include "LoginRequestJSON.h"
#include "LoginResponseJSON.h"

#include "AddNewMarkRequestJSON.h"
#include "AddNewMarkResponseJSON.h"

#include "AddUserRequestJSON.h"
#include "AddUserResponseJSON.h"

#include "RSSFeedRequestJSON.h"
#include "RSSFeedJSON.h"

#include "AddChannelRequestJSON.h"
#include "AddChannelResponseJSON.h"

#include "SubscribedChannelsRequestJSON.h"
#include "SubscribedChannelsResponseJSON.h"

#include "SubscribeChannelJSON.h"
#include "SubscribeChannelResponseJSON.h"

#include "GetTimeSlotRequestJSON.h"
#include "GetTimeSlotResponseJSON.h"

#include "SetTimeSlotRequestJSON.h"
#include "SetTimeSlotResponseJSON.h"

#include "JsonTimeSlot.h"

#include <QtSql>
#include <QMap>

namespace common
{
    const qulonglong DbObjectsCollection::A_YEAR_IN_ms = 31536000000;

    const QString DbObjectsCollection::error = QString("Error");
    const QString DbObjectsCollection::ok = QString("Ok");

    QSharedPointer<TimeSlot> DbObjectsCollection::defaultTimeSlot; // Null pointer


    DbObjectsCollection::DbObjectsCollection():
            m_channelsContainer(new Channels()),
            m_tagsContainer(new DataMarks()),
            m_usersContainer(new Users()),

            m_timeSlotsContainer(new TimeSlots()),
            m_dataChannelsMap(new DataChannels()),
            m_channelActionsContainer(new ChannelActions()),


            m_updateThread(NULL),
            m_queryExecutor(NULL)
    {

        m_processors.insert("login", &DbObjectsCollection::processLoginQuery);
        m_processors.insert("apply", &DbObjectsCollection::processAddNewMarkQuery);
        m_processors.insert("rss", &DbObjectsCollection::processRssFeedQuery);
        m_processors.insert("subscribe", &DbObjectsCollection::processSubscribeQuery);
        m_processors.insert("subscribed", &DbObjectsCollection::processSubscribedChannelsQuery);
        m_processors.insert("addUser", &DbObjectsCollection::processAddUserQuery);
        m_processors.insert("addChannel", &DbObjectsCollection::processAddChannelQuery);

        m_processors.insert("getChannelActions", &DbObjectsCollection::processGetChannelActionsQuery);

        m_processors.insert("getTimeSlot", &DbObjectsCollection::processGetTimeSlotQuery);
        m_processors.insert("setTimeSlot", &DbObjectsCollection::processSetTimeSlotQuery);


        QSqlDatabase database = QSqlDatabase::addDatabase("QPSQL");
        database.setHostName("localhost");
        database.setDatabaseName("geo2tag");
        database.setUserName("geo2tag");
        database.setPassword("geo2tag");
	

        m_updateThread = new UpdateThread(
                        QSqlDatabase::cloneDatabase(database,"updateThread"),
                        m_tagsContainer,
                        m_usersContainer,
                        m_channelsContainer,

                        m_timeSlotsContainer,
                        m_channelActionsContainer,

                        m_dataChannelsMap,
                        NULL);

        m_updateThread->start();

        m_queryExecutor = new QueryExecutor(QSqlDatabase::cloneDatabase(database,"executor"), NULL);
    }

    DbObjectsCollection& DbObjectsCollection::getInstance()
    {
        static DbObjectsCollection s;      
        return s;
    }

    DbObjectsCollection::~DbObjectsCollection()
    {
        m_updateThread->wait();
        delete m_updateThread;
        delete m_queryExecutor;
    }

    QByteArray DbObjectsCollection::process(const QString& queryType, const QByteArray& body)
    {
        if(!m_queryExecutor->isConnected())
        {
            m_queryExecutor->connect();
        }

        ProcessMethod method = m_processors.value(queryType);
        setDefaultTimeSlotValueForChannels();
	syslog(LOG_INFO,"calling %s processor %s",queryType.toStdString().c_str(),QString(body).toStdString().c_str());
        return (*this.*method)(body);
    }


    QByteArray DbObjectsCollection::setDefaultTimeSlotValueForChannels()
    {
        syslog(LOG_INFO, "Setting default time slot value for channels");
        if (defaultTimeSlot.isNull())
        {
            QSharedPointer<TimeSlot> timeSlot(new JsonTimeSlot(A_YEAR_IN_ms));            
            QSharedPointer<TimeSlot> realTimeSlot; // Null pointer
            QVector<QSharedPointer<TimeSlot> > currentTimeSlots = m_timeSlotsContainer->vector();           
            for(int i=0; i<currentTimeSlots.size(); i++)
            {                
                if(currentTimeSlots.at(i)->getSlot() == timeSlot->getSlot())
                {
                    realTimeSlot = currentTimeSlots.at(i);
                }
            }
            if (realTimeSlot.isNull())
            {
                QSharedPointer<TimeSlot> addedTimeSlot = m_queryExecutor->insertNewTimeSlot(timeSlot);
                if(!addedTimeSlot)
                {
                    syslog(LOG_INFO, "Error while inserting new time slot value");
                    DefaultResponseJSON response;
                    QByteArray answer;
                    response.setStatus(error);
                    response.setStatusMessage("Internal server error ):");
                    answer.append(response.getJson());
                    return answer;
                }
                m_updateThread->lockWriting();
                m_timeSlotsContainer->push_back(addedTimeSlot);
                defaultTimeSlot = addedTimeSlot;
                m_updateThread->unlockWriting();
            }
            else
            {
                m_updateThread->lockWriting();
                defaultTimeSlot = realTimeSlot;
                m_updateThread->unlockWriting();
            }
        }

        QVector<QSharedPointer<Channel> > currentChannels = m_channelsContainer->vector();
        for(int i=0; i<currentChannels.size(); i++)
        {
            if(currentChannels.at(i)->getTimeSlot().isNull())
            {
                m_updateThread->lockWriting();
                currentChannels.at(i)->setTimeSlot(defaultTimeSlot);
                m_updateThread->unlockWriting();
            }
        }
        return 0;
    }


    QSharedPointer<User> DbObjectsCollection::findUserFromToken(const QSharedPointer<User> &dummyUser) const
    {
        QSharedPointer<User> realUser; // Null pointer
        QVector<QSharedPointer<User> > currentUsers = m_usersContainer->vector();
        syslog(LOG_INFO, "checking user's key: %s from %d known users", dummyUser->getToken().toStdString().c_str(),
                                currentUsers.size());
        for(int i=0; i<currentUsers.size(); i++)
        {
            if(currentUsers.at(i)->getToken() == dummyUser->getToken())
            {
                realUser = currentUsers.at(i);
                break;
            }
        }
        return realUser;
    }





    QByteArray DbObjectsCollection::processLoginQuery(const QByteArray &data)
    {
        LoginRequestJSON request;
        LoginResponseJSON response;
        QByteArray answer;

        request.parseJson(data);

        QSharedPointer<User> dummyUser = request.getUsers()->at(0);
        QSharedPointer<User> realUser; // Null pointer
        QVector<QSharedPointer<User> > currentUsers = m_usersContainer->vector();

        for(int i=0; i<currentUsers.size(); i++)
        {
	    syslog(LOG_INFO,"Look up in %s and %s",currentUsers.at(i)->getLogin().toStdString().c_str(),
	    					currentUsers.at(i)->getPassword().toStdString().c_str());
            if(currentUsers.at(i)->getLogin() == dummyUser->getLogin())
            {
                if(currentUsers.at(i)->getPassword() == dummyUser->getPassword())
                {
                    realUser = currentUsers.at(i);
                    break;
                }
                else
                {
                    response.setStatus(error);
                    response.setStatusMessage("Wrong password");
                }
            }
        }
        answer.append("Status: 200 OK\r\nContent-Type: text/html\r\n\r\n");
        if(realUser.isNull())
        {
            response.setStatus(error);
            response.setStatusMessage("Wrong login or password");
        }
        else
        {
            response.setStatus(ok);
            response.setStatusMessage("Authorization was successful");
            response.addUser(realUser);
        }

        answer.append(response.getJson());
        syslog(LOG_INFO, "answer: %s", answer.data());
        return answer;
    }






    QByteArray DbObjectsCollection::processAddNewMarkQuery(const QByteArray &data)
    {
        AddNewMarkRequestJSON request;
        AddNewMarkResponseJSON response;
        QByteArray answer("Status: 200 OK\r\nContent-Type: text/html\r\n\r\n");

        request.parseJson(data);
        QSharedPointer<DataMark> dummyTag = request.getTags()->at(0);
        QSharedPointer<User> dummyUser = dummyTag->getUser();
        QSharedPointer<User> realUser = findUserFromToken(dummyUser);

        if(realUser.isNull())//
        {
            response.setStatus(error);
            response.setStatusMessage("Wrong authentification key");
            answer.append(response.getJson());
            return answer;
        }

        QSharedPointer<Channel> dummyChannel = dummyTag->getChannel();
        QSharedPointer<Channel> realChannel; // Null pointer
        QVector<QSharedPointer<Channel> > currentChannels = m_channelsContainer->vector();

        for(int i=0; i<currentChannels.size(); i++)
        {
            if(currentChannels.at(i)->getName() == dummyChannel->getName())
            {
                realChannel = currentChannels.at(i);
            }
        }
        if(realChannel.isNull())
        {
            response.setStatus(error);
            response.setStatusMessage("Wrong channel's' name");
            answer.append(response.getJson());
            return answer;
        }

        dummyTag->setChannel(realChannel);
        dummyTag->setUser(realUser);
        QSharedPointer<DataMark> realTag = m_queryExecutor->insertNewTag(dummyTag);//now
        if(realTag == NULL)
        {
            response.setStatus(error);
            response.setStatusMessage("Internal server error ):");
            answer.append(response.getJson());
            return answer;
        }
        m_updateThread->lockWriting();
        m_tagsContainer->push_back(realTag);       
        m_dataChannelsMap->insert(realChannel, realTag);
        m_updateThread->unlockWriting();

        response.setStatus(ok);
        response.setStatusMessage("Tag has been added");
        answer.append(response.getJson());
        syslog(LOG_INFO, "answer: %s", answer.data());
        return answer;
    }


    QByteArray DbObjectsCollection::processSubscribedChannelsQuery(const QByteArray &data)
    {
        SubscribedChannelsRequestJSON request;
        SubscribedChannelsResponseJSON response;
        QByteArray answer("Status: 200 OK\r\nContent-Type: text/html\r\n\r\n");

        request.parseJson(data);
        QSharedPointer<User> dummyUser = request.getUsers()->at(0);
        QSharedPointer<User> realUser = findUserFromToken(dummyUser);
        if(realUser.isNull())
        {
            response.setStatus("Error");
            response.setStatusMessage("Wrong authentification key");
            answer.append(response.getJson());
            return answer;
        }

        QSharedPointer<Channels> channels = realUser->getSubscribedChannels();
	response.setChannels(channels);
        response.setStatus("Ok");
        //response.setStatusMessage("feed has been generated");
        answer.append(response.getJson());
        syslog(LOG_INFO, "answer: %s", answer.data());
        return answer;
    }



    QByteArray DbObjectsCollection::processRssFeedQuery(const QByteArray &data)
    {
        RSSFeedRequestJSON request;
        QByteArray answer("Status: 200 OK\r\nContent-Type: text/html\r\n\r\n");

        request.parseJson(data);
        QSharedPointer<User> dummyUser = request.getUsers()->at(0);
        QSharedPointer<User> realUser = findUserFromToken(dummyUser);
        if(realUser.isNull())
        {
            RSSFeedResponseJSON response;
            response.setStatus(error);
            response.setStatusMessage("Wrong authentification key");
            answer.append(response.getJson());
            return answer;
        }

        QSharedPointer<Channels> channels = realUser->getSubscribedChannels();
        DataChannels feed;
//        syslog(LOG_INFO, "rssfeed processing: user %s has %d channels subscribed",
//               realUser->getLogin().toStdString().c_str(), channels->size());
        for(int i = 0; i<channels->size(); i++)
        {
            QSharedPointer<Channel> channel = channels->at(i);
            QList<QSharedPointer<DataMark> > tags = m_dataChannelsMap->values(channel);
            qSort(tags);
            QList<QSharedPointer<DataMark> > last10 = tags.mid(tags.size()>10?tags.size()-10:0, 10);
            for(int j = 0; j<last10.size(); j++)
            {
//                syslog(LOG_INFO,"rssfeed: adding tag with time: %s", last10.at(j)->getTime().toString("dd MM yyyy HH:mm:ss.zzz").toStdString().c_str());
                feed.insert(channel, last10.at(j));
            }
        }
        RSSFeedResponseJSON response(feed);
        response.setStatus(ok);
        response.setStatusMessage("feed has been generated");
        answer.append(response.getJson());
        syslog(LOG_INFO, "answer: %s", answer.data());
        return answer;
    }




//TODO create function that will check validity of authkey, and channel name
    QByteArray DbObjectsCollection::processSubscribeQuery(const QByteArray &data)
    {
	syslog(LOG_INFO, "starting SubscribeQuery processing");    
        SubscribeChannelRequestJSON request;
	syslog(LOG_INFO, " SubscribeChannelRequestJSON created, now create SubscribeChannelResponseJSON ");
        SubscribeChannelResponseJSON response;
        QByteArray answer("Status: 200 OK\r\nContent-Type: text/html\r\n\r\n");
        syslog(LOG_INFO, "Starting Json parsing for SubscribeQuery");
        request.parseJson(data);
	syslog(LOG_INFO, "Json parsed for SubscribeQuery");
        QSharedPointer<User> dummyUser = request.getUsers()->at(0);;
        QSharedPointer<User> realUser = findUserFromToken(dummyUser);

        if(realUser.isNull())
        {
            response.setStatus(error);
            response.setStatusMessage("Wrong authentification key");
            answer.append(response.getJson());
            return answer;
        }

        QSharedPointer<Channel> dummyChannel = request.getChannels()->at(0);;

        QSharedPointer<Channel> realChannel; // Null pointer
        QVector<QSharedPointer<Channel> > currentChannels = m_channelsContainer->vector();
        for(int i=0; i<currentChannels.size(); i++)
        {
            if(currentChannels.at(i)->getName() == dummyChannel->getName())
            {
                realChannel = currentChannels.at(i);
            }
        }
        if(realChannel.isNull())
        {
            response.setStatus(error);
            response.setStatusMessage("Wrong channel's' name");
            answer.append(response.getJson());
            return answer;
        }
	syslog(LOG_INFO, "Sending sql request for SubscribeQuery");
        bool result = m_queryExecutor->subscribeChannel(realUser,realChannel);
        if(!result)
        {
            response.setStatus(error);
            response.setStatusMessage("Internal server error ):");
            answer.append(response.getJson());
            return answer;
        }
        m_updateThread->lockWriting();
	realUser->subscribe(dummyChannel);
        m_updateThread->unlockWriting();

        response.setStatus(ok);
        response.setStatusMessage("Channel subscribed");
        answer.append(response.getJson());
        syslog(LOG_INFO, "answer: %s", answer.data());
        return answer;
    }




    QByteArray DbObjectsCollection::processAddUserQuery(const QByteArray &data)
    {
				syslog(LOG_INFO, "starting AddUser processing");    
        AddUserRequestJSON request;
				syslog(LOG_INFO, " AddUserRequestJSON created, now create AddUserResponseJSON ");
        AddUserResponseJSON response;
        QByteArray answer("Status: 200 OK\r\nContent-Type: text/html\r\n\r\n");
        syslog(LOG_INFO, "Starting Json parsing for AddUserQuery");
        request.parseJson(data);
				// Look for user with the same name
        QSharedPointer<User> dummyUser = request.getUsers()->at(0);
        QVector<QSharedPointer<User> > currentUsers = m_usersContainer->vector();
        for(int i=0; i<currentUsers.size(); i++)
        {
            if(currentUsers.at(i)->getLogin() == dummyUser->getLogin())
            {
                    response.setStatus(error);
                    response.setStatusMessage("Username already exists!");
        						answer.append(response.getJson());
        						syslog(LOG_INFO, "answer: %s", answer.data());
						        return answer;
            }
        }

				syslog(LOG_INFO, "Sending sql request for AddUser");
        QSharedPointer<User> addedUser = m_queryExecutor->insertNewUser(dummyUser);
        if(!addedUser)
        {
            response.setStatus(error);
            response.setStatusMessage("Internal server error ):");
            answer.append(response.getJson());
        		syslog(LOG_INFO, "answer: %s", answer.data());
            return answer;
        }
        m_updateThread->lockWriting();
				// Here will be adding user into user container
				m_usersContainer->push_back(addedUser);
        m_updateThread->unlockWriting();

        response.setStatus(ok);
        response.setStatusMessage("User added");
        answer.append(response.getJson());
        syslog(LOG_INFO, "answer: %s", answer.data());
        return answer;

		}





        QByteArray DbObjectsCollection::processAddChannelQuery(const QByteArray &data)
        {
            syslog(LOG_INFO, "starting AddChannelQuery processing");
            AddChannelRequestJSON request;
            syslog(LOG_INFO, " AddChannelRequestJSON created, now create AddChannelResponseJSON ");
            AddChannelResponseJSON response;
            QByteArray answer("Status: 200 OK\r\nContent-Type: text/html\r\n\r\n");
            syslog(LOG_INFO, "Starting Json parsing for AddChannelQuery");
            request.parseJson(data);
            syslog(LOG_INFO, "Json parsed for AddChanenlQuery");
            QSharedPointer<User> dummyUser = request.getUsers()->at(0);
            QSharedPointer<User> realUser = findUserFromToken(dummyUser);

            if(realUser.isNull())
            {
                response.setStatus(error);
                response.setStatusMessage("Wrong authentification key");
                answer.append(response.getJson());
                return answer;
            }

            QSharedPointer<Channel> dummyChannel = request.getChannels()->at(0);
            QSharedPointer<Channel> realChannel; // Null pointer
            QVector<QSharedPointer<Channel> > currentChannels = m_channelsContainer->vector();
            for(int i=0; i<currentChannels.size(); i++)
            {
                if(currentChannels.at(i)->getName() == dummyChannel->getName())
                {
                    realChannel = currentChannels.at(i);
                }
            }

            if(!realChannel.isNull())
            {
                response.setStatus(error);
                response.setStatusMessage("Channel exists!");
                answer.append(response.getJson());
                return answer;
            }

            syslog(LOG_INFO, "Sending sql request for AddChannel");
            QSharedPointer<Channel> addedChannel = m_queryExecutor->insertNewChannel(dummyChannel);
            if(!addedChannel)
            {
                response.setStatus(error);
                response.setStatusMessage("Internal server error ):");
                answer.append(response.getJson());
                syslog(LOG_INFO, "answer: %s", answer.data());
                return answer;
            }

            syslog(LOG_INFO, "Setting default time slot value for the channel");
            if (!defaultTimeSlot.isNull())
                addedChannel->setTimeSlot(defaultTimeSlot);            

            m_updateThread->lockWriting();
            // Here will be adding user into user container
            m_channelsContainer->push_back(addedChannel);
            m_updateThread->unlockWriting();

            response.setStatus(ok);
            response.setStatusMessage("Channel added");
            answer.append(response.getJson());
            syslog(LOG_INFO, "answer: %s", answer.data());
            return answer;
        }







        QByteArray DbObjectsCollection::processGetTimeSlotQuery(const QByteArray &data)
        {
            syslog(LOG_INFO, "starting GetTimeSlotQuery processing");
            GetTimeSlotRequestJSON request;
            syslog(LOG_INFO, " GetTimeSlotRequestJSON created, now create GetTimeSlotResponseJSON ");
            GetTimeSlotResponseJSON response;
            QByteArray answer("Status: 200 OK\r\nContent-Type: text/html\r\n\r\n");
            syslog(LOG_INFO, "Starting Json parsing for GetTimeSlotQuery");
            request.parseJson(data);
            syslog(LOG_INFO, "Json parsed for GetTimeSlotQuery");            

            QSharedPointer<User> dummyUser = request.getUsers()->at(0);
            QSharedPointer<User> realUser = findUserFromToken(dummyUser);

            if(realUser.isNull())
            {
                DefaultResponseJSON response;
                response.setStatus(error);
                response.setStatusMessage("Wrong authentification key");
                answer.append(response.getJson());
                return answer;
            }


            QSharedPointer<Channel> dummyChannel = request.getChannels()->at(0);
            QSharedPointer<Channel> realChannel; // Null pointer
            QVector<QSharedPointer<Channel> > currentChannels = m_channelsContainer->vector();
            for(int i=0; i<currentChannels.size(); i++)
            {
                if(currentChannels.at(i)->getName() == dummyChannel->getName())
                {
                    realChannel = currentChannels.at(i);
                }
            }           
            if(realChannel.isNull())
            {
                DefaultResponseJSON response;
                response.setStatus(error);
                response.setStatusMessage("Wrong channel's' name!");
                answer.append(response.getJson());
                return answer;
            }            

            response.addChannel(realChannel);
            answer.append(response.getJson());
            syslog(LOG_INFO, "answer: %s", answer.data());
            return answer;
        }



        QByteArray DbObjectsCollection::processSetTimeSlotQuery(const QByteArray &data)
        {
            syslog(LOG_INFO, "starting SetTimeSlotQuery processing");
            SetTimeSlotRequestJSON request;
            syslog(LOG_INFO, " SetTimeSlotRequestJSON created, now create SetTimeSlotResponseJSON ");
            SetTimeSlotResponseJSON response;
            QByteArray answer("Status: 200 OK\r\nContent-Type: text/html\r\n\r\n");
            syslog(LOG_INFO, "Starting Json parsing for SetTimeSlotQuery");
            request.parseJson(data);
            syslog(LOG_INFO, "Json parsed for SetTimeSlotQuery");

            QSharedPointer<User> dummyUser = request.getUsers()->at(0);
            QSharedPointer<User> realUser = findUserFromToken(dummyUser);

            if(realUser.isNull())
            {                
                response.setStatus(error);
                response.setStatusMessage("Wrong authentification key");
                answer.append(response.getJson());
                return answer;
            }


            QSharedPointer<Channel> dummyChannel = request.getChannels()->at(0);
            QSharedPointer<Channel> realChannel; // Null pointer
            QVector<QSharedPointer<Channel> > currentChannels = m_channelsContainer->vector();
            for(int i=0; i<currentChannels.size(); i++)
            {
                if(currentChannels.at(i)->getName() == dummyChannel->getName())
                {
                    realChannel = currentChannels.at(i);
                }
            }

            if(realChannel.isNull())
            {                
                response.setStatus(error);
                response.setStatusMessage("Wrong channel's' name!");
                answer.append(response.getJson());
                return answer;
            }


            syslog(LOG_INFO, "Sending sql request for SetTimeSlot");

            QSharedPointer<TimeSlot> dummyTimeSlot = dummyChannel->getTimeSlot();
            if (!dummyTimeSlot->getSlot())
            {
                response.setStatus(error);
                response.setStatusMessage("Time slot can't be a null");
                answer.append(response.getJson());
                return answer;
            }

            QSharedPointer<TimeSlot> realTimeSlot; // Null pointer
            QVector<QSharedPointer<TimeSlot> > currentTimeSlots = m_timeSlotsContainer->vector();
            for(int i=0; i<currentTimeSlots.size(); i++)
            {
                if(currentTimeSlots.at(i)->getSlot() == dummyTimeSlot->getSlot())
                {
                    realTimeSlot = currentTimeSlots.at(i);
                }
            }            

            bool realTimeSlotIsNull = false;            
            QSharedPointer<TimeSlot> addedTimeSlot;

            if (realTimeSlot.isNull())
            {
                realTimeSlotIsNull = true;
                addedTimeSlot = m_queryExecutor->insertNewTimeSlot(dummyTimeSlot);
                if(!addedTimeSlot)
                {                    
                    response.setStatus("Error");
                    response.setStatusMessage("Internal server error ):");
                    answer.append(response.getJson());
                    syslog(LOG_INFO, "answer: %s", answer.data());
                    return answer;
                }
                m_updateThread->lockWriting();
                m_timeSlotsContainer->push_back(addedTimeSlot);
                m_updateThread->unlockWriting();
            }             

            bool result;
            if (realChannel->getTimeSlot()->getSlot() == defaultTimeSlot->getSlot())
            {
                if (realTimeSlotIsNull)
                    result = m_queryExecutor->insertNewChannelTimeSlot(realChannel, addedTimeSlot);
                else if (realTimeSlot->getSlot() != defaultTimeSlot->getSlot())
                    result = m_queryExecutor->insertNewChannelTimeSlot(realChannel, realTimeSlot);
            }
            else
            {
                if (realTimeSlotIsNull)
                    result = m_queryExecutor->changeChannelTimeSlot(realChannel, addedTimeSlot);
                else
                    result = m_queryExecutor->changeChannelTimeSlot(realChannel, realTimeSlot);
            }

            if(!result)
            {
                response.setStatus(error);
                response.setStatusMessage("Internal server error ):");
                answer.append(response.getJson());
                return answer;
            }
            m_updateThread->lockWriting();
            if (realTimeSlotIsNull)
                realChannel->setTimeSlot(addedTimeSlot);
            else
                realChannel->setTimeSlot(realTimeSlot);
            m_updateThread->unlockWriting();

            response.setStatus(ok);
            response.setStatusMessage("Time slot for channel is set");
            answer.append(response.getJson());
            syslog(LOG_INFO, "answer: %s", answer.data());
            return answer;

        }
        //QByteArray DbObjectsCollection::processGetChannelActionsQuery(const QByteArray &data)
        //{

        //}
} // namespace common

/* ===[ End of file ]=== */
