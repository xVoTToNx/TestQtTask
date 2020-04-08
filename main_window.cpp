#include "main_window.h"
#include "ui_main_window.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , network_protocol(new NetworkProtocol(this))
    , main_screen(new QWidget(this))
    , screens(new QStackedWidget(this))
    , login_screen(new LoginScreen(this, network_protocol))
    , projects_screen(new ProjectsScreen(this, network_protocol))
    , project_info_screen(new ProjectInfoScreen(this, network_protocol))
    , toolbar(new QToolBar("Title", this))
    , main_layout(new QVBoxLayout())
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    initMainScreen();

    screens->addWidget(login_screen);
    screens->addWidget(projects_screen);
    screens->addWidget(project_info_screen);

    QObject::connect (network_protocol, &NetworkProtocol::LoggedIn, this, &MainWindow::PrepareProjectsScreen);
    QObject::connect (network_protocol, &NetworkProtocol::ProjectsReceived, this, &MainWindow::ShowProjectsScreen);
    QObject::connect (network_protocol, &NetworkProtocol::ProjectInfoReceived, this, &MainWindow::ShowProjectInfoScreen);

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

    screens->setCurrentWidget(login_screen);
}

void MainWindow::PrepareProjectsScreen()
{
    qDebug()<<"Prepairing project screen";
    network_protocol->GetProjects();
}

void MainWindow::ShowProjectsScreen(QJsonArray projects)
{
    qDebug()<<"Show porjects screen!";
    setProjectsToolBar();

    projects_screen->ShowMe(projects);

    screens->setCurrentWidget(projects_screen);
}

void MainWindow::PrepareProjectInfoScreen(const QString& id_str)
{
    network_protocol->GetProjectInfo(id_str);
}

void MainWindow::ShowProjectInfoScreen(QJsonObject project_info)
{
    project_info_screen->ShowMe(project_info);

    screens->setCurrentWidget(project_info_screen);
}

void MainWindow::initToolBar()
{
    toolbar->setMovable(false);
    toolbar->setOrientation(Qt::Orientation::Horizontal);
    toolbar->setFloatable(false);
    toolbar->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    toolbar->setStyleSheet("QToolBar { background-color: white; border: 1px solid black; }");

    QWidget *spacerWidget = new QWidget(this);
    spacerWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    spacerWidget->setVisible(true);
    toolbar->addWidget(spacerWidget);

    login_action = new QAction("LOGIN", toolbar);
    login_action->setEnabled(false);
    toolbar->addAction(login_action);

    projects_action = new QAction("PROJECTS", toolbar);
    projects_action->setEnabled(true);
    toolbar->addAction(projects_action);

    logout_action = new QAction("LOGOUT", toolbar);
    logout_action->setEnabled(true);
    toolbar->addAction(logout_action);

    QObject::connect(projects_action, &QAction::triggered, this, &MainWindow::PrepareProjectsScreen);
    QObject::connect(logout_action, &QAction::triggered, this, &MainWindow::ShowLoginScreen);

    login_action->setVisible(false);
    projects_action->setVisible(false);
    logout_action->setVisible(false);
}

void MainWindow::setLoginToolBar()
{
    login_action->setVisible(true);
}

void MainWindow::setProjectsToolBar()
{
    projects_action->setVisible(true);
    logout_action->setVisible(true);
}

void MainWindow::ChangeLoginScreen(bool isAuthorized)
{
    if(isAuthorized)
    {
        PrepareProjectsScreen();
    }
    else
    {
        ShowLoginScreen();
    }
}


