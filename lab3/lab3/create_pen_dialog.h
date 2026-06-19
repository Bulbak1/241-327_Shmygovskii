#pragma once
#include "pen.h"
#include <QDialog>
#include <QJsonObject>


QT_FORWARD_DECLARE_CLASS(QLineEdit)
QT_FORWARD_DECLARE_CLASS(QComboBox)
QT_FORWARD_DECLARE_CLASS(QDoubleSpinBox)
QT_FORWARD_DECLARE_CLASS(QSpinBox)

class CreatePenDialog : public QDialog
{
    Q_OBJECT
public:
    explicit CreatePenDialog(QWidget *parent = nullptr);
    QJsonObject penData() const;
    void fillFrom(const Pen &p);
private:
    QLineEdit      *m_name;
    QDoubleSpinBox *m_price;
    QSpinBox       *m_quantity;
    QDoubleSpinBox *m_weight;
    QLineEdit      *m_createdAt;
    QLineEdit      *m_description;
    QLineEdit      *m_sku;
    QComboBox      *m_penType;
};


