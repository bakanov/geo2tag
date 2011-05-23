#ifndef LOGINREQUESTJSON_H
#define LOGINREQUESTJSON_H
#include "JsonSerializer.h"

class LoginRequestJSON: public JsonSerializer
{
  Q_OBJECT;
  public:
    LoginRequestJSON(QObject *parent=0);

    QByteArray getJson() const;

    void parseJson(const QByteArray&);
};
// LOGINREQUESTJSON_H
#endif
