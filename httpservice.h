#ifndef HTTPSERVICE_H
#define HTTPSERVICE_H

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QObject>

enum HttpOp {
    None,
    GetByFilters,
    GetById,
};

class HttpService : public QObject
{
    Q_OBJECT
public:
    explicit HttpService(QObject *parent = nullptr);

    void getByFilters(QString jsonFilters);
    void getById(QString id);

    const QString &rootUrl() const;
    void setRootUrl(const QString &newRootUrl);

public slots:
    void abortReply();

signals:
    void didGetByFilters(QByteArray&);
    void didGetById(QByteArray&);

private:
    QNetworkAccessManager *_manager;
    QNetworkReply *_reply;
    QNetworkRequest request;
    QString _rootUrl;
    HttpOp _currentOp;

    void replyFinished(QNetworkReply *reply);
};

#endif // HTTPSERVICE_H
