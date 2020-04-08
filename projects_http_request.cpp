#include "projects_http_request.h"

ProjectsHttpRequest::ProjectsHttpRequest(QNetworkAccessManager *network_manager, const QString &auth_token)
{
    QNetworkRequest request;
    request.setUrl(QUrl("https://api.quwi.com/v2/projects-manage/index"));
    request.setRawHeader("Authorization", ("Bearer " + auth_token).toUtf8());

    QNetworkReply *reply = network_manager->get(request);
    setReply(reply);
}

void ProjectsHttpRequest::dataReceived(QJsonObject &object)
{
    emit ProjectsReceived(object["projects"].toArray());
}
