#ifndef NET
#define NET

#include "base.h"
#include "popup.h"
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
    void Fire(int pos, Popup *popup);
    bool VKConnected();
    void BufferizeMap();
    void GetParams(int pos, Popup *popup);
    void NetConnect(Base *base);
    bool _connected, _authorized, _disconnect, _killed, _fire;
    int _mypos, _firepos, _life, _energy, _armor, _fuel, _shipfire, _level;
private:
    Base *_base;
    Popup *_popup;
    QTcpSocket *_tcp;
    bool _vk_connected;
    QNetworkReply *_reply;
    QString _firstName, _lastName;
    QNetworkAccessManager *_manager;
    QString _access_token, _vk_user_id;
    int _vk_player_id, _player_id, _port;
public slots:
    void Connected();
    void readyRead();
    void Disconnected();
};

#endif // NET
