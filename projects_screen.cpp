#include "project_info_screen.h"
#include "main_window.h"

ProjectsScreen::ProjectsScreen(MainWindow* main_window)
    : QWidget(main_window)
    , isProjectProcessing(false)
    , main_window(main_window)
    , projects_list(new QListWidget())
    , projects_layout(new QVBoxLayout())
{
    setLayout(projects_layout);
    projects_layout->addWidget(projects_list);
    projects_layout->setAlignment(Qt::AlignHCenter);
    projects_list->setFixedWidth(600);

    connect(projects_list, &QListWidget::itemClicked, this, &ProjectsScreen::onProjectsListItemClicked);
}

void ProjectsScreen::ShowMe(QJsonObject &projects_info)
{
    projects_list->clear();

    QJsonArray projects = projects_info["projects"].toArray();
    for(auto i = projects.begin(); i != projects.end(); ++i)
    {
        addProjectToList(i->toObject());
    }
}

void ProjectsScreen::addProjectToList(QJsonObject project_info)
{
    QListWidgetItem* project_item = new QListWidgetItem(projects_list);
    QWidget* project_widget = new QListWidget();
    QGridLayout* project_layout = new QGridLayout();
    project_item->setSizeHint({50, 150});
    project_item->setData(Qt::UserRole + 1, project_info["id"].toInt());
    project_widget->setLayout(project_layout);

    bool isAnyUser = project_info["users"].toArray().count() != 0;

    QLabel* icon = new QLabel(project_widget);
    QLabel* name = new QLabel(project_info["name"].toString(), project_widget);
    QLabel* isActive = new QLabel(project_info["is_active"].toInt() == 1 ? "Active" : "Inactive", project_widget);
    QLabel* noUsers;
    if(!isAnyUser)
        noUsers = new QLabel("No users", project_widget);
    QLabel* time_week_label = new QLabel("time this week", project_widget);
    QLabel* time_month_label = new QLabel("this month", project_widget);
    QLabel* time_total_label = new QLabel("total", project_widget);
    QLabel* time_week_value = new QLabel(QString::number(project_info["spent_time_week"].toInt()), project_widget);
    QLabel* time_month_value = new QLabel(QString::number(project_info["spent_time_month"].toInt()), project_widget);
    QLabel* time_total_value = new QLabel(QString::number(project_info["spent_time_all"].toInt()), project_widget);

    isActive->setStyleSheet("QLabel {color: " + QString(isActive->text() == "Active" ? "green" : "grey") + "; }");
    QFont font("Arial", 10, 10);
    font.setBold(true);
    name->setFont(font);
    isActive->setFont(font);
    noUsers->setFont(font);

    time_week_value->setFont(font);
    time_month_value->setFont(font);
    time_total_value->setFont(font);

    font.setBold(false);
    time_week_label->setFont(font);
    time_month_label->setFont(font);
    time_total_label->setFont(font);


    project_layout->addWidget(icon, 0, 0, 3, 1);
    project_layout->addWidget(name, 0, 1, 3, 1);
    if(isAnyUser)
        project_layout->addWidget(isActive, 0, 2, 3, 1);
    else
    {
        project_layout->addWidget(isActive, 0, 2, 2, 1);
        project_layout->addWidget(noUsers, 0, 3, 1, 1);
    }
    project_layout->addWidget(time_week_label, 0, 3, 1, 1);
    project_layout->addWidget(time_month_label, 1, 3, 1, 1);
    project_layout->addWidget(time_total_label, 2, 3, 1, 1);
    project_layout->addWidget(time_week_value, 0, 4, 1, 1);
    project_layout->addWidget(time_month_value, 1, 4, 1, 1);
    project_layout->addWidget(time_total_value, 2, 4, 1, 1);

    main_window->LoadIcon(icon, project_info["logo_url"].toString(), {100, 100});

    projects_list->addItem(project_item);
    projects_list->setItemWidget(project_item, project_widget);
}


void ProjectsScreen::onProjectsListItemClicked(QListWidgetItem *item)
{
    if(isProjectProcessing)
        return;

    isProjectProcessing = true;

    QNetworkRequest request;

    request.setUrl(QUrl("https://api.quwi.com/v2/projects-manage/index"));
    request.setRawHeader("Authorization", ("Bearer " + main_window->auth_token).toUtf8());

    QNetworkReply *reply = main_window->manager->get(request);

    int id = item->data(Qt::UserRole + 1).toInt();
    connect(reply, &QNetworkReply::readyRead, [reply, this, id]()
    {
        if (reply->error())
        {
            qDebug()<<reply->errorString();

            isProjectProcessing = false;
            return;
        }

        QString answer = reply->readAll();
        QJsonDocument doc = QJsonDocument::fromJson(answer.toUtf8());
        QJsonObject projects_info = doc.object();

        QJsonArray projects = projects_info["projects"].toArray();
        for(auto i = projects.begin(); i != projects.end(); ++i)
        {
            if(i->toObject()["id"].toInt() == id)
            {
                main_window->setProperty("current_project_id", id);
                main_window->ShowProjectInfoScreen(i->toObject());
                break;
            }
        }


        isProjectProcessing = false;
    });
}

