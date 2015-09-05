#ifndef MYSERVER_H
#define MYSERVER_H

#include "loader.h"
#include "myclient.h"
#include <QTcpServer>

class MyServer : public QTcpServer
{
    Q_OBJECT
public:
    ~MyServer();
    void startServer();
    explicit MyServer(Loader *loader, QObject *parent = 0);
protected:
    void incomingConnection(qintptr socketDescriptor);
private:
    void DeleteNotActive();
    Loader *_loader;
    QVector <MyClient* > _clients;
};

#endif // MYSERVER_H
