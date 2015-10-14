#ifndef MYCLIENT_H
#define MYCLIENT_H

#include "npc.h"
#include <QtSql>
#include "loader.h"
#include <QtNetwork>

class MyClient : public QObject
{
    Q_OBJECT
public:
    ~MyClient();
    void SendInfo();
    void SendParams();
    QString GetVKName(int id);
    int GetLife(int pos);
    void setSocket(qintptr Descriptor);
    explicit MyClient(Loader *loader, QObject *parent = 0);
    bool _delete;
public slots:
    void connected();
    void readyRead();
    void disconnected();
private:
    Npc *_fireNpc;
    Loader *_loader;
    Player *_player;
    QTcpSocket *_socket;
    QNetworkReply *_reply;
    QNetworkAccessManager *_manager;
};

#endif // MYCLIENT_H
