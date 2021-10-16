#include "httpservice.h"

#include <QDebug>

HttpService::HttpService(QObject *parent) : QObject(parent)
{
    _manager = new QNetworkAccessManager(this);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    connect(_manager, &QNetworkAccessManager::finished, this, &HttpService::replyFinished);
}

void HttpService::getByFilters(QString jsonFilters)
{
    _currentOp = HttpOp::GetByFilters;

    request.setUrl(QUrl(_rootUrl + "/_search"));
    _reply = _manager->post(request, jsonFilters.toUtf8());
}

void HttpService::getById(QString id)
{
    _currentOp = HttpOp::GetById;

    request.setUrl(QUrl(_rootUrl + "/_doc/" + id));
    _reply = _manager->get(request);
}

const QString &HttpService::rootUrl() const
{
    return _rootUrl;
}

void HttpService::setRootUrl(const QString &newRootUrl)
{
    QString connectUrl = newRootUrl;

    if (!connectUrl.startsWith("http://") && !connectUrl.startsWith("https://")) {
        connectUrl = "http://" + connectUrl;
    }

    _rootUrl = connectUrl;
}

void HttpService::abortReply()
{
    if (_reply == nullptr) {
        return;
    }

    _reply->abort();
    _reply->deleteLater();
}

void HttpService::replyFinished(QNetworkReply *reply)
{
    if (reply == nullptr) {
        return;
    }

    reply->deleteLater();

    if (reply->error()) {
        qDebug() << reply->error();
        return;
    }

    QByteArray data = reply->readAll();

    switch (_currentOp) {
    case HttpOp::GetByFilters:
        emit didGetByFilters(data);

        break;
    case HttpOp::GetById:
        emit didGetById(data);

        break;
    case HttpOp::None:
        return;
    }
}
