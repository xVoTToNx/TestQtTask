#ifndef PROJECTSHTTPREQUEST_H
#define PROJECTSHTTPREQUEST_H

#include "http_request.h"


class ProjectsHttpRequest : public HttpRequest
{
    Q_OBJECT

public:
    ProjectsHttpRequest(QNetworkAccessManager* network_manager, const QString& auth_token);

protected:
    void dataReceived(QJsonObject& object) override;

signals:
    void ProjectsReceived(QJsonArray projects);

};

#endif // PROJECTSHTTPREQUEST_H
