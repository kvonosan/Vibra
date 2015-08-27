// myserver.cpp

#include "myserver.h"

MyServer::MyServer(QObject *parent) :
    QTcpServer(parent)
{
}

MyServer::~MyServer()
{
    QVectorIterator <MyClient* > i(_clients);
    while(i.hasNext())
    {
        delete i.next();
    }
}

void MyServer::startServer()
{
    if(listen(QHostAddress::Any, 33333))
    {
        qDebug() << "Server: started";
    }
    else
    {
        qDebug() << "Server: not started!";
    }
}

void MyServer::incomingConnection(qintptr socketDescriptor)
{
    // At the incoming connection, make a client
    // and set the socket
    MyClient *client = new MyClient(this);
    client->setSocket(socketDescriptor);
    _clients.push_back(client);
}
