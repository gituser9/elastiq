#ifndef APP_STRUCT_H
#define APP_STRUCT_H

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

struct ElasticRecord
{
    QString id;
    QString type;
    QString index;
    QString source;

    ElasticRecord()
    {
        id = 0;
        type = "";
        index = "";
        source = "";
    }

    ElasticRecord(QJsonObject &jsonObject)
    {
        id = jsonObject["_id"].toString();
        type = jsonObject["_type"].toString();
        index = jsonObject["_index"].toString();
        source = QJsonDocument(jsonObject["_source"].toObject()).toJson(QJsonDocument::Indented);
    }
};

struct KeyValueFilter
{
    QString key;
    QVariant value;
};

struct ElasticFilter
{
    KeyValueFilter match;
    KeyValueFilter term;
    int size;
    QStringList source;

    QString toString(QJsonDocument::JsonFormat format) const
    {
        QJsonObject json;

        if (!match.key.isEmpty()) {
            json[match.key] = QJsonValue::fromVariant(match.value);
        }

        if (!term.key.isEmpty()) {
            json[term.key] = QJsonValue::fromVariant(term.value);
        }

        if (size != 0) {
            json["size"] = size;
        }

        if (!source.isEmpty()) {
            json["_source"] = QJsonArray::fromStringList(source);
        }

        QJsonDocument doc(json);

        return doc.toJson(format);
    }
};

#endif // APP_STRUCT_H
