#pragma once
#include "pen.h"
#include <QMainWindow>
#include <QList>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void on_btnList_clicked();
    void on_btnGet_clicked();
    void on_btnCreate_clicked();
    void on_btnUpdate_clicked();
    void on_btnDelete_clicked();

    void onPensReceived(const QList<Pen> &pens);
    void onPenReceived(const Pen &pen);
    void onPenCreated(const Pen &pen);
    void onPenUpdated(const Pen &pen);
    void onPenDeleted(const QString &message);
    void onError(const QString &error);

    void onPenLoadedForUpdate(const Pen &pen);

private:
    void appendPen(const Pen &p);
    int m_pendingUpdateId = 0;
    Ui::MainWindow *ui;
};

