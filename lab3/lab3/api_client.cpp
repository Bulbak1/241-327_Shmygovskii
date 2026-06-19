#include "api_client.h"
#include "pen_json_adapter.h"
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QJsonArray>
#include <QDebug>

ApiClient &ApiClient::instance()
{
    static ApiClient s_instance;
    return s_instance;
}

ApiClient::ApiClient(QObject *parent)
    : QObject(parent)
    , m_manager(new QNetworkAccessManager(this))
    , m_adapter(new PenJsonAdapter())
    , m_baseUrl("http://localhost:80")
{}

ApiClient::~ApiClient() { delete m_adapter; }

// GET /api/pens/
void ApiClient::fetchPens()
{
    QNetworkRequest req(QUrl(m_baseUrl + "/api/pens/"));
    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QNetworkReply *reply = m_manager->get(req);
    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        reply->deleteLater();
        if (reply->error() != QNetworkReply::NoError) { emit errorOccurred(reply->errorString()); return; }
        QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
        if (!doc.isArray()) { emit errorOccurred("Expected JSON array"); return; }
        emit pensReceived(m_adapter->toPenList(doc.array()));
    });
}

// GET /api/pens/:id/
void ApiClient::fetchPen(int id)
{
    QNetworkRequest req(QUrl(m_baseUrl + "/api/pens/" + QString::number(id) + "/"));
    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QNetworkReply *reply = m_manager->get(req);
    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        reply->deleteLater();
        if (reply->error() != QNetworkReply::NoError) { emit errorOccurred(reply->errorString()); return; }
        QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
        if (!doc.isObject()) { emit errorOccurred("Expected JSON object"); return; }
        emit penReceived(m_adapter->toPen(doc.object()));
    });
}

// POST /api/pens/
void ApiClient::createPen(const QJsonObject &data)
{
    QNetworkRequest req(QUrl(m_baseUrl + "/api/pens/"));
    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QNetworkReply *reply = m_manager->post(req, QJsonDocument(data).toJson(QJsonDocument::Compact));
    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        reply->deleteLater();
        if (reply->error() != QNetworkReply::NoError) { emit errorOccurred(reply->errorString()); return; }
        QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
        if (!doc.isObject()) { emit errorOccurred("POST: unexpected format"); return; }
        emit penCreated(m_adapter->toPen(doc.object()));
    });
}

// PUT /api/pens/:id/
void ApiClient::updatePen(int id, const QJsonObject &data)
{
    QNetworkRequest req(QUrl(m_baseUrl + "/api/pens/" + QString::number(id) + "/"));
    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QNetworkReply *reply = m_manager->put(req, QJsonDocument(data).toJson(QJsonDocument::Compact));
    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        reply->deleteLater();
        if (reply->error() != QNetworkReply::NoError) { emit errorOccurred(reply->errorString()); return; }
        QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
        if (!doc.isObject()) { emit errorOccurred("PUT: unexpected format"); return; }
        emit penUpdated(m_adapter->toPen(doc.object()));
    });
}

// DELETE /api/pens/:id/
void ApiClient::deletePen(int id)
{
    QNetworkRequest req(QUrl(m_baseUrl + "/api/pens/" + QString::number(id) + "/"));
    QNetworkReply *reply = m_manager->deleteResource(req);
    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        reply->deleteLater();
        if (reply->error() != QNetworkReply::NoError) { emit errorOccurred(reply->errorString()); return; }
        emit penDeleted("Ручка удалена");
    });
}
