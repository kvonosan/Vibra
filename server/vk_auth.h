#ifndef VK_AUTH
#define VK_AUTH

#include <QString>
#include <QtNetwork>

class vk_auth: public QObject
{
    Q_OBJECT
public:
    vk_auth(QString client_id, QString client_secret);
    ~vk_auth();
    QString _access_token;
};

#endif // VK_AUTH
