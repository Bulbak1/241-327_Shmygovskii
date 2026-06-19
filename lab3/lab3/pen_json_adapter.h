#ifndef PEN_JSON_ADAPTER_H
#define PEN_JSON_ADAPTER_H

#include "ipen_adapter.h"

class PenJsonAdapter : public IPenAdapter {
public:
    Pen        toPen    (const QJsonObject &json) const override;
    QList<Pen> toPenList(const QJsonArray  &json) const override;
};


#endif // PEN_JSON_ADAPTER_H
