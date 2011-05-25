
#include "LoginRequestJSON.h"
#include "JsonUser.h"

#if !defined(Q_OS_SYMBIAN) && !defined(MAEMO_OS)
#include <qjson/parser.h>
#include <qjson/serializer.h>
#else
#include "parser.h"
#include "serializer.h"
#endif

LoginRequestJSON::LoginRequestJSON(QObject *parent) : JsonSerializer(parent)
{
}


QByteArray LoginRequestJSON::getJson() const
{
  QJson::Serializer serializer;
  QVariantMap obj;
  obj.insert("login", m_usersContainer->at(0)->getLogin());
  obj.insert("password", m_usersContainer->at(0)->getPassword());
  return serializer.serialize(obj);
}


void LoginRequestJSON::parseJson(const QByteArray&data)
{
  clearContainers();

  QJson::Parser parser;
  bool ok;
  QVariantMap result = parser.parse(data, &ok).toMap();
  if (!ok)
  {
    qFatal("An error occured during parsing json with channel list");
  }
  QString login = result["login"].toString();
  QString password = result["password"].toString();
  m_usersContainer->push_back(QSharedPointer<common::User>(new JsonUser(login,password)));
}
