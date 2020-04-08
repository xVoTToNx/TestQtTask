#ifndef NETWORKPROTOCOL_H
#define NETWORKPROTOCOL_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrlQuery>
#include <QLabel>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include "login_http_request.h"
#include "projects_http_request.h"
#include "project_info_http_request.h"
#include "edit_project_info_http_request.h"
#include "load_icon_http_request.h"

class NetworkProtocol : public QObject
{
    Q_OBJECT

    bool authorized;
    QString auth_token;
    QNetworkAccessManager *manager;

public:
    explicit NetworkProtocol(QObject *parent = nullptr);
    void Login(const QString& email, const QString& password);
    void GetProjects();
    void GetProjectInfo(const QString& project_id);
    void EditProjectInfo(const QString& project_id, const QJsonObject& project_info);
    void LoadIcon(QLabel* label, const QString& url, const QSize& size);

signals:
    void AuthorizedChanged(bool authorized);
    void ProjectsReceived(QJsonArray projects);
    void ProjectInfoReceived(QJsonObject projects);
    void LoggedIn();
    void LoggedOut();

    void onLoginErrorReceived(QString error_str);


private slots:
    void  onAuthTokenReceived(const QString& auth_token);

};

#endif // NETWORKPROTOCOL_H
