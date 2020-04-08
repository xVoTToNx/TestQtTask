#ifndef LOADICONHTTPREQUEST_H
#define LOADICONHTTPREQUEST_H

#include <QLabel>
#include <QPixmap>
#include <QImage>
#include <QImageReader>

#include "http_request.h"


class LoadIconHttpRequest : public HttpRequest
{
    Q_OBJECT

    QLabel* label;
    QSize size;

public:
    LoadIconHttpRequest(QNetworkAccessManager* network_manager, QLabel* label, const QString& adress, const QSize& size);

protected:
    void dataReceived(QJsonObject& object) override;

signals:
    void IconDone();
};

#endif // LOADICONHTTPREQUEST_H
