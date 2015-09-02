#include "myclient.h"

MyClient::MyClient(QObject *parent) :
    QObject(parent)
{
    QThreadPool::globalInstance()->setMaxThreadCount(5);
    _delete = false;
}

MyClient::~MyClient()
{
    delete _socket;
    delete _player;
}

void MyClient::setSocket(qintptr descriptor)
{
    _socket = new QTcpSocket(this);

    qDebug() << "A new socket created!";

    connect(_socket, SIGNAL(connected()), this, SLOT(connected()));
    connect(_socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(_socket, SIGNAL(readyRead()), this, SLOT(readyRead()));

    _socket->setSocketDescriptor(descriptor);
    _player = new Player();

    qDebug() << " Client connected at " << descriptor;
}

void MyClient::connected()
{
    qDebug() << "Client connected event";
}

void MyClient::disconnected()
{
    qDebug() << "Client disconnected";
}

void MyClient::VkAuth(QString access_token)
{
    _manager = new QNetworkAccessManager(0);
    _reply = _manager->get(QNetworkRequest(QUrl("https://api.vk.com/method/users.get?v=5.37&"+access_token)));
    QEventLoop loop;
    connect(_reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();
    QByteArray recv = _reply->readAll();
    QString recv_str = QString::fromUtf8(recv.toStdString().c_str());
    if (recv_str.contains("error"))
    {
        _socket->close();
        _delete = true;
    } else
    {
        QJsonDocument document = QJsonDocument::fromJson(recv);
        QJsonObject object = document.object();
        QJsonValue value = object.value("response");
        QJsonArray array1 = value.toArray();
        foreach (const QJsonValue & v, array1)
        {
            _player->_player_id_vk =  v.toObject().value("id").toInt();
            //_firstName = v.toObject().value("first_name").toString();
            //_lastName = v.toObject().value("last_name").toString();
        }
        _player->Search();
        QByteArray array;
        QDataStream stream(&array, QIODevice::WriteOnly);
        stream << _player->_player_id;
        _socket->write(array.toHex());
    }
    delete _manager;
}

void MyClient::readyRead()
{
    qDebug() << "MyClient::readyRead()";
    QByteArray array = _socket->readAll();
    //auth with access_token
    VkAuth(QString::fromUtf8(array.toStdString().c_str()));
    _player->newPlayer();
}
