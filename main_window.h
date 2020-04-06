#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrlQuery>
#include <QLabel>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
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

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    QWidget* main_screen;

    QStackedWidget* screens;

    LoginScreen login_screen;
    ProjectsScreen projects_screen;
    ProjectInfoScreen project_info_screen;

    QToolBar* toolbar;
    QVBoxLayout* main_layout;

public:
    QNetworkAccessManager *manager;
    QString auth_token;

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void ShowLoginScreen();
    void ShowProjectsScreen();
    void ShowProjectInfoScreen(QJsonObject project_info);

    void LoadIcon(QLabel* icon, QString url, QSize icon_size);

private:
    Ui::MainWindow *ui;

    void initMainScreen();
    void initToolBar();

    void setLoginToolBar();
    void setProjectsToolBar();

};
#endif // MAINWINDOW_H
