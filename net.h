#ifndef NET
#define NET

#include <QtNetwork>

class Net : public QObject
{
public:
    Net();
    ~Net();
    void Connect();
    bool VKConnected();
    bool _connected;
private:
    int _port;
    QString _acess_token;
    QTcpSocket *_tcp;
    QNetworkAccessManager *_manager;
    QNetworkReply *_reply;
    int _vk_player_id;
    QString _firstName;
    QString _lastName;
private slots:
    void Connected();
};

#endif // NET
