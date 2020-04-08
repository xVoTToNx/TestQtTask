#include "network_protocol.h"

NetworkProtocol::NetworkProtocol(QObject *parent)
    : QObject(parent)
    , authorized(false)
    , auth_token("")
    , manager(new QNetworkAccessManager(this))
{

}

void NetworkProtocol::Login(const QString &email, const QString &password)
{
    auto request = new LoginHttpRequest(manager, email, password);
    QObject::connect(request, &LoginHttpRequest::AuthTokenReceived,
           this, &NetworkProtocol::onAuthTokenReceived);
    QObject::connect(request, &LoginHttpRequest::ErrorReceived,
           this, &NetworkProtocol::onLoginErrorReceived);
    QObject::connect(request, &LoginHttpRequest::AuthTokenReceived,
           request, &LoginHttpRequest::deleteLater);
}

void NetworkProtocol::GetProjects()
{
    auto request = new ProjectsHttpRequest(manager, auth_token);
    QObject::connect(request, &ProjectsHttpRequest::ProjectsReceived,
           this, &NetworkProtocol::ProjectsReceived);
    QObject::connect(request, &ProjectsHttpRequest::ProjectsReceived,
           request, &ProjectsHttpRequest::deleteLater);
}

void NetworkProtocol::GetProjectInfo(const QString& project_id)
{
    auto request = new ProjectInfoHttpRequest(manager, auth_token, project_id);
    QObject::connect(request, &ProjectInfoHttpRequest::ProjectInfoReceived,
           this, &NetworkProtocol::ProjectInfoReceived);
    QObject::connect(request, &ProjectInfoHttpRequest::ProjectInfoReceived,
           request, &ProjectInfoHttpRequest::deleteLater);
}

void NetworkProtocol::EditProjectInfo(const QString& project_id, const QJsonObject& project_info)
{
    EditProjectInfoHttpRequest(manager, auth_token, project_id, project_info);
}

void NetworkProtocol::LoadIcon(QLabel* label, const QString& url, const QSize& size)
{
    auto request = new LoadIconHttpRequest(manager, label, url, size);
    QObject::connect(request, &LoadIconHttpRequest::IconDone,
           request, &LoadIconHttpRequest::deleteLater);
}

void NetworkProtocol::onAuthTokenReceived(const QString& auth_token)
{
   this->auth_token = auth_token;
   emit LoggedIn();
}
