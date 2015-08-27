#ifndef VK_AUTH
#define VK_AUTH

#include <QString>
#include <QtNetwork>

class Net: public QObject
{
    Q_OBJECT
public:
    ~Net();
    Net(QString client_id, QString client_secret);
    QString _access_token;
    QNetworkReply *_reply;
    QNetworkAccessManager *_manager;
};

#endif // VK_AUTH
