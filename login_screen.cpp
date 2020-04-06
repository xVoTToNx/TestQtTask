#include "login_screen.h"
#include "main_window.h"

LoginScreen::LoginScreen(MainWindow* main_window)
    : QWidget(main_window)
    , main_window(main_window)
    , isLoginProcessing(false)
    , login_edit(new QLineEdit(""))
    , password_edit(new QLineEdit(""))
    , login_label(new QLabel("LOGIN"))
    , login_error_label(new QLabel(""))
    , login_button(new QPushButton("LOGIN"))
    , login_layout(new QVBoxLayout())
{
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

    connect(login_button, &QPushButton::clicked,
            this, &LoginScreen::onLoginButtonClick);

    setLayout(login_layout);
}

void LoginScreen::ShowErrorMessage(QString error_msg)
{
    login_error_label->setText(error_msg);
}

void LoginScreen::onLoginButtonClick()
{
    if(isLoginProcessing)
        return;

    isLoginProcessing = true;

    QNetworkRequest request;

    request.setUrl(QUrl("https://api.quwi.com/v2/auth/login"));
    QUrlQuery params;
    params.addQueryItem("email", login_edit->text().toUtf8());
    params.addQueryItem("password", password_edit->text().toUtf8());

    QNetworkReply *reply = main_window->manager->post(request, params.query().toUtf8());

    connect(reply, &QNetworkReply::readyRead, [reply, this]()
    {
        if (reply->error())
        {
            login_error_label->setText("Error: " + reply->errorString());

            isLoginProcessing = false;
            return;
        }

        QString answer = reply->readAll();
        QJsonDocument doc = QJsonDocument::fromJson(answer.toUtf8());
        QJsonObject obj = doc.object();

        if(obj.contains("first_errors"))
        {
            login_error_label->setText(obj["first_errors"].toObject().begin()->toString());

            isLoginProcessing = false;
            return;
        }

        login_error_label->setText("");
        login_edit->setText("");
        password_edit->setText("");

        main_window->auth_token = obj["token"].toString();
        main_window->ShowProjectsScreen();

        isLoginProcessing = false;
    });
}
