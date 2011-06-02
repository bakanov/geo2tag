#include <qjson/parser.h>
#include <qjson/serializer.h>

#include "SetSessionPointRequestJSON.h"
#include "JsonSession.h"

SetSessionPointRequestJSON::SetSessionPointRequestJSON(QObject *parent) : JsonSerializer(parent)
{
}


void SetSessionPointRequestJSON::parseJson(const QByteArray &data)
{
  clearContainers();

  QJson::Parser parser;
  bool ok;
  QVariantMap result = parser.parse(data, &ok).toMap();

  if (!ok)
  {
    qFatal("An error occured during parsing json with rss request");
    return;
  }

  m_token = result["auth_token"].toString();

  double latitude = result["latitude"].toDouble();
  double longitude = result["longitude"].toDouble();
  double radius = result["radius"].toDouble();
  qulonglong timeSlot = result["timeSlot"].toULongLong();
  bool isCurrentTime = result["isCurrentTime"].toBool();
  QDateTime time = QDateTime::fromString(result["time"].toString(), "dd MM yyyy HH:mm:ss.zzz");

  m_sessionsContainer->push_back(QSharedPointer<Session>(new JsonSession(latitude,longitude,radius, timeSlot, isCurrentTime, time)));

}


QByteArray SetSessionPointRequestJSON::getJson() const
{
  QJson::Serializer serializer;
  QVariantMap obj;

  QSharedPointer<Session> session = m_sessionsContainer->at(0);

  obj.insert("latitude", session->getLatitude());
  obj.insert("longitude", session->getLongitude());
  obj.insert("radius", session->getRadius());
  obj.insert("timeSlot", session->getTimeSlot());
  obj.insert("isCurrentTime", session->getIsTimeCurrent());
  obj.insert("time", session->getTime());

  return serializer.serialize(obj);
}
