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
    void Top();
    void Left();
    void Right();
    void Bottom();
    void GetMyPos();
    void GetVKName();
    void Fire(int pos);
    bool VKConnected();
    void BufferizeMap();
    void NetConnect(Base *base);
    bool _connected;
    bool _authorized;
    bool _disconnect;
    int _mypos, _firepos;
private:
    int _port;
    Base *_base;
    QTcpSocket *_tcp;
    bool _vk_connected;
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
