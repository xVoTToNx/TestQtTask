#ifndef EDITPROJECTINFOHTTPREQUEST_H
#define EDITPROJECTINFOHTTPREQUEST_H

#include "http_request.h"

class EditProjectInfoHttpRequest : public HttpRequest
{
    Q_OBJECT
public:
    EditProjectInfoHttpRequest(QNetworkAccessManager* network_manager, const QString &auth_token, const QString& id, const QJsonObject& project_info);
};

#endif // EDITPROJECTINFOHTTPREQUEST_H
