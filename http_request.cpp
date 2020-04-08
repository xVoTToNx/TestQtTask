#include "http_request.h"

HttpRequest::HttpRequest(QObject *parent)
    : QObject(parent)
{

}

void HttpRequest::setReply(QNetworkReply *reply)
{
    reply->setParent(this);
    this->reply = reply;
    QObject::connect(reply, &QNetworkReply::readyRead,
           this, &HttpRequest::onRequestCompleted);
}

void HttpRequest::setReplyWithoutReadingData(QNetworkReply *reply)
{
    reply->setParent(this);
    this->reply = reply;
    QObject::connect(reply, &QNetworkReply::readyRead,
           this, &HttpRequest::onRequestWithoutReadingCompleted);
}

void HttpRequest::onRequestCompleted()
{
    if(!reply)
    {
        qDebug()<<"HttpRequst::onRequestComleted - reply is nullptr";
        return;
    }

    if (reply->error())
    {
        qDebug()<<reply->errorString();
        emit errorReceived(reply->errorString());
        return;
    }
    QString answer = reply->readAll();
    qDebug()<<answer;
    QJsonDocument doc = QJsonDocument::fromJson(answer.toUtf8());
    QJsonObject obj = doc.object();

    if(obj.contains("first_errors"))
    {
        qDebug()<<obj["first_errors"].toString();
        emit errorReceived(obj["first_errors"].toObject().begin().value().toString());
        return;
    }

    emit dataReceived(obj);
}

void HttpRequest::onRequestWithoutReadingCompleted()
{
    if(!reply)
    {
        qDebug()<<"HttpRequst::onRequestComleted - reply is nullptr";
        return;
    }

    if (reply->error())
    {
        qDebug()<<reply->errorString();
        emit errorReceived(reply->errorString());
        return;
    }

    QJsonObject obj;
    emit dataReceived(obj);
}
