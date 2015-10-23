#include "player.h"
#include "myclient.h"

MyClient::MyClient(Loader *loader, QObject *parent) :
    QObject(parent)
{
    _delete = false;
    if (loader == NULL)
    {
        qDebug() << "Ошибка loader == NULL.";
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
    qDebug() << "Создан новый сокет.";
    connect(_socket, SIGNAL(connected()), this, SLOT(connected()));
    connect(_socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(_socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    _socket->setSocketDescriptor(descriptor);
    _player = new Player(_loader);
    qDebug() << "Клиент подсоединен на дескриптор " << descriptor << ".";
    _loader->Reconnect();
}

void MyClient::connected()
{
    qDebug() << "Клиент подсоединился.";
}

void MyClient::disconnected()
{
    qDebug() << "Клиент отсоединился.";
}

void MyClient::readyRead()
{
    //qDebug() << "readyread";
    _player->_level = 0;
    _player->_bonus = 0;
    QByteArray array = _socket->readAll();
    QString str = QString::fromUtf8(array.toStdString().c_str());
    //qDebug() << str;
    if (str.startsWith("id"))
    {
        str.replace("id ", "");
        _player->_player_id_vk = str.toInt();
        _player->News();
        _player->Search();
        QString str =  QString("id") + " " + QString::number(_player->_player_id);;
        _socket->write(str.toUtf8());
        _player->newPlayer();
        _player->AddToMap();
    } else if (str.startsWith("getinfo"))
    {
        SendInfo();
    } else if (str.startsWith("getmap"))
    {
        QString map = QString("map ") + QString::number(_player->_pos) + ";"  + _loader->Bufferize(_player);
        _socket->write(map.toUtf8());
    } else if (str.startsWith("left"))
    {
        if (!_loader->_db.isOpen())
        {
            if (!_loader->_db.open())
            {
                qDebug() << "Ошибка соединения к базе данных:" << _loader->_db.lastError();
                exit(-1);
            }
        }
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
        if (!_loader->_db.isOpen())
        {
            if (!_loader->_db.open())
            {
                qDebug() << "Ошибка соединения к базе данных:" << _loader->_db.lastError();
                exit(-1);
            }
        }
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
        if (!_loader->_db.isOpen())
        {
            if (!_loader->_db.open())
            {
                qDebug() << "Ошибка соединения к базе данных:" << _loader->_db.lastError();
                exit(-1);
            }
        }
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
        if (!_loader->_db.isOpen())
        {
            if (!_loader->_db.open())
            {
                qDebug() << "Ошибка соединения к базе данных:" << _loader->_db.lastError();
                exit(-1);
            }
        }
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
        if (!_loader->_db.isOpen())
        {
            if (!_loader->_db.open())
            {
                qDebug() << "Ошибка соединения к базе данных:" << _loader->_db.lastError();
                exit(-1);
            }
        }
        str.replace("fire ", "");
        if (_fireNpc == NULL)
        {
            _fireNpc = new Npc(_player, _loader);
        }
        if (_fireNpc != NULL)
        {
            int num = str.toInt();
            if (num != _player->_pos && num > -1 && num <=768)
            {
                if (_fireNpc->fireToNpc(num))
                {
                    if (_fireNpc->_killed)
                    {
                        QString str1 = "killed";
                        str1 = str1 + " " + QString::number(_player->_level);
                        if (_player->_bonus)
                        {
                            str1 = str1 + " bonus";
                            if (_player->_bonus == 1)
                            {
                                str1 = str1 + " cartograph";
                            } else if (_player->_bonus == 2)
                            {
                                str1 = str1 + " droid";
                            }
                        }
                        _socket->write(str1.toUtf8());
                        _socket->flush();
                        delete _fireNpc;
                        _fireNpc = NULL;
                    } else
                    {
                        QString str1 = "fire " + str;
                        int life_enemy = GetLife(num);
                        QSqlQuery q1;
                        q1.prepare("SELECT ship FROM player WHERE player_id=:player_id");
                        q1.bindValue(":player_id", _player->_player_id);
                        q1.exec();
                        int ship = 0;
                        if (q1.next())
                        {
                            ship = q1.value(0).toInt();
                        }
                        if (ship == 0)
                        {
                            qDebug() << "Error: corrupted ship.";
                            exit(-1);
                        }
                        QSqlQuery q2;
                        q2.prepare("SELECT life FROM ship_point WHERE ship_id=:ship");
                        q2.bindValue(":ship", ship);
                        q2.exec();
                        int life = 0;
                        if (q2.next())
                        {
                            life = q2.value(0).toInt();
                        }
                        if (life == 0)
                        {
                            qDebug() << "Error: corrupted life.";
                            exit(-1);
                        }
                        str1 = str1 + " " + QString::number(life_enemy) + " " + QString::number(life);
                        _socket->write(str1.toUtf8());
                        _socket->flush();
                    }
                }
            }
        }
    } else if (str.startsWith("getnews"))
    {
        QSqlQuery q1;
        q1.prepare("SELECT text FROM news ORDER BY news_id DESC LIMIT 1");
        q1.exec();
        qDebug() << q1.lastError();
        QString str = "Нет новостей.";
        if (q1.next())
        {
            str = "news " + q1.value(0).toString();
        }
        _socket->write(str.toUtf8());
        _socket->flush();
    } else if (str.startsWith("getrating"))
    {
        QSqlQuery q1;
        q1.prepare("SELECT player_id, exp, kills, death, mission, credits, fights FROM rating ORDER BY exp");
        q1.exec();
        int p_id = 0;
        if (q1.next())
        {
            p_id = q1.value(0).toInt();
            QSqlQuery q2;
            q2.prepare("SELECT vk_id FROM player WHERE player_id=:id");
            q2.bindValue(":id", p_id);
            q2.exec();
            int vk_id = 0;
            if (q2.next())
            {
                vk_id = q2.value(0).toInt();
            }
            QString name = GetVKName(vk_id);
            if (name.size() > 0)
            {
                //addToJSON
            }
        }
    }
}

void MyClient::SendInfo()
{
    if (!_loader->_db.isOpen())
    {
        if (!_loader->_db.open())
        {
            qDebug() << "Ошибка соединения к базе данных:" << _loader->_db.lastError();
            exit(-1);
        }
    }
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
        qDebug() << "Поврежденный рейтинг у player_id = " <<  _player->_player_id;
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
    if (!_loader->_db.isOpen())
    {
        if (!_loader->_db.open())
        {
            qDebug() << "Ошибка соединения к базе данных:" << _loader->_db.lastError();
            exit(-1);
        }
    }
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
        qDebug() << "Поврежденная карта у player_id = " <<  _player->_player_id;
    } else
    {
        QSqlQuery q2;
        q2.prepare("SELECT life, armor FROM ship_point WHERE map=:map AND pos=:pos");
        q2.bindValue(":map", map);
        q2.bindValue(":pos", pos);
        q2.exec();
        int life = 0, armor = 0;
        if (q2.next())
        {
            life = q2.value(0).toInt();
            armor = q2.value(1).toInt();
        }
        int ret = armor + life;
        return ret;
    }
    return 0;
}

QString MyClient::GetVKName(int id)
{
    //
}
