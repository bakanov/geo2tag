#ifndef JSONSERIALIZER_H
#define JSONSERIALIZER_H

#include <QByteArray>
#include <QObject>
#include <QVariantMap>
#include "DataMarks.h"
#include "Channel.h"
#include "User.h"
#include "TimeSlot.h"
#include "Session.h"

class JsonSerializer:public QObject
{

  protected:
    QSharedPointer<Channels>    m_channelsContainer;
    QSharedPointer<DataMarks>   m_tagsContainer;
    QSharedPointer<Users>       m_usersContainer;
    QSharedPointer<Sessions>    m_sessionsContainer;

    QVariantMap m_jsonTree;

    QString m_status;
    QString m_statusMessage;

    QString m_token;

    void clearContainers();
  public:
    JsonSerializer(QObject * parent=0);

    void addChannel(const QSharedPointer<Channel>&);
    void addTag(const QSharedPointer<DataMark>&);
    void addUser(const QSharedPointer<User>&);
    void addSession(const QSharedPointer<Session>&);

    virtual QByteArray getJson() const = 0;

    virtual void parseJson(const QByteArray&) = 0;

    QSharedPointer<DataMarks> getTags() const;
    QSharedPointer<Users> getUsers() const;
    QSharedPointer<Channels> getChannels() const;
    QSharedPointer<Sessions> getSessions() const;

    const QString& getStatus() const;
    void setStatus(const QString&);

    const QString& getStatusMessage() const;
    void setStatusMessage(const QString&);

    const QString& getAuthToken() const;
    void setAuthToken(const QString&);

    ~JsonSerializer();
};
// JSONSERIALIZER_H
#endif
