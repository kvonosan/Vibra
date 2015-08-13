#include "vk_auth.h"
#include <QJsonDocument>
#include <QJsonObject>

vk_auth::vk_auth(QString client_id, QString client_secret)
{
    QNetworkAccessManager *manager = new QNetworkAccessManager(0);
    QNetworkReply *netReply = manager->get(QNetworkRequest(QUrl("https://oauth.vk.com/access_token?client_id="+client_id+"&client_secret="+client_secret+"&v=5.37&grant_type=client_credentials")));
    QEventLoop loop;
    connect(netReply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();
    QJsonDocument doc(QJsonDocument::fromJson(netReply->readAll()));
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

vk_auth::~vk_auth()
{}
