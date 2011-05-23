
#include <qjson/parser.h>
#include <qjson/serializer.h>

#include "GetSessionPointResponseJSON.h"
#include "JsonSession.h"

GetSessionPointResponseJSON::GetSessionPointResponseJSON(QObject *parent) : JsonSerializer(parent)
{
}


void GetSessionPointResponseJSON::parseJson(const QByteArray &data)
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

  double latitude = result["latitude"].toDouble();
  double longitude= result["longitude"].toDouble();
  double radius= result["radius"].toDouble();
  qulonglong timeSlot = result["timeSlot"].toULongLong();
  QDateTime time = QDateTime::fromString(result["time"].toString(), "dd MM yyyy HH:mm:ss.zzz");

  m_sessionsContainer->push_back(QSharedPointer<Session>(new JsonSession(latitude,longitude,radius, timeSlot, 0, time)));
}


QByteArray GetSessionPointResponseJSON::getJson() const
{
  QJson::Serializer serializer;
  QVariantMap obj;

  QSharedPointer<Session> session = m_sessionsContainer->at(0);

  obj.insert("latitude", session->getLatitude());
  obj.insert("longitude", session->getLongitude());
  obj.insert("radius", session->getRadius());
  obj.insert("timeSlot", session->getTimeSlot());
  obj.insert("time", session->getTime());

  return serializer.serialize(obj);
}
