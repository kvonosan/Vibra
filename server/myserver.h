// myserver.h

#ifndef MYSERVER_H
#define MYSERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QAbstractSocket>
#include "myclient.h"

class MyServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit MyServer(QObject *parent = 0);
    ~MyServer();
    void startServer();
protected:
    void incomingConnection(qintptr socketDescriptor);
private:
    QVector <MyClient* > _clients;
};

#endif // MYSERVER_H
