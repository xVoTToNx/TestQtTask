#ifndef PROJECTINFOHTTPREQUEST_H
#define PROJECTINFOHTTPREQUEST_H

#include "http_request.h"

class ProjectInfoHttpRequest : public HttpRequest
{
    Q_OBJECT

    int id;
public:
    ProjectInfoHttpRequest(QNetworkAccessManager* network_manager, const QString& auth_token, const QString& project_id);

protected:
    void dataReceived(QJsonObject& object) override;

signals:
    void ProjectInfoReceived(QJsonObject project_info);

};

#endif // PROJECTINFOHTTPREQUEST_H
