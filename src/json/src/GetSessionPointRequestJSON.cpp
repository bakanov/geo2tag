#include <qjson/parser.h>
#include <qjson/serializer.h>

#include "GetSessionPointRequestJSON.h"
#include "JsonUser.h"

GetSessionPointRequestJSON::GetSessionPointRequestJSON(QObject *parent) : JsonSerializer(parent)
{
}


void GetSessionPointRequestJSON::parseJson(const QByteArray &data)
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
}


QByteArray GetSessionPointRequestJSON::getJson() const
{
  QJson::Serializer serializer;
  QVariantMap obj;

  obj.insert("auth_token", m_token);

  return serializer.serialize(obj);
}
