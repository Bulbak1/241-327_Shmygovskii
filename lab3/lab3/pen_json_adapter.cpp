#include "pen_json_adapter.h"
#include <QJsonValue>

Pen PenJsonAdapter::toPen(const QJsonObject &json) const
{
    Pen p;
    p.id          = json["id"].toInt();
    p.name        = json["name"].toString();
    p.price       = json["price"].toString().toDouble(); // Django возвращает decimal как строку
    p.quantity    = json["quantity"].toInt();
    p.weight      = json["weight"].toDouble();
    p.createdAt   = json["created_at"].toString();
    p.description = json["description"].toString();
    p.sku         = json["sku"].toString();
    p.penType     = json["pen_type"].toString();
    return p;
}

QList<Pen> PenJsonAdapter::toPenList(const QJsonArray &json) const
{
    QList<Pen> list;
    list.reserve(json.size());
    for (const QJsonValue &value : json) {
        if (value.isObject())
            list.append(toPen(value.toObject()));
    }
    return list;
}
