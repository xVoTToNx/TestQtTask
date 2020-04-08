#include "login_http_request.h"


LoginHttpRequest::LoginHttpRequest(QNetworkAccessManager *network_manager, const QString &email, const QString& password)
{
    QNetworkRequest request;

    request.setUrl(QUrl("https://api.quwi.com/v2/auth/login"));
    QUrlQuery params;
    params.addQueryItem("email", email.toUtf8());
    params.addQueryItem("password", password.toUtf8());
    QNetworkReply* reply = network_manager->post(request, params.query().toUtf8());
    setReply(reply);
}

void LoginHttpRequest::dataReceived(QJsonObject &object)
{
    QString auth_token = object["token"].toString();
    emit AuthTokenReceived(auth_token);
}

void LoginHttpRequest::errorReceived(QString error_str)
{
    emit ErrorReceived(error_str);
}
