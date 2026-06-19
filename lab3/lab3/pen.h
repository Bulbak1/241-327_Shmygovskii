#pragma once
#include <QString>

class Pen {
public:
    Pen() = default;

    int     id = 0;
    QString name;
    double  price = 0.0;
    int     quantity = 0;
    double  weight = 0.0;
    QString createdAt;
    QString description;
    QString sku;
    QString penType;
};
