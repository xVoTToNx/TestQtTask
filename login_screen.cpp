#include "login_screen.h"
#include "main_window.h"

LoginScreen::LoginScreen(MainWindow* main_window, NetworkProtocol* network_protocol)
    : QWidget(main_window)
    , network_protocol(network_protocol)
    , main_window(main_window)
    , isLoginProcessing(false)
    , login_edit(new QLineEdit(""))
    , password_edit(new QLineEdit(""))
    , login_label(new QLabel("LOGIN"))
    , login_error_label(new QLabel(""))
    , login_button(new QPushButton("LOGIN"))
    , login_layout(new QVBoxLayout())
{

    QObject::connect(network_protocol, &NetworkProtocol::onLoginErrorReceived,
                     this, &LoginScreen::onLoginError);

    QFont font("Arial", 9, 9);
    login_edit->setFont(font);
    password_edit->setFont(font);
    font.setBold(true);
    login_label->setFont(font);
    font.setPixelSize(15);
    font.setWeight(15);
    login_button->setFont(font);
    login_error_label->setFont(font);


    login_layout->addWidget(login_label);
    login_layout->addWidget(login_edit);
    login_layout->addWidget(password_edit);
    login_layout->addWidget(login_button);
    login_layout->addWidget(login_error_label);

    login_label->setFixedSize(50, 30);
    login_edit->setFixedSize(260, 30);
    password_edit->setFixedSize(260, 30);
    login_button->setFixedSize(85, 30);
    login_error_label->setFixedSize(260, 30);

    login_edit->setPlaceholderText(" Email");
    password_edit->setPlaceholderText(" Password");
    password_edit->setEchoMode(QLineEdit::Password);
    login_button->setDefault(true);

    login_edit->setStyleSheet("QLineEdit { border: 1px solid grey; border-radius: 5px;}");
    password_edit->setStyleSheet("QLineEdit { border: 1px solid grey; border-radius: 5px;}");
    login_button->setStyleSheet("QPushButton { color: white; background-color: blue; border-radius: 5px;}");
    login_error_label->setStyleSheet("QLabel { color: red; }");

    login_layout->setAlignment(Qt::AlignCenter);
    login_error_label->setAlignment(Qt::AlignLeft);

    QObject::connect(login_button, &QPushButton::clicked,
            this, &LoginScreen::onLoginButtonClick);

    setLayout(login_layout);
}

void LoginScreen::onLoginButtonClick()
{
    QString email = login_edit->text();
    QString password = password_edit->text();
    network_protocol->Login(email, password);
}

void LoginScreen::onLoginError(QString error_str)
{
    login_error_label->setText(error_str);
}
