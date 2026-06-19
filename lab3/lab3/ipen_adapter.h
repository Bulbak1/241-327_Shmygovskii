#pragma once
#include "pen.h"
#include <QJsonObject>
#include <QJsonArray>
#include <QList>


class IPenAdapter {
public:
    virtual ~IPenAdapter() = default;
    virtual Pen        toPen    (const QJsonObject &json) const = 0;
    virtual QList<Pen> toPenList(const QJsonArray  &json) const = 0;
};
