/*
 * Copyright 2010  Open Source & Linux Lab (OSLL)  osll@osll.spb.ru
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

/* $Id$ */
/*!
 * \file UnsubscribeChannelQuery.h
 * \brief Header of UnsubscribeChannelQuery
 * \todo add comment here
 *
 * File description
 *
 * PROJ: geo2tag
 * ---------------------------------------------------------------- */


#ifndef _UnsubscribeChannelQuery_H_AEC54E51_233A_4854_90B8_F70C8DAAF3ED_INCLUDED_
#define _UnsubscribeChannelQuery_H_AEC54E51_233A_4854_90B8_F70C8DAAF3ED_INCLUDED_

#include <QObject>
#include <QString>
#include <QNetworkAccessManager>
#include <QNetworkReply>

#include "Channel.h"

namespace GUI
{
    /*!
     * UnsubscribeChannelQuery class definition.
     *
     * The object of this class represents http query to server.
     * This query includes json request to Unsubscribe channel.
     *
     */
    class UnsubscribeChannelQuery: public QObject
    {
        Q_OBJECT

    private:
        QNetworkAccessManager *manager;

        /* Url of th request */
        QString httpQuery;

        /* Body of the request */
        QString jsonQuery;

    public:

        UnsubscribeChannelQuery(QObject *parent = 0);

        UnsubscribeChannelQuery(QString auth_token, QString channel, QObject *parent = 0);

        void setQuery(QString auth_token, QString channel);

        ~UnsubscribeChannelQuery();

        const QString& getHttpQuery();
        const QString& getJsonQuery();

        void doRequest();

    signals:
        void responseReceived(QString status);

    private slots:
        void onManagerFinished(QNetworkReply *reply);
        void onReplyError(QNetworkReply::NetworkError);
        void onManagerSslErrors();

    private:
        /* \todo Do we need next constructor and overloaded operator? */
        UnsubscribeChannelQuery(const UnsubscribeChannelQuery& obj);
        UnsubscribeChannelQuery& operator=(const UnsubscribeChannelQuery& obj);

    }; // class UnsubscribeChannelQuery

} // namespace GUI

#endif //_UnsubscribeChannelQuery_H_AEC54E51_233A_4854_90B8_F70C8DAAF3ED_INCLUDED_

/* ===[ End of file $HeadURL$ ]=== */