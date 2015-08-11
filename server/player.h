#ifndef PLAYER
#define PLAYER

#include <QtNetwork>

class Player: public QObject
{
    Q_OBJECT
public:
    Player(QObject *parent=0);
    ~Player();
private:
    QNetworkAccessManager *_manager;
private slots:
    void replyFinished(QNetworkReply *reply);
};

#endif // PLAYER
