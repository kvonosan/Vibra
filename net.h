#ifndef NET
#define NET

#include "base.h"
#include <QtNetwork>

class Base;

class Net : public QObject
{
    Q_OBJECT
public:
    Net();
    ~Net();
    void GetVKName();
    void NetConnect(Base *base);
    bool VKConnected();
    void BufferizeMap();
    void Left();
    void Right();
    void Top();
    void Bottom();
    bool _connected;
    bool _authorized;
    bool _disconnect;
private:
    bool _vk_connected;
    int _port;
    Base *_base;
    QTcpSocket *_tcp;
    QNetworkReply *_reply;
    QString _firstName, _lastName;
    int _vk_player_id, _player_id;
    QNetworkAccessManager *_manager;
    QString _access_token, _vk_user_id;
public slots:
    void Connected();
    void readyRead();
    void Disconnected();
};

#endif // NET
