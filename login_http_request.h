#ifndef LOGINHTTPREQUEST_H
#define LOGINHTTPREQUEST_H

#include "http_request.h"


class LoginHttpRequest : public HttpRequest
{
    Q_OBJECT

public:
    LoginHttpRequest(QNetworkAccessManager* network_manager, const QString &email, const QString& password);

protected:
    void dataReceived(QJsonObject& object) override;
    void errorReceived(QString error_str) override;

signals:
    void AuthTokenReceived(QString auth_token);
    void ErrorReceived(QString error_str);

};

#endif // LOGINHTTPREQUEST_H
