#ifndef LOGINSCREEN_H
#define LOGINSCREEN_H

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

class MainWindow;

class LoginScreen : public QWidget
{
    Q_OBJECT

    MainWindow* main_window;

    bool isLoginProcessing;

    QLineEdit* login_edit;
    QLineEdit* password_edit;
    QLabel* login_label;
    QLabel* login_error_label;
    QPushButton* login_button;
    QVBoxLayout* login_layout;

public:
    LoginScreen(MainWindow* main_window);
    void ShowErrorMessage(QString error_msg);

private slots:
    void onLoginButtonClick();
};

#endif // LOGINSCREEN_H
