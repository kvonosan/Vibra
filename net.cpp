#include "net.h"

Net::Net()
{
    _port = 33333;
    _manager = new QNetworkAccessManager(0);
    _reply = _manager->get(QNetworkRequest(QUrl("https://api.vk.com/method/users.get?v=5.37")));
    QEventLoop loop;
    connect(_reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();
    QJsonDocument document = QJsonDocument::fromJson(_reply->readAll());
    QJsonObject object = document.object();
    QJsonValue value = object.value("response");
    QJsonArray array = value.toArray();
    foreach (const QJsonValue & v, array)
    {
        _vk_player_id =  v.toObject().value("id").toInt();
        _firstName = v.toObject().value("first_name").toString();
        _lastName = v.toObject().value("last_name").toString();
    }
    _connected = false;
}

Net::~Net()
{
    delete _manager;
    delete _reply;
}

void Net::NetConnect()
{
    _tcp = new QTcpSocket();
    connect(_tcp, SIGNAL(connected()), SLOT(Connected()));
    _tcp->connectToHost("31.24.29.91", _port);
    _tcp->waitForConnected(2000);
    _tcp->connectToHost("127.0.0.1", _port);
}

void Net::Connected()
{
    _tcp->write((const char*) &_vk_player_id, sizeof(_vk_player_id));
    _connected = true;
}

bool Net::VKConnected()
{
    QString filename = "token.txt";
    QFile file( filename );
    QString token;
    if ( file.open(QIODevice::ReadOnly) )
    {
        QTextStream stream( &file );
        stream >> _acess_token;
    }
    if (token.startsWith("error"))
    {
        return false;
    } else
    {
        QNetworkAccessManager *manager = new QNetworkAccessManager(0);
        QNetworkReply *netReply = manager->get(QNetworkRequest(QUrl("https://api.vk.com/method/friends.getOnline?v=5.37&" + _acess_token)));
        QEventLoop loop;
        connect(netReply, SIGNAL(finished()), &loop, SLOT(quit()));
        loop.exec();
        QString reply = netReply->readAll();
        if (reply.contains("response"))
        {
            return true;
        } else
        {
            return false;
        }
    }
}
