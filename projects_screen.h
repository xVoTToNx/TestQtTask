#ifndef PROJECTSSCREEN_H
#define PROJECTSSCREEN_H


#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QListWidget>

#include "network_protocol.h"

class MainWindow;

class ProjectsScreen : public QWidget
{
    Q_OBJECT

    bool isProjectProcessing;

    NetworkProtocol* network_protocol;
    MainWindow* main_window;

    QListWidget* projects_list;
    QVBoxLayout* projects_layout;

public:
    ProjectsScreen(MainWindow* main_window, NetworkProtocol* network_protocol);
    void ShowMe(QJsonArray& projects_info);

private:
    void addProjectToList(QJsonObject project_info);

private slots:
    void onProjectsListItemClicked(QListWidgetItem* item);
};

#endif // PROJECTSSCREEN_H
