// myclient.h

#ifndef MYCLIENT_H
#define MYCLIENT_H

#include <QtSql>
#include <QObject>
#include <QtNetwork>
#include <QThreadPool>
#include "mytask.h"
#include "player.h"

class MyClient : public QObject
{
    Q_OBJECT
public:
    ~MyClient();
    void VkAuth(QString access_token);
    void setSocket(qintptr Descriptor);
    explicit MyClient(QObject *parent = 0);
    bool _delete;
public slots:
    void connected();
    void readyRead();
    void disconnected();
    // make the server fully ascynchronous
    // by doing time consuming task
    void TaskResult(int Number);
private:
    Player *_player;
    QTcpSocket *_socket;
    QNetworkReply *_reply;
    QNetworkAccessManager *_manager;
};

#endif // MYCLIENT_H
