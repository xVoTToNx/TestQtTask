#include "edit_project_info_http_request.h"

EditProjectInfoHttpRequest::EditProjectInfoHttpRequest(QNetworkAccessManager *network_manager,
                                                       const QString &auth_token,
                                                       const QString &id,
                                                       const QJsonObject &project_info)
{
    QNetworkRequest request;

    request.setUrl(QUrl("https://api.quwi.com/v2/projects-manage/update?id=" + id));
    request.setRawHeader("Authorization", ("Bearer " + auth_token.toUtf8()));
qDebug()<<"!1";
    QUrlQuery params;
    for(auto i = project_info.begin(); i != project_info.end(); ++i)
    {
        params.addQueryItem(i.key(), i.value().toString());
    }
    QNetworkReply *reply = network_manager->post(request, params.query().toUtf8());
}
