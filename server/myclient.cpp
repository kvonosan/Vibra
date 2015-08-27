// myclient.cpp

#include <QDataStream>
#include "myclient.h"

MyClient::MyClient(QObject *parent) :
    QObject(parent)
{
    QThreadPool::globalInstance()->setMaxThreadCount(5);
}

MyClient::~MyClient()
{
    delete _socket;
    delete _player;
}

void MyClient::setSocket(qintptr descriptor)
{
    // make a new socket
    _socket = new QTcpSocket(this);

    qDebug() << "A new socket created!";

    connect(_socket, SIGNAL(connected()), this, SLOT(connected()));
    connect(_socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(_socket, SIGNAL(readyRead()), this, SLOT(readyRead()));

    _socket->setSocketDescriptor(descriptor);
    _player = new Player();

    qDebug() << " Client connected at " << descriptor;
}


// asynchronous - runs separately from the thread we created
void MyClient::connected()
{
    qDebug() << "Client connected event";
}

// asynchronous
void MyClient::disconnected()
{
    qDebug() << "Client disconnected";
}

bool MyClient::VkAuth(QString access_token)
{
    //get ident
    _manager = new QNetworkAccessManager(0);
    _reply = _manager->get(QNetworkRequest(QUrl("https://api.vk.com/method/users.get?v=5.37&"+access_token)));
    QEventLoop loop;
    connect(_reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();
    QByteArray recv = _reply->readAll();
    QString recv_str = QString::fromUtf8(recv.toStdString().c_str());
    if (recv_str.contains("error"))
    {
        //bye
        qDebug() <<"bye";
    } else
    {
        //todo
        qDebug() <<"todo";
        /*QJsonDocument document = QJsonDocument::fromJson(recv);
        QJsonObject object = document.object();
        QJsonValue value = object.value("response");
        QJsonArray array = value.toArray();
        int _vk_player_id=0;
        QString _firstName, _lastName;
        foreach (const QJsonValue & v, array)
        {
            _vk_player_id =  v.toObject().value("id").toInt();
            _firstName = v.toObject().value("first_name").toString();
            _lastName = v.toObject().value("last_name").toString();
        }*/
    }
    delete _manager;
}

// Our main thread of execution
// This happening via main thread
// Our code running in our current thread not in another QThread
// That's why we're getting the thread from the pool

void MyClient::readyRead()
{
    qDebug() << "MyClient::readyRead()";
    QByteArray array = _socket->readAll();
    //auth with access_token
    VkAuth(QString::fromUtf8(array.toStdString().c_str()));
/*
    bool ok;
    _player->_player_id_vk = array.toInt(&ok, 16);
    if (!ok)
    {
        qDebug() << "Отсоединен из-за неверного player_id_vk = " << _player->_player_id_vk;
        socket->close();
        return;
    }
    qDebug() << "player_id_vk = " << _player->_player_id_vk;
    if (_player->Search())
    {
        qDebug() << "player_id = " << _player->_player_id;
    } else
    {
        qDebug() << "new player_id = " << _player->_player_id;
        //send new
        QByteArray buf;
        buf.append("new");
        socket->write(buf);
    }*/

    // Time consumer
    /*MyTask *mytask = new MyTask();
    mytask->setAutoDelete(true);
    
    // using queued connection
    connect(mytask, SIGNAL(Result(int)), this, SLOT(TaskResult(int)), Qt::QueuedConnection);

    qDebug() << "Starting a new task using a thread from the QThreadPool";
    
    // QThreadPool::globalInstance() returns global QThreadPool instance
    QThreadPool::globalInstance()->start(mytask);*/

}

// After a task performed a time consuming task,
// we grab the result here, and send it to client
void MyClient::TaskResult(int Number)
{
    QByteArray Buffer;
    Buffer.append("\r\nTask result = ");
    Buffer.append(QString::number(Number));

    _socket->write(Buffer);
}
