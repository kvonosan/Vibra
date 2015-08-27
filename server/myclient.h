// myclient.h

#ifndef MYCLIENT_H
#define MYCLIENT_H

#include <QtNetwork>
#include <QObject>
#include <QDebug>
#include <QThreadPool>
#include "mytask.h"
#include "player.h"

class MyClient : public QObject
{
    Q_OBJECT
public:
    explicit MyClient(QObject *parent = 0);
    ~MyClient();
    void setSocket(qintptr Descriptor);
    bool VkAuth(QString access_token);
signals:
public slots:
    void connected();
    void disconnected();
    void readyRead();

    // make the server fully ascynchronous
    // by doing time consuming task
    void TaskResult(int Number);

private:
    QTcpSocket *_socket;
    Player *_player;
    QNetworkAccessManager *_manager;
    QNetworkReply *_reply;
};

#endif // MYCLIENT_H
