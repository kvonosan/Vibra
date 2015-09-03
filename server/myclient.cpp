#include "myclient.h"

MyClient::MyClient(QObject *parent) :
    QObject(parent)
{
    QThreadPool::globalInstance()->setMaxThreadCount(5);
    _delete = false;
}

MyClient::~MyClient()
{
    delete _socket;
    delete _player;
}

void MyClient::setSocket(qintptr descriptor)
{
    _socket = new QTcpSocket(this);

    qDebug() << "A new socket created!";

    connect(_socket, SIGNAL(connected()), this, SLOT(connected()));
    connect(_socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(_socket, SIGNAL(readyRead()), this, SLOT(readyRead()));

    _socket->setSocketDescriptor(descriptor);
    _player = new Player();

    qDebug() << " Client connected at " << descriptor;
}

void MyClient::connected()
{
    qDebug() << "Client connected event";
}

void MyClient::disconnected()
{
    qDebug() << "Client disconnected";
}

void MyClient::VkAuth(QString access_token)
{
    _manager = new QNetworkAccessManager(0);
    _reply = _manager->get(QNetworkRequest(QUrl("https://api.vk.com/method/users.get?v=5.37&"+access_token)));
    QEventLoop loop;
    connect(_reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();
    QByteArray recv = _reply->readAll();
    QString recv_str = QString::fromUtf8(recv.toStdString().c_str());
    if (recv_str.contains("error"))
    {
        QByteArray array;
        QDataStream stream(&array, QIODevice::WriteOnly);
        stream << 0;
        _socket->write(array.toHex());
        _socket->close();
        _delete = true;
    } else
    {
        QJsonDocument document = QJsonDocument::fromJson(recv);
        QJsonObject object = document.object();
        QJsonValue value = object.value("response");
        QJsonArray array1 = value.toArray();
        foreach (const QJsonValue & v, array1)
        {
            _player->_player_id_vk =  v.toObject().value("id").toInt();
            //_firstName = v.toObject().value("first_name").toString();
            //_lastName = v.toObject().value("last_name").toString();
        }
        _player->Search();
        QString str =  QString("id") + " " + QString::number(_player->_player_id);
        _socket->write(str.toUtf8());
    }
    delete _manager;
}

void MyClient::readyRead()
{
    //qDebug() << "MyClient::readyRead()";
    QByteArray array = _socket->readAll();
    QString str = QString::fromUtf8(array.toStdString().c_str());
    if (str.startsWith("token"))
    {
        QStringList list = str.split(" ");
        VkAuth(list[1]);
        _player->newPlayer();
        _player->AddToMap();
    } else if (str.startsWith("getinfo"))
    {
        SendInfo();
    }
}

void MyClient::SendInfo()
{
    QSqlQuery q1;
    q1.prepare("SELECT rating, gold, credits, race, ship, level FROM player "
               "WHERE player_id=:id");
    q1.bindValue(":id", _player->_player_id);
    q1.exec();
    int rating = 0, exp = 0, gold = 0, credits = 0, race = 0, ship = 0,
            ship_body = 0, level = 0;
    QString race1, ship_body1;
    if (q1.next())
    {
        rating = q1.value(0).toInt();
        gold = q1.value(1).toInt();
        credits = q1.value(2).toInt();
        race = q1.value(3).toInt();
        ship = q1.value(4).toInt();
        level = q1.value(5).toInt();
    }
    if (rating == 0)
    {
        qDebug() << "Corrupted rating on player_id = " <<  _player->_player_id;
    } else
    {
        QSqlQuery q2;
        q2.prepare("SELECT exp FROM rating WHERE rating_id=:id");
        q2.bindValue(":id", rating);
        q2.exec();
        if (q2.next())
        {
            exp = q2.value(0).toInt();
        }
        QSqlQuery q3;
        q3.prepare("SELECT name FROM race WHERE race_id=:id");
        q3.bindValue(":id", race);
        q3.exec();
        if (q3.next())
        {
            race1 = q3.value(0).toString();
        }
        QSqlQuery q4;
        q4.prepare("SELECT ship_body FROM ship WHERE ship_id=:id");
        q4.bindValue(":id", ship);
        q4.exec();
        if (q4.next())
        {
            ship_body = q4.value(0).toInt();
        }
        QSqlQuery q5;
        q5.prepare("SELECT class FROM ship_body WHERE body_id=:id");
        q5.bindValue(":id", ship_body);
        q5.exec();
        if (q5.next())
        {
            ship_body1 = q5.value(0).toString();
        }
        /*_string = " Опыт: " + _experience + "\n" +
                " Золото: " + _gold + "\n" + " Кредиты: " + _credits + "\n" +
                " Раса: " + _race + "\n" + " Корабль: " + _ship + "\n" +
                " Уровень: " + _level + "\n";*/
        //exp, gold, credits, race1, ship_body1, level
        QJsonObject obj;
        obj["exp"] = exp;
        obj["gold"] = gold;
        obj["credits"] = credits;
        obj["race"] = race1;
        obj["ship_body"] = ship_body1;
        obj["level"] = level;
        //QJsonObject player;
        //player["player"] = obj;
        QJsonDocument doc(obj);
        QString str = QString("info") + " " + QString::fromUtf8(doc.toJson(QJsonDocument::Compact).toStdString().c_str());
        _socket->write(str.toUtf8());
    }
}
