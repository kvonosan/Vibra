#ifndef NET
#define NET

#include <QtNetwork>

class Net : public QObject
{
    Q_OBJECT
public:
    Net();
    ~Net();
    void GetVKName();
    void NetConnect();
    bool VKConnected();
    bool _connected;
private:
    int _port;
    QTcpSocket *_tcp;
    QNetworkReply *_reply;
    QString _firstName, _lastName;
    int _vk_player_id, _player_id;
    QNetworkAccessManager *_manager;
    QString _access_token, _vk_user_id;
public slots:
    void Connected();
    void readyRead();
};

#endif // NET
