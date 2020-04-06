#include "main_window.h"
#include "ui_main_window.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , auth_token("")
    , main_screen(new QWidget(this))
    , screens(new QStackedWidget(this))
    , login_screen(this)
    , projects_screen(this)
    , project_info_screen(this)
    , toolbar(new QToolBar("Title", this))
    , main_layout(new QVBoxLayout())

    , manager(new QNetworkAccessManager(this))
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    initMainScreen();

    screens->addWidget(&login_screen);
    screens->addWidget(&projects_screen);
    screens->addWidget(&project_info_screen);

    ShowLoginScreen();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initMainScreen()
{
    initToolBar();

    setCentralWidget(main_screen);
    main_screen->setLayout(main_layout);
    main_layout->addWidget(toolbar, 0);

    main_layout->addWidget(screens, 1);
    screens->setStyleSheet("QWidget {background-color: white;}");
}

void MainWindow::ShowLoginScreen()
{
    setLoginToolBar();

    screens->setCurrentWidget(&login_screen);
}

void MainWindow::ShowProjectsScreen()
{
    setProjectsToolBar();

    QNetworkRequest request;

    request.setUrl(QUrl("https://api.quwi.com/v2/projects-manage/index"));
    request.setRawHeader("Authorization", ("Bearer " + auth_token).toUtf8());

    QNetworkReply *reply = manager->get(request);
    connect(reply, &QNetworkReply::readyRead, [reply, this]()
    {
        if (reply->error())
        {
            login_screen.ShowErrorMessage("Something went wrong");
            ShowLoginScreen();
            return;
        }

        QString answer = reply->readAll();
        QJsonDocument doc = QJsonDocument::fromJson(answer.toUtf8());
        QJsonObject proj_info = doc.object();

        projects_screen.ShowMe(proj_info);

        screens->setCurrentWidget(&projects_screen);
    });
}

void MainWindow::ShowProjectInfoScreen(QJsonObject project_info)
{
    project_info_screen.ShowMe(project_info);

    screens->setCurrentWidget(&project_info_screen);
}

void MainWindow::initToolBar()
{
    toolbar->setMovable(false);
    toolbar->setOrientation(Qt::Orientation::Horizontal);
    toolbar->setFloatable(false);
    toolbar->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    toolbar->setStyleSheet("QToolBar { background-color: white; border: 1px solid black; }");
}

void MainWindow::setLoginToolBar()
{
    toolbar->clear();
    QWidget *spacerWidget = new QWidget(this);
    spacerWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    spacerWidget->setVisible(true);
    toolbar->addWidget(spacerWidget);

    QAction* login_action = new QAction("LOGIN", toolbar);
    login_action->setEnabled(false);
    toolbar->addAction(login_action);
}

void MainWindow::setProjectsToolBar()
{
    toolbar->clear();
    QWidget *spacerWidget = new QWidget(this);
    spacerWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    spacerWidget->setVisible(true);
    toolbar->addWidget(spacerWidget);

    QAction* projects_action = new QAction("PROJECTS", toolbar);
    projects_action->setEnabled(true);
    toolbar->addAction(projects_action);

    QAction* logout_action = new QAction("LOGOUT", toolbar);
    logout_action->setEnabled(true);
    toolbar->addAction(logout_action);

    connect(toolbar, &QToolBar::actionTriggered, [this, projects_action, logout_action](QAction* action){
        if(action == projects_action)
            ShowProjectsScreen();
        else if (action == logout_action)
            ShowLoginScreen();
    });
}

void MainWindow::LoadIcon(QLabel *icon, QString url, QSize icon_size)
{
    QNetworkRequest request;
    request.setUrl(QUrl(url));


    QNetworkReply *reply = manager->get(request);
    connect(reply, &QNetworkReply::readyRead, [reply, icon, icon_size]()
    {
        if (reply->error())
        {return;}
        QImageReader imageReader(reply);
        imageReader.setAutoDetectImageFormat (true);
        QImage pic = imageReader.read();
        pic = pic.scaled(icon_size, Qt::KeepAspectRatio);
        icon->setPixmap(QPixmap::fromImage(pic));
    });
}


