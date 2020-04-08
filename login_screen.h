#ifndef LOGINSCREEN_H
#define LOGINSCREEN_H

#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

#include "network_protocol.h"

class MainWindow;

class LoginScreen : public QWidget
{
    Q_OBJECT

    NetworkProtocol* network_protocol;
    MainWindow* main_window;

    QLineEdit* login_edit;
    QLineEdit* password_edit;
    QLabel* login_label;
    QLabel* login_error_label;
    QPushButton* login_button;
    QVBoxLayout* login_layout;

    bool isLoginProcessing;


public:
    LoginScreen(MainWindow* main_window, NetworkProtocol* network_protocol);

private slots:
    void onLoginButtonClick();
    void onLoginError(QString error_str);
};

#endif // LOGINSCREEN_H
