#include "project_info_screen.h"
#include "main_window.h"

ProjectInfoScreen::ProjectInfoScreen(MainWindow* main_window)
    : QWidget(main_window)
    , isProjectProcessing(false)
    , main_window(main_window)
    , active_label(new QLabel("Active"))
    , name_label(new QLabel("Name"))
    , add_me_as_watcher_label(new QLabel("Add me as watcher to tickets created by others"))
    , project_icon_label(new QLabel(""))
    , project_name_edit(new QLineEdit())
    , project_name_button(new QPushButton("OK"))
    , active_button(new QToolButton())
    , add_me_as_watcher_button(new QToolButton())
    , project_info_layout(new QGridLayout())
{
    setLayout(project_info_layout);
    project_info_layout->addWidget(active_label, 0, 0, 1, 1);
    project_info_layout->addWidget(active_button, 0, 1, 1, 2);
    project_info_layout->addWidget(name_label, 1, 0, 1, 1);
    project_info_layout->addWidget(project_name_edit,1, 1, 1, 1);
    project_info_layout->addWidget(project_name_button, 1, 2, 1, 1);
    project_info_layout->addWidget(project_icon_label, 0, 3, 2, 1);
    project_info_layout->addWidget(add_me_as_watcher_button, 2, 0, 1, 1);
    project_info_layout->addWidget(add_me_as_watcher_label, 2, 1, 1, 3);

    active_label->setFixedSize(80, 40);
    active_button->setFixedSize(40, 40);
    name_label->setFixedSize(80, 40);
    project_name_edit->setFixedSize(280, 40);
    project_name_button->setFixedSize(50, 40);
    project_icon_label->setFixedSize(80, 80);
    add_me_as_watcher_button->setFixedSize(40, 40);
    add_me_as_watcher_label->setFixedSize(300, 40);

    QFont font("Arial", 12, 12);
    active_label->setFont(font);
    name_label->setFont(font);
    add_me_as_watcher_label->setFont(font);
    project_name_edit->setFont(font);
    font.setBold(true);
    project_name_button->setFont(font);

    project_info_layout->setAlignment(Qt::AlignCenter);
    active_button->setCheckable(true);
    add_me_as_watcher_button->setCheckable(true);
    active_button->setStyleSheet("QToolButton {background-color: grey };");
    add_me_as_watcher_button->setStyleSheet("QToolButton {background-color: grey };");

    connect(active_button, &QToolButton::toggled, [this](bool checked) {
        active_button->setStyleSheet("QToolButton {background-color: " + QString(checked ? "green" : "grey") + " };");
    });
    connect(add_me_as_watcher_button, &QToolButton::toggled, [this](bool checked) {
        add_me_as_watcher_button->setStyleSheet("QToolButton {background-color: " + QString(checked ? "green" : "grey") + " };");
    });
    connect(project_name_button, &QPushButton::clicked, this, &ProjectInfoScreen::onProjectNameButtonClicked);

    project_name_edit->setStyleSheet("QLineEdit { border: 1px solid grey; border-radius: 5px;}");
    project_name_button->setStyleSheet("QPushButton { color: white; background-color: blue; border-radius: 5px;}");

}

void ProjectInfoScreen::ShowMe(QJsonObject &project_info)
{
    active_button->setChecked(project_info["is_active"].toInt() == 1);
    add_me_as_watcher_button->setChecked(project_info["is_owner_watcher"].toInt() == 1);
    project_name_edit->setText(project_info["name"].toString());

    QPixmap pixmap;
    project_icon_label->setPixmap(pixmap);
    main_window->LoadIcon(project_icon_label, project_info["logo_url"].toString(), {80, 80});
}

void ProjectInfoScreen::onProjectNameButtonClicked()
{
    QNetworkRequest request;

    request.setUrl(QUrl("https://api.quwi.com/v2/projects-manage/update?id=" + QString::number(main_window->property("current_project_id").toInt())));
    request.setRawHeader("Authorization", ("Bearer " + main_window->auth_token).toUtf8());

    QUrlQuery params;
    params.addQueryItem("name", project_name_edit->text());

    QNetworkReply *reply = main_window->manager->post(request, params.query().toUtf8());
}



