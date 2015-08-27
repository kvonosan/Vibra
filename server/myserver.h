// myserver.h

#ifndef MYSERVER_H
#define MYSERVER_H

#include <QTcpServer>
#include "myclient.h"

class MyServer : public QTcpServer
{
    Q_OBJECT
public:
    ~MyServer();
    void startServer();
    explicit MyServer(QObject *parent = 0);
protected:
    void incomingConnection(qintptr socketDescriptor);
private:
    void DeleteNotActive();
    QVector <MyClient* > _clients;
};

#endif // MYSERVER_H
