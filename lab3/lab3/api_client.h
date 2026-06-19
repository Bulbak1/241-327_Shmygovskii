#pragma once
#include "pen.h"
#include "ipen_adapter.h"
#include <QObject>
#include <QNetworkAccessManager>
#include <QJsonObject>
#include <QList>


class ApiClient : public QObject {
    Q_OBJECT
public:
    static ApiClient &instance();

    void fetchPens();
    void fetchPen(int id);
    void createPen(const QJsonObject &data);
    void updatePen(int id, const QJsonObject &data);
    void deletePen(int id);

signals:
    void pensReceived(QList<Pen> pens);
    void penReceived(Pen pen);
    void penCreated(Pen pen);
    void penUpdated(Pen pen);
    void penDeleted(QString message);
    void errorOccurred(QString error);

private:
    explicit ApiClient(QObject *parent = nullptr);
    ~ApiClient() override;
    ApiClient(const ApiClient &)            = delete;
    ApiClient &operator=(const ApiClient &) = delete;

    QNetworkAccessManager *m_manager;
    IPenAdapter           *m_adapter;
    QString                m_baseUrl;
};
