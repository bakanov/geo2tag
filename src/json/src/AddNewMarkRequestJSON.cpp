#include <qjson/parser.h>
#include <qjson/serializer.h>

#include "AddNewMarkRequestJSON.h"
#include "DataMarks.h"
#include "JsonChannel.h"
#include "JsonDataMark.h"
#include "JsonUser.h"

AddNewMarkRequestJSON::AddNewMarkRequestJSON(QObject *parent) : JsonSerializer(parent)
{
}


void AddNewMarkRequestJSON::parseJson(const QByteArray &data)
{
  clearContainers();
  QJson::Parser parser;
  bool ok;
  QVariantMap result = parser.parse(data, &ok).toMap();
  if (!ok)
  {
    qFatal("An error occured during parsing json with channel list");
    return;
  }

  m_token = result["auth_token"].toString();
  QString channel_name = result["channel"].toString();
  QString title = result["title"].toString();
  QString link = result["link"].toString();
  QString description = result["description"].toString();
  double longitude = result["longitude"].toDouble();
  double latitude = result["latitude"].toDouble();
  QDateTime time = QDateTime::fromString(result["time"].toString(), "dd MM yyyy HH:mm:ss.zzz");

  QSharedPointer<Channel> channel(new JsonChannel(channel_name, "unknown"));
  QSharedPointer<DataMark> tag(new JsonDataMark(latitude, longitude, title, description, link, time));
  tag->setChannel(channel);
  m_tagsContainer->push_back(tag);
}


QByteArray AddNewMarkRequestJSON::getJson() const
{
  QJson::Serializer serializer;
  QVariantMap request;
  QSharedPointer<DataMark> mark = m_tagsContainer->at(0);
  request.insert("auth_token", m_token);
  request.insert("channel", mark->getChannel()->getName());
  request.insert("title", mark->getLabel().isEmpty()? "New mark":mark->getLabel());
  request.insert("link", mark->getUrl());
  request.insert("description", mark->getDescription());
  request.insert("latitude", mark->getLatitude());
  request.insert("longitude", mark->getLongitude());
  request.insert("time", mark->getTime().toString("dd MM yyyy HH:mm:ss.zzz"));
  return serializer.serialize(request);
}
