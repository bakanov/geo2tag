#include <qjson/parser.h>
#include <qjson/serializer.h>

#include <QDebug>

#include "AddNewMarkResponseJSON.h"
#include "JsonDataMark.h"
#include "DataMarks.h"

AddNewMarkResponseJSON::AddNewMarkResponseJSON(QObject *parent) : JsonSerializer(parent)
{
}

QByteArray AddNewMarkResponseJSON::getJson() const
{
    QJson::Serializer serializer;
    QVariantMap obj;

    QSharedPointer<DataMark> mark = m_tagsContainer->at(0);

    obj.insert("status", m_status);
    obj.insert("status_description", m_statusMessage);
    obj.insert("mark_id", mark->getId());
    return serializer.serialize(obj);
}

void AddNewMarkResponseJSON::parseJson(const QByteArray &data)
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

    qlonglong markId = result["timeSlot"].toLongLong();
    JsonDataMark* jsonMark = new JsonDataMark(0,0,"unknown", "unknown", "unknown", QDateTime());
    jsonMark->setId(markId);
    QSharedPointer<DataMark> mark(jsonMark);
    m_tagsContainer->push_back(mark);
}


