#ifndef VK_AUTH
#define VK_AUTH

#include <QString>
#include <QtNetwork>

class VkAuth: public QObject
{
    Q_OBJECT
public:
    VkAuth(QString client_id, QString client_secret);
    ~VkAuth();
    QString _access_token;
};

#endif // VK_AUTH
