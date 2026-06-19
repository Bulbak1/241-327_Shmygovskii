#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "api_client.h"
#include "create_pen_dialog.h"
#include <QInputDialog>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ApiClient &client = ApiClient::instance();
    connect(&client, &ApiClient::pensReceived,  this, &MainWindow::onPensReceived);
    connect(&client, &ApiClient::penReceived,   this, &MainWindow::onPenReceived);
    connect(&client, &ApiClient::penCreated,    this, &MainWindow::onPenCreated);
    connect(&client, &ApiClient::penUpdated,    this, &MainWindow::onPenUpdated);
    connect(&client, &ApiClient::penDeleted,    this, &MainWindow::onPenDeleted);
    connect(&client, &ApiClient::errorOccurred, this, &MainWindow::onError);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Кнопки-------------------------------------------------

void MainWindow::on_btnList_clicked()
{
    ui->outputEdit->clear();
    ApiClient::instance().fetchPens();
}

void MainWindow::on_btnGet_clicked()
{
    bool ok;
    int id = QInputDialog::getInt(this, "Get by ID", "ID ручки:", 1, 1, 99999, 1, &ok);
    if (!ok) return;
    ui->outputEdit->clear();
    ApiClient::instance().fetchPen(id);
}

void MainWindow::on_btnCreate_clicked()
{
    CreatePenDialog dlg(this);
    dlg.setWindowTitle("Создать ручку — POST /api/pens/");
    if (dlg.exec() != QDialog::Accepted) return;
    ui->outputEdit->clear();
    ApiClient::instance().createPen(dlg.penData());
}

void MainWindow::on_btnUpdate_clicked()
{
    bool ok;
    int id = QInputDialog::getInt(this, "Update", "ID ручки:", 1, 1, 99999, 1, &ok);
    if (!ok) return;
    m_pendingUpdateId = id;

    // временно переключаем сигнал penReceived на update слот
    disconnect(&ApiClient::instance(), &ApiClient::penReceived,
               this, &MainWindow::onPenReceived);
    connect(&ApiClient::instance(), &ApiClient::penReceived,
            this, &MainWindow::onPenLoadedForUpdate);

    ApiClient::instance().fetchPen(id);
}

void MainWindow::onPenLoadedForUpdate(const Pen &pen)
{
    // восстанавливаем нормальный слот
    disconnect(&ApiClient::instance(), &ApiClient::penReceived,
               this, &MainWindow::onPenLoadedForUpdate);
    connect(&ApiClient::instance(), &ApiClient::penReceived,
            this, &MainWindow::onPenReceived);

    CreatePenDialog dlg(this);
    dlg.setWindowTitle(QString("Обновить ID=%1 — PUT /api/pens/%1/").arg(m_pendingUpdateId));
    dlg.fillFrom(pen);
    if (dlg.exec() != QDialog::Accepted) return;
    ui->outputEdit->clear();
    ApiClient::instance().updatePen(m_pendingUpdateId, dlg.penData());
}

void MainWindow::on_btnDelete_clicked()
{
    bool ok;
    int id = QInputDialog::getInt(this, "Delete", "ID ручки:", 1, 1, 99999, 1, &ok);
    if (!ok) return;
    ui->outputEdit->clear();
    ApiClient::instance().deletePen(id);
}

// Слоты ответов ---------------------------------------------------

void MainWindow::onPensReceived(const QList<Pen> &pens)
{
    ui->outputEdit->append(QString("<b>Получено ручек: %1</b>").arg(pens.size()));
    for (const Pen &p : pens) {
        ui->outputEdit->append("─────────────────────────");
        appendPen(p);
        qDebug() << "[GET ALL] id:" << p.id << p.name << p.sku;
    }
}

void MainWindow::onPenReceived(const Pen &p)
{
    ui->outputEdit->append("<b>GET by ID</b>");
    ui->outputEdit->append("─────────────────────────");
    appendPen(p);
    qDebug() << "[GET] id:" << p.id << p.name;
}

void MainWindow::onPenCreated(const Pen &p)
{
    ui->outputEdit->append("<b>POST — создана</b>");
    ui->outputEdit->append("─────────────────────────");
    appendPen(p);
    qDebug() << "[CREATE] id:" << p.id << p.name;
}

void MainWindow::onPenUpdated(const Pen &p)
{
    ui->outputEdit->append("<b>PUT — обновлена</b>");
    ui->outputEdit->append("─────────────────────────");
    appendPen(p);
    qDebug() << "[UPDATE] id:" << p.id << p.name;
}

void MainWindow::onPenDeleted(const QString &message)
{
    ui->outputEdit->append("<b>DELETE — успешно</b>");
    ui->outputEdit->append(message);
    qDebug() << "[DELETE]" << message;
}

void MainWindow::onError(const QString &error)
{
    ui->outputEdit->append(
        QString("<span style='color:red'><b>Ошибка:</b> %1</span>").arg(error));
    qDebug() << "[ERROR]" << error;
}

// -------------------------------------------------------

void MainWindow::appendPen(const Pen &p)
{
    ui->outputEdit->append(QString(
                               "ID:          %1\n"
                               "Название:    %2\n"
                               "Тип:         %3\n"
                               "SKU:         %4\n"
                               "Цена:        %5\n"
                               "Количество:  %6\n"
                               "Вес:         %7\n"
                               "Дата:        %8\n"
                               "Описание:    %9"
                               ).arg(p.id)
                               .arg(p.name, p.penType, p.sku)
                               .arg(p.price, 0, 'f', 2)
                               .arg(p.quantity)
                               .arg(p.weight, 0, 'f', 2)
                               .arg(p.createdAt, p.description));
}

