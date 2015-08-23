#ifndef NET
#define NET

#include <QtNetwork>

class Net : public QObject
{
    Q_OBJECT
public:
    Net();
    ~Net();
    void NetConnect();
    bool VKConnected();
    void GetVKID();
    bool _connected;
private:
    int _port;
    QString _acess_token, _vk_user_id;
    QTcpSocket *_tcp;
    QNetworkAccessManager *_manager;
    QNetworkReply *_reply;
    int _vk_player_id;
    QString _firstName;
    QString _lastName;
public slots:
    void Connected();
};

#endif // NET
