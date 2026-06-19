#include "create_pen_dialog.h"
#include <QFormLayout>
#include <QVBoxLayout>
#include <QDialogButtonBox>
#include <QLineEdit>
#include <QComboBox>
#include <QDoubleSpinBox>
#include <QSpinBox>
#include <QDate>

CreatePenDialog::CreatePenDialog(QWidget *parent)
    : QDialog(parent)
{
    setMinimumWidth(360);

    m_name        = new QLineEdit(this);
    m_price       = new QDoubleSpinBox(this);
    m_quantity    = new QSpinBox(this);
    m_weight      = new QDoubleSpinBox(this);
    m_createdAt   = new QLineEdit(this);
    m_description = new QLineEdit(this);
    m_sku         = new QLineEdit(this);
    m_penType     = new QComboBox(this);

    m_price->setRange(0.0, 99999.99);
    m_price->setDecimals(2);
    m_quantity->setRange(0, 9999);
    m_weight->setRange(0.0, 9999.99);
    m_weight->setDecimals(2);
    m_createdAt->setText(QDate::currentDate().toString("yyyy-MM-dd"));
    m_penType->addItems({"ballpoint", "gel", "fountain", "roller"});

    auto *form = new QFormLayout();
    form->addRow("Название:",   m_name);
    form->addRow("Цена:",       m_price);
    form->addRow("Количество:", m_quantity);
    form->addRow("Вес:",        m_weight);
    form->addRow("Дата (created_at):", m_createdAt);
    form->addRow("Описание:",   m_description);
    form->addRow("SKU:",        m_sku);
    form->addRow("Тип:",        m_penType);

    auto *buttons = new QDialogButtonBox(
        QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    connect(buttons, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttons, &QDialogButtonBox::rejected, this, &QDialog::reject);

    auto *layout = new QVBoxLayout(this);
    layout->addLayout(form);
    layout->addWidget(buttons);
}

QJsonObject CreatePenDialog::penData() const
{
    QJsonObject obj;
    obj["name"]        = m_name->text();
    obj["price"]       = m_price->value();
    obj["quantity"]    = m_quantity->value();
    obj["weight"]      = m_weight->value();
    obj["created_at"] = m_createdAt->text().isEmpty()
                            ? QDate::currentDate().toString("yyyy-MM-dd")
                            : m_createdAt->text();
    obj["description"] = m_description->text();
    obj["sku"]         = m_sku->text();
    obj["pen_type"]    = m_penType->currentText();
    return obj;
}

void CreatePenDialog::fillFrom(const Pen &p)
{
    m_name->setText(p.name);
    m_price->setValue(p.price);
    m_quantity->setValue(p.quantity);
    m_weight->setValue(p.weight);
    m_createdAt->setText(p.createdAt);
    m_description->setText(p.description);
    m_sku->setText(p.sku);
    int idx = m_penType->findText(p.penType);
    if (idx >= 0) m_penType->setCurrentIndex(idx);
}
