#include "net.h"

Net::Net()
{
    _port = 33333;
    _connected = false;
    _tcp = new QTcpSocket();
}

Net::~Net()
{
    delete _tcp;
}

bool Net::VKConnected()
{
    QString filename = "token.txt";
    QFile file( filename );
    QString token;
    if ( file.open(QIODevice::ReadOnly) )
    {
        QTextStream stream( &file );
        stream >> _access_token;
        stream >> _vk_user_id;
        QStringList user_id = _vk_user_id.split("=");
        QString id = user_id.at(1);
        QStringList user_id_lst = id.split("\"");
        _vk_user_id = user_id_lst.at(0);
        //qDebug() << _vk_user_id;
    }
    if (token.startsWith("error"))
    {
        return false;
    } else
    {
        QNetworkAccessManager *manager = new QNetworkAccessManager(0);
        QNetworkReply *netReply = manager->get(QNetworkRequest(QUrl("https://api.vk.com/method/friends.getOnline?v=5.37&" + _access_token)));
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
        delete manager;
    }
    return false;
}

void Net::GetVKName()
{
    _manager = new QNetworkAccessManager(0);
    _reply = _manager->get(QNetworkRequest(QUrl("https://api.vk.com/method/users.get?v=5.37&user_ids="+_vk_user_id)));
    QEventLoop loop;
    connect(_reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();
    QByteArray recv = _reply->readAll();
    QJsonDocument document = QJsonDocument::fromJson(recv);
    QJsonObject object = document.object();
    QJsonValue value = object.value("response");
    QJsonArray array = value.toArray();
    foreach (const QJsonValue & v, array)
    {
        _vk_player_id =  v.toObject().value("id").toInt();
        _firstName = v.toObject().value("first_name").toString();
        _lastName = v.toObject().value("last_name").toString();
    }
    delete _manager;
}

void Net::NetConnect()
{
    connect(_tcp, SIGNAL(connected()), this, SLOT(Connected()));
    _tcp->connectToHost("91.215.138.69", _port);
    _tcp->waitForConnected(2000);
    _tcp->connectToHost("127.0.0.1", _port);
    _connected = true;
}

void Net::Connected()
{
    _tcp->write(_access_token.toUtf8());
    connect(_tcp, SIGNAL(readyRead()), this, SLOT(readyRead()));
}

void Net::readyRead()
{
    QByteArray _player_id_buf = _tcp->readAll();
    bool ok;
    _player_id = _player_id_buf.toInt(&ok, 16);
    if (!ok)
    {
        qDebug() << "Net read error.";
        exit(-1);
    }
    GetVKName();
}
