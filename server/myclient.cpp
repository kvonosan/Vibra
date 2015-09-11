#include "player.h"
#include "myclient.h"

MyClient::MyClient(Loader *loader, QObject *parent) :
    QObject(parent)
{
    _delete = false;
    if (loader == NULL)
    {
        qDebug() << "Error loader == NULL";
        exit(-1);
    }
    _loader = loader;
    _fireNpc = NULL;
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
    QByteArray array = _socket->readAll();
    QString str = QString::fromUtf8(array.toStdString().c_str());
    //qDebug() << str;
    if (str.startsWith("token"))
    {
        QStringList list = str.split(" ");
        VkAuth(list[1]);
        _player->newPlayer();
        _player->AddToMap();
    } else if (str.startsWith("getinfo"))
    {
        SendInfo();
    } else if (str.startsWith("getmap"))
    {
        QString map = QString("map ") + _loader->Bufferize(_player);
        _socket->write(map.toUtf8());
    } else if (str.startsWith("left"))
    {
        bool generate = false;
        bool map_not_found = false;
        bool hod = true;
        QSqlQuery q8;
        q8.prepare("SELECT inleft FROM map WHERE map_id=:map_id");
        q8.bindValue(":map_id", _player->_map);
        q8.exec();
        int inleft = 0;
        if (q8.next())
        {
            inleft = q8.value(0).toInt();
        }
        if (inleft == 0)
        {
            map_not_found = true;
        }
        if (_player->_pos%32 == 0 && map_not_found)
        {
            _loader->GenerateLeftMap(_player);
            generate = true;
        } else
        {
            int pos = _player->_pos-1;
            int last_pos = _player->_pos;
            if (pos == -1)
            {
                _player->_pos = 31;
                pos = 31;
            } else if (last_pos%32 == 0)
            {
                _player->_pos = _player->_pos+31;
                pos = _player->_pos;
            }
            if (last_pos%32 == 0)
            {
                hod = false;
                QSqlQuery q2;
                q2.prepare("UPDATE player SET map=:map,pos=:pos WHERE player_id = :id");
                q2.bindValue(":map", inleft);
                q2.bindValue(":pos", pos);
                q2.bindValue(":id", _player->_player_id);
                q2.exec();
                int last = _player->_map;
                _player->_map = inleft;
                QSqlQuery q3;
                q3.prepare("SELECT data FROM map WHERE map_id=:map_id");
                q3.bindValue(":map_id", last);
                q3.exec();
                QString data;
                if (q3.next())
                {
                    data = q3.value(0).toString();
                }
                QChar symbol = data[last_pos];
                data[last_pos] = ' ';
                QSqlQuery q5;
                q5.prepare("UPDATE map SET data=:data WHERE map_id=:map_id");
                q5.bindValue(":map_id", last);
                q5.bindValue(":data", data);
                q5.exec();
                QSqlQuery q4;
                q4.prepare("SELECT data FROM map WHERE map_id=:map_id");
                q4.bindValue(":map_id", _player->_map);
                q4.exec();
                QString data1;
                if (q4.next())
                {
                    data1 = q4.value(0).toString();
                }
                data1[pos] = symbol;
                QSqlQuery q9;
                q9.prepare("UPDATE map SET data=:data WHERE map_id=:map_id");
                q9.bindValue(":map_id", _player->_map);
                q9.bindValue(":data", data1);
                q9.exec();
            }
        }
        if (_player->_pos - 1 >= 0 && !generate && hod)
        {
            int border = (_player->_pos - 1)%32;
            if (border != 31)
            {
                QSqlQuery q1;
                q1.prepare("SELECT data FROM map WHERE map_id=:m");
                q1.bindValue(":m", _player->_map);
                q1.exec();
                QString data;
                if (q1.next())
                {
                    data = q1.value(0).toString();
                }
                if (data[_player->_pos-1] == ' ')
                {
                    data[_player->_pos-1] = data[_player->_pos];
                    data[_player->_pos] = ' ';
                    _player->_pos = _player->_pos-1;
                }
                QSqlQuery q6;
                q6.prepare("UPDATE map SET data=:data WHERE map_id=:id");
                q6.bindValue(":id", _player->_map);
                q6.bindValue(":data", data);
                q6.exec();
                QSqlQuery q7;
                q7.prepare("UPDATE player SET pos=:p WHERE player_id=:id");
                q7.bindValue(":id", _player->_player_id);
                q7.bindValue(":p", _player->_pos);
                q7.exec();
            }
        }
    } else if (str.startsWith("right"))
    {
        bool generate = false;
        bool map_not_found = false;
        bool hod = true;
        QSqlQuery q8;
        q8.prepare("SELECT inright FROM map WHERE map_id=:map_id");
        q8.bindValue(":map_id", _player->_map);
        q8.exec();
        int inright = 0;
        if (q8.next())
        {
            inright = q8.value(0).toInt();
        }
        if (inright == 0)
        {
            map_not_found = true;
        }
        if (_player->_pos%32 == 31 && map_not_found)
        {
            _loader->GenerateRightMap(_player);
            generate = true;
        } else
        {
            int pos = _player->_pos%32;
            if (pos == 31)
            {
                hod = false;
                int last_pos = _player->_pos;
                _player->_pos = _player->_pos-31;
                pos = _player->_pos;
                QSqlQuery q2;
                q2.prepare("UPDATE player SET map=:map,pos=:pos WHERE player_id = :id");
                q2.bindValue(":map", inright);
                q2.bindValue(":pos", pos);
                q2.bindValue(":id", _player->_player_id);
                q2.exec();
                int last = _player->_map;
                _player->_map = inright;
                QSqlQuery q3;
                q3.prepare("SELECT data FROM map WHERE map_id=:map_id");
                q3.bindValue(":map_id", last);
                q3.exec();
                QString data;
                if (q3.next())
                {
                    data = q3.value(0).toString();
                }
                QChar symbol = data[last_pos];
                data[last_pos] = ' ';
                QSqlQuery q5;
                q5.prepare("UPDATE map SET data=:data WHERE map_id=:map_id");
                q5.bindValue(":map_id", last);
                q5.bindValue(":data", data);
                q5.exec();
                QSqlQuery q4;
                q4.prepare("SELECT data FROM map WHERE map_id=:map_id");
                q4.bindValue(":map_id", _player->_map);
                q4.exec();
                QString data1;
                if (q4.next())
                {
                    data1 = q4.value(0).toString();
                }
                data1[pos] = symbol;
                QSqlQuery q9;
                q9.prepare("UPDATE map SET data=:data WHERE map_id=:map_id");
                q9.bindValue(":map_id", _player->_map);
                q9.bindValue(":data", data1);
                q9.exec();
            }
        }
        if (_player->_pos + 1 < 768 && !generate && hod)
        {
            int border = (_player->_pos + 1)%32;
            if (border != 0)
            {
                QSqlQuery q1;
                q1.prepare("SELECT data FROM map WHERE map_id=:m");
                q1.bindValue(":m", _player->_map);
                q1.exec();
                QString data;
                if (q1.next())
                {
                    data = q1.value(0).toString();
                }
                if (data[_player->_pos+1] == ' ')
                {
                    data[_player->_pos+1] = data[_player->_pos];
                    data[_player->_pos] = ' ';
                    _player->_pos = _player->_pos+1;
                }
                QSqlQuery q6;
                q6.prepare("UPDATE map SET data=:data WHERE map_id=:id");
                q6.bindValue(":id", _player->_map);
                q6.bindValue(":data", data);
                q6.exec();
                QSqlQuery q7;
                q7.prepare("UPDATE player SET pos=:p WHERE player_id=:id");
                q7.bindValue(":id", _player->_player_id);
                q7.bindValue(":p", _player->_pos);
                q7.exec();
            }
        }
    } else if (str.startsWith("top"))
    {
        bool generate = false;
        bool map_not_found = false;
        bool hod = true;
        QSqlQuery q8;
        q8.prepare("SELECT intop FROM map WHERE map_id=:map_id");
        q8.bindValue(":map_id", _player->_map);
        q8.exec();
        int intop = 0;
        if (q8.next())
        {
            intop = q8.value(0).toInt();
        }
        if (intop == 0)
        {
            map_not_found = true;
        }
        if (_player->_pos-32<0 && map_not_found)
        {
            _loader->GenerateTopMap(_player);
            generate = true;
        } else
        {
            int pos = _player->_pos-32;
            if (pos < 0)
            {
                hod = false;
                int last_pos = _player->_pos;
                _player->_pos = 768 - 32 + _player->_pos;
                pos = _player->_pos;
                QSqlQuery q2;
                q2.prepare("UPDATE player SET map=:map,pos=:pos WHERE player_id = :id");
                q2.bindValue(":map", intop);
                q2.bindValue(":pos", pos);
                q2.bindValue(":id", _player->_player_id);
                q2.exec();
                int last = _player->_map;
                _player->_map = intop;
                QSqlQuery q3;
                q3.prepare("SELECT data FROM map WHERE map_id=:map_id");
                q3.bindValue(":map_id", last);
                q3.exec();
                QString data;
                if (q3.next())
                {
                    data = q3.value(0).toString();
                }
                QChar symbol = data[last_pos];
                data[last_pos] = ' ';
                QSqlQuery q5;
                q5.prepare("UPDATE map SET data=:data WHERE map_id=:map_id");
                q5.bindValue(":map_id", last);
                q5.bindValue(":data", data);
                q5.exec();
                QSqlQuery q4;
                q4.prepare("SELECT data FROM map WHERE map_id=:map_id");
                q4.bindValue(":map_id", _player->_map);
                q4.exec();
                QString data1;
                if (q4.next())
                {
                    data1 = q4.value(0).toString();
                }
                data1[pos] = symbol;
                QSqlQuery q9;
                q9.prepare("UPDATE map SET data=:data WHERE map_id=:map_id");
                q9.bindValue(":map_id", _player->_map);
                q9.bindValue(":data", data1);
                q9.exec();
            }
        }
        if (_player->_pos-32 >= 0 && !generate && hod)
        {
            QSqlQuery q1;
            q1.prepare("SELECT data FROM map WHERE map_id=:m");
            q1.bindValue(":m", _player->_map);
            q1.exec();
            QString data;
            if (q1.next())
            {
                data = q1.value(0).toString();
            }
            if (data[_player->_pos-32] == ' ')
            {
                data[_player->_pos-32] = data[_player->_pos];
                data[_player->_pos] = ' ';
                _player->_pos = _player->_pos-32;
            }
            QSqlQuery q6;
            q6.prepare("UPDATE map SET data=:data WHERE map_id=:id");
            q6.bindValue(":id", _player->_map);
            q6.bindValue(":data", data);
            q6.exec();
            QSqlQuery q7;
            q7.prepare("UPDATE player SET pos=:p WHERE player_id=:id");
            q7.bindValue(":id", _player->_player_id);
            q7.bindValue(":p", _player->_pos);
            q7.exec();
        }
    } else if (str.startsWith("bottom"))
    {
        bool generate = false;
        bool map_not_found = false;
        bool hod = true;
        QSqlQuery q8;
        q8.prepare("SELECT inbottom FROM map WHERE map_id=:map_id");
        q8.bindValue(":map_id", _player->_map);
        q8.exec();
        int inbottom = 0;
        if (q8.next())
        {
            inbottom = q8.value(0).toInt();
        }
        if (inbottom == 0)
        {
            map_not_found = true;
        }
        if (_player->_pos+32 > 768 && map_not_found)
        {
            _loader->GenerateBottomMap(_player);
            generate = true;
        } else
        {
            int pos = _player->_pos+32;
            if (pos >= 768)
            {
                hod = false;
                int last_pos = _player->_pos;
                _player->_pos = _player->_pos+32-768;
                pos = _player->_pos;
                QSqlQuery q2;
                q2.prepare("UPDATE player SET map=:map,pos=:pos WHERE player_id = :id");
                q2.bindValue(":map", inbottom);
                q2.bindValue(":pos", pos);
                q2.bindValue(":id", _player->_player_id);
                q2.exec();
                int last = _player->_map;
                _player->_map = inbottom;
                QSqlQuery q3;
                q3.prepare("SELECT data FROM map WHERE map_id=:map_id");
                q3.bindValue(":map_id", last);
                q3.exec();
                QString data;
                if (q3.next())
                {
                    data = q3.value(0).toString();
                }
                QChar symbol = data[last_pos];
                data[last_pos] = ' ';
                QSqlQuery q5;
                q5.prepare("UPDATE map SET data=:data WHERE map_id=:map_id");
                q5.bindValue(":map_id", last);
                q5.bindValue(":data", data);
                q5.exec();
                QSqlQuery q4;
                q4.prepare("SELECT data FROM map WHERE map_id=:map_id");
                q4.bindValue(":map_id", _player->_map);
                q4.exec();
                QString data1;
                if (q4.next())
                {
                    data1 = q4.value(0).toString();
                }
                data1[pos] = symbol;
                QSqlQuery q9;
                q9.prepare("UPDATE map SET data=:data WHERE map_id=:map_id");
                q9.bindValue(":map_id", _player->_map);
                q9.bindValue(":data", data1);
                q9.exec();
            }
        }
        if (_player->_pos+32 < 768 && !generate && hod)
        {
            QSqlQuery q1;
            q1.prepare("SELECT data FROM map WHERE map_id=:m");
            q1.bindValue(":m", _player->_map);
            q1.exec();
            QString data;
            if (q1.next())
            {
                data = q1.value(0).toString();
            }
            if (data[_player->_pos+32] == ' ')
            {
                data[_player->_pos+32] = data[_player->_pos];
                data[_player->_pos] = ' ';
                _player->_pos = _player->_pos+32;
            }
            QSqlQuery q6;
            q6.prepare("UPDATE map SET data=:data WHERE map_id=:id");
            q6.bindValue(":id", _player->_map);
            q6.bindValue(":data", data);
            q6.exec();
            QSqlQuery q7;
            q7.prepare("UPDATE player SET pos=:p WHERE player_id=:id");
            q7.bindValue(":id", _player->_player_id);
            q7.bindValue(":p", _player->_pos);
            q7.exec();
        }
    } else if(str.startsWith("getmypos"))
    {
        QString send = QString("yourpos ") + QString::number(_player->_pos);
        _socket->write(send.toUtf8());
    } else if (str.startsWith("fire"))
    {
        str.replace("fire ", "");
        if (_fireNpc == NULL)
        {
            _fireNpc = new Npc(_player);
        }
        if (_fireNpc->_killed)
        {
            delete _fireNpc;
            _fireNpc = NULL;
            QString str1 = "killed";
            _socket->write(str1.toUtf8());
            _socket->flush();
        }
        if (_fireNpc != NULL)
        {
            int num = str.toInt();
            if (num != _player->_pos && num > -1 && num <=768)
            {
                if (_fireNpc->fireToNpc(num))
                {
                    QString str1 = "fire " + str;
                    int life = GetLife(num);
                    str1 = str1 + " " + QString::number(life);
                    _socket->write(str1.toUtf8());
                    _socket->flush();
                }
            }
        }
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
        QJsonObject obj;
        obj["exp"] = exp;
        obj["gold"] = gold;
        obj["credits"] = credits;
        obj["race"] = race1;
        obj["ship_body"] = ship_body1;
        obj["level"] = level;
        QJsonDocument doc(obj);
        QString str = QString("info") + " " + QString::fromUtf8(doc.toJson(QJsonDocument::Compact).toStdString().c_str());
        _socket->write(str.toUtf8());
    }
}

int MyClient::GetLife(int pos)
{
    QSqlQuery q1;
    q1.prepare("SELECT map FROM player WHERE player_id=:id");
    q1.bindValue(":id", _player->_player_id);
    q1.exec();
    int map = 0;
    if (q1.next())
    {
        map = q1.value(0).toInt();
    }
    if (map == 0)
    {
        qDebug() << "Corrupted map on player_id = " <<  _player->_player_id;
    } else
    {
        QSqlQuery q2;
        q2.prepare("SELECT life, energy, fuel, armor, fire, ship_id FROM ship_point WHERE map=:map AND pos=:pos");
        q2.bindValue(":map", map);
        q2.bindValue(":pos", pos);
        q2.exec();
        int life = 0;
        if (q2.next())
        {
            life = q2.value(0).toInt();
        }
        return life;
    }
    return 0;
}
