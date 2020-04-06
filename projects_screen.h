#ifndef PROJECTSSCREEN_H
#define PROJECTSSCREEN_H


#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QNetworkRequest>
#include <QUrlQuery>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QListWidget>

class MainWindow;

class ProjectsScreen : public QWidget
{
    Q_OBJECT

    bool isProjectProcessing;

    MainWindow* main_window;

    QListWidget* projects_list;
    QVBoxLayout* projects_layout;

public:
    ProjectsScreen(MainWindow* main_window);
    void ShowMe(QJsonObject& projects_info);

private:
    void addProjectToList(QJsonObject project_info);

private slots:
    void onProjectsListItemClicked(QListWidgetItem* item);
};

#endif // PROJECTSSCREEN_H
