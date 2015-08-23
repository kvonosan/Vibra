#ifndef VK_AUTH
#define VK_AUTH

#include <QString>
#include <QtNetwork>

class Net: public QObject
{
    Q_OBJECT
public:
    Net(QString client_id, QString client_secret);
    ~Net();
    QString _access_token;
    QNetworkAccessManager *_manager;
    QNetworkReply *_reply;
};

#endif // VK_AUTH
