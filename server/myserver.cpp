#include "myserver.h"

MyServer::MyServer(Loader *loader, QObject *parent) :
    QTcpServer(parent)
{
    if (loader==NULL)
    {
        qDebug() << "loader == NULL";
        exit(-1);
    }
    _loader = loader;
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
    MyClient *client = new MyClient(_loader, this);
    client->setSocket(socketDescriptor);
    _clients.push_back(client);
    DeleteNotActive();
}

void MyServer::DeleteNotActive()
{
    QVectorIterator <MyClient* > i(_clients);
    while(i.hasNext())
    {
        MyClient *ptr = i.next();
         if (ptr->_delete)
         {
            delete ptr;
         }
    }
}
