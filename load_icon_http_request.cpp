#include "load_icon_http_request.h"


LoadIconHttpRequest::LoadIconHttpRequest(QNetworkAccessManager *network_manager,
                                         QLabel *label,
                                         const QString &url,
                                         const QSize& size)
    : label(label)
    , size(size)
{
    QNetworkRequest request;
    request.setUrl(QUrl(url));

    QNetworkReply *reply = network_manager->get(request);
    setReplyWithoutReadingData(reply);
}

void LoadIconHttpRequest::dataReceived(QJsonObject &object)
{
    QImageReader imageReader(reply);
    imageReader.setAutoDetectImageFormat (true);
    QImage pic = imageReader.read();
    pic = pic.scaled(size, Qt::KeepAspectRatio);
    label->setPixmap(QPixmap::fromImage(pic));

    emit IconDone();
}
