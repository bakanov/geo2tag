#include <qjson/parser.h>
#include <qjson/serializer.h>

#include <QDebug>

#include "LoginResponseJSON.h"
#include "JsonUser.h"

LoginResponseJSON::LoginResponseJSON(QObject *parent) : JsonSerializer(parent)
{
}


QByteArray LoginResponseJSON::getJson() const
{
  QJson::Serializer serializer;
  QVariantMap obj;
  //  if(m_usersContainer->size()>0)
  //    obj.insert("auth_token", m_usersContainer->at(0)->getToken());
  obj.insert("auth_token", m_token);
  obj.insert("status", m_status);
  obj.insert("status_description", m_statusMessage);
  return serializer.serialize(obj);
}


void LoginResponseJSON::parseJson(const QByteArray &data)
{
  clearContainers();

  QJson::Parser parser;
  bool ok;

  QVariantMap result = parser.parse(data, &ok).toMap();
  if (!ok)
  {
    qFatal("An error occured during parsing json with channel list");
  }

  m_status = result["status"].toString();
  m_statusMessage = result["status_description"].toString();
  m_token = result["auth_token"].toString();

  //  QString auth_token = result["auth_token"].toString();
  //  QSharedPointer<User> user(new JsonUser("unknown", "unknown", auth_token));
  //  m_usersContainer->push_back(user);
}
