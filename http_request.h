#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H

#include <QObject>
#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrlQuery>
#include <QLabel>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

class HttpRequest : public QObject
{
    Q_OBJECT
public:
    explicit HttpRequest(QObject* parent = nullptr);

protected:
    QNetworkReply* reply;

    void setReply(QNetworkReply* reply);
    void setReplyWithoutReadingData(QNetworkReply *reply);

    virtual void dataReceived(QJsonObject& object) {}
    virtual void errorReceived(QString error_str) {}

private slots:
    void onRequestCompleted();
    void onRequestWithoutReadingCompleted();
};

#endif // HTTPREQUEST_H
