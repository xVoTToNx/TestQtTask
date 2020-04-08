#include "project_info_http_request.h"

ProjectInfoHttpRequest::ProjectInfoHttpRequest(QNetworkAccessManager *network_manager, const QString &auth_token, const QString &project_id)
{
    id = project_id.toInt();

    QNetworkRequest request;

    request.setUrl(QUrl("https://api.quwi.com/v2/projects-manage/index"));
    request.setRawHeader("Authorization", ("Bearer " + auth_token).toUtf8());

    QNetworkReply *reply = network_manager->get(request);
    setReply(reply);
}

void ProjectInfoHttpRequest::dataReceived(QJsonObject &object)
{
    QJsonArray projects = object["projects"].toArray();
    for(auto i = projects.begin(); i != projects.end(); ++i)
    {
        if(i->toObject()["id"].toInt() == id)
        {
            emit ProjectInfoReceived(i->toObject());
            break;
        }
    }
}
