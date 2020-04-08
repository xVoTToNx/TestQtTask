#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QFont>
#include <QToolBar>
#include <QStackedWidget>
#include <QListWidget>
#include <QGridLayout>
#include <QImageReader>
#include <QToolButton>

#include "login_screen.h"
#include "projects_screen.h"
#include "project_info_screen.h"

#include "network_protocol.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    NetworkProtocol* network_protocol;

    QWidget* main_screen;

    QStackedWidget* screens;

    LoginScreen* login_screen;
    ProjectsScreen* projects_screen;
    ProjectInfoScreen* project_info_screen;

    QToolBar* toolbar;
    QVBoxLayout* main_layout;

    QAction* login_action;
    QAction* projects_action;
    QAction* logout_action;

public:

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void ChangeLoginScreen(bool isAuthorized);

private:
    Ui::MainWindow *ui;

    void initMainScreen();
    void initToolBar();

    void setLoginToolBar();
    void setProjectsToolBar();

public slots:
    void ShowLoginScreen();
    void PrepareProjectsScreen();
    void ShowProjectsScreen(QJsonArray projects);
    void PrepareProjectInfoScreen(const QString& id_str);
    void ShowProjectInfoScreen(QJsonObject project_info);

};
#endif // MAINWINDOW_H
