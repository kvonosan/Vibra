#include "player.h"
#include <QtDebug>

Player::Player(QObject *parent)
    : QObject(parent)
{
    _manager = new QNetworkAccessManager(this);
    connect(_manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(replyFinished(QNetworkReply*)));
    _manager->get(QNetworkRequest(QUrl("https://oauth.vk.com/access_token")));
}

Player::~Player()
{
    delete _manager;
}

void Player::replyFinished(QNetworkReply *reply)
{
    qDebug() << "Reply";
    qDebug() << reply->readAll() << "/n";
}
