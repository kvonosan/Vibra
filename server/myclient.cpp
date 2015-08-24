// myclient.cpp

#include <QDataStream>
#include "myclient.h"

MyClient::MyClient(QObject *parent) :
    QObject(parent)
{
    QThreadPool::globalInstance()->setMaxThreadCount(5);
}

void MyClient::setSocket(qintptr descriptor)
{
    // make a new socket
    socket = new QTcpSocket(this);

    qDebug() << "A new socket created!";

    connect(socket, SIGNAL(connected()), this, SLOT(connected()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));

    socket->setSocketDescriptor(descriptor);
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

// Our main thread of execution
// This happening via main thread
// Our code running in our current thread not in another QThread
// That's why we're getting the thread from the pool

void MyClient::readyRead()
{
    qDebug() << "MyClient::readyRead()";
    QByteArray array = socket->readAll();
    //array.remove(array.size()-1, 1);
    QDataStream stream(&array, QIODevice::ReadOnly);
    bool ok;
    _player->_player_id_vk = array.toInt(&ok, 16);
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
    }

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

    socket->write(Buffer);
}
