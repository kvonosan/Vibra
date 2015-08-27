#include "net.h"
#include <QJsonDocument>
#include <QJsonObject>

Net::Net(QString client_id, QString client_secret)
{
    _manager = new QNetworkAccessManager(0);
    _reply = _manager->get(QNetworkRequest(QUrl("https://oauth.vk.com/access_token?client_id="+client_id+"&client_secret="+client_secret+"&v=5.37&grant_type=client_credentials")));
    QEventLoop loop;
    connect(_reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();
    QJsonDocument doc(QJsonDocument::fromJson(_reply->readAll()));
    QJsonObject obj = doc.object();
    if (obj.contains("access_token"))
    {
        _access_token =  obj["access_token"].toString();
    } else
    {
        qDebug() << "Invalid access token.";
        exit(-1);
    }
}

Net::~Net()
{
    delete _manager;
}
