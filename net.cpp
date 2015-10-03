#include "net.h"
#include "hero.h"
#include <QMessageBox>

Net::Net()
{
    _port = 33333;
    _connected = false;
    _tcp = new QTcpSocket();
    _vk_connected = false;
    _disconnect = true;
    _killed = false;
    QFile file("settings.json");
    if (!file.open(QIODevice::ReadOnly))
    {
        file.open(QIODevice::ReadWrite);
        QJsonObject obj;
        obj["hostname"] = "127.0.0.1";
        _hostname = "127.0.0.1";
        QJsonDocument doc(obj);
        file.write(doc.toJson());
        file.close();
        qDebug() << "Файл настроек не найден, загружены стандартные настройки.";
    } else
    {
        QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
        QJsonObject obj = doc.object();
        _hostname = obj["hostname"].toString();
        qDebug() << "Настройки загружены.";
    }
}

Net::~Net()
{
    delete _tcp;
}

bool Net::VKConnected()
{
    if (_vk_connected)
    {
        return true;
    }
    QString filename = "token.txt";
    QFile file( filename );
    QString token;
    if ( file.open(QIODevice::ReadOnly) )
    {
        QTextStream stream( &file );
        stream >> _access_token;
        stream >> _vk_user_id;
        QStringList user_id = _vk_user_id.split("=");
        QString id = user_id.at(1);
        QStringList user_id_lst = id.split("\"");
        _vk_user_id = user_id_lst.at(0);
    }
    if (token.startsWith("error"))
    {
        return false;
    } else
    {
        QNetworkAccessManager *manager = new QNetworkAccessManager(0);
        QNetworkReply *netReply = manager->get(QNetworkRequest(QUrl("https://api.vk.com/method/friends.getOnline?v=5.37&" + _access_token)));
        QEventLoop loop;
        connect(netReply, SIGNAL(finished()), &loop, SLOT(quit()));
        loop.exec();
        QString reply = netReply->readAll();
        if (reply.contains("response"))
        {
            _vk_connected = true;
            return true;
        } else
        {
            return false;
        }
        delete manager;
    }
    return false;
}

void Net::GetVKName()
{
    _manager = new QNetworkAccessManager(0);
    _reply = _manager->get(QNetworkRequest(QUrl("https://api.vk.com/method/users.get?v=5.37&user_ids="+_vk_user_id)));
    QEventLoop loop;
    connect(_reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();
    QByteArray recv = _reply->readAll();
    QJsonDocument document = QJsonDocument::fromJson(recv);
    QJsonObject object = document.object();
    QJsonValue value = object.value("response");
    QJsonArray array = value.toArray();
    foreach (const QJsonValue & v, array)
    {
        _vk_player_id =  v.toObject().value("id").toInt();
        _firstName = v.toObject().value("first_name").toString();
        _lastName = v.toObject().value("last_name").toString();
    }
    delete _manager;
}

void Net::NetConnect(Base *base)
{
    if (base == NULL)
    {
        qDebug() << "Error: base = NULL.";
        exit(-1);
    }
    _base = base;
    connect(_tcp, SIGNAL(connected()), this, SLOT(Connected()));
    connect(_tcp, SIGNAL(disconnected()), this, SLOT(Disconnected()));
    _tcp->connectToHost(_hostname, _port);
    //_tcp->waitForConnected(2000);
    //_tcp->connectToHost("127.0.0.1", _port);
    _connected = true;
    _authorized = false;
}

void Net::Connected()
{
    QString str = "id " + _vk_user_id;
    _tcp->write(str.toUtf8());
    connect(_tcp, SIGNAL(readyRead()), this, SLOT(readyRead()));
}

void Net::Disconnected()
{
    if (_disconnect)
    {
        QMessageBox* pmbx = new QMessageBox("Соединение с сервером",
                            "<b>Соединение прервано!</b>",
                            QMessageBox::Information,
                            QMessageBox::NoButton,
                            QMessageBox::Ok,
                            QMessageBox::NoButton);
        pmbx->exec();
        delete pmbx;
        exit(-1);
    }
}

void Net::readyRead()
{
    _level = 0;
    QByteArray array = _tcp->readAll();
    QString str = QString::fromUtf8(array.toStdString().c_str());
    //qDebug() << str;
    if (str.startsWith("id"))
    {
        QStringList list = str.split(" ");
        bool ok, ok1;
        _player_id = list[1].toInt(&ok, 10);
        _mypos = list[2].toInt(&ok1, 10);
        if (!ok || !ok1)
        {
            qDebug() << "Net read error.";
            exit(-1);
        }
        if (_player_id != 0)
        {
            _authorized = true;
            GetVKName();
            _base->_hero_obj->_name = _firstName + " "+ _lastName;
        }
    } else if (str.startsWith("info"))
    {
        str.replace("info", "");
        QJsonObject object;
        QJsonDocument document = QJsonDocument::fromJson(str.toUtf8());
        if (!document.isNull())
        {
            if (document.isObject())
            {
                object = document.object();
            }
        } else
        {
            qDebug() << "Parse json error.";
        }
        int exp = 0, gold = 0, credits = 0, level = 0;
        QString race, ship_body;
        exp = object["exp"].toInt();
        gold = object["gold"].toInt();
        credits = object["credits"].toInt();
        race = object["race"].toString();
        ship_body = object["ship_body"].toString();
        level = object["level"].toInt();
        _base->_hero_obj->_experience = QString::number(exp);
        _base->_hero_obj->_gold = QString::number(gold);
        _base->_hero_obj->_credits = QString::number(credits);
        _base->_hero_obj->_race = race;
        _base->_hero_obj->_ship = "Класс "+ ship_body;
        _base->_hero_obj->_level = QString::number(level);
    } else if (str.startsWith("map"))
    {
        str.replace("map ", "");
        int g=0;
        for(int j=0; j < 24; j++)
            for(int i=0; i < 32; i++)
            {
                Symbol *sym = _base->_fly->_grid->GetSymbolAt(i, j);
                sym->_symbol = str[g];
                if (str[g] == 'A' || str[g] == 'B' || str[g] == 'C'
                        || str[g] == 'D' || str[g] == 'E')
                {
                    sym->_attacked = true;
                }
                g++;
            }
        _base->_mainwindow->renderNow();
    } else if (str.startsWith("yourpos"))
    {
        str.replace("yourpos ", "");
        _mypos = str.toInt();
    } else if (str.startsWith("fire"))
    {
        str.replace("fire ", "");
        QStringList list = str.split(" ");
        _firepos = list[0].toInt();
        _popup->_life_enemy = list[1].toInt();
        _popup->_life = list[2].toInt();
    } else if (str.startsWith("killed"))
    {
        _killed = true;
        str.replace("killed ", "");
        _level = str.toInt();
        if (_level < 0 || _level > 100)
        {
            _level = 0;
        }
    } else if (str.startsWith("params"))
    {
        str.replace("params ", "");
        QJsonObject object;
        QJsonDocument document = QJsonDocument::fromJson(str.toUtf8());
        if (!document.isNull())
        {
            if (document.isObject())
            {
                object = document.object();
            }
        } else
        {
            qDebug() << "Parse json error.";
        }
        _life = object["life"].toInt();
        _energy = object["energy"].toInt();
        _armor = object["armor"].toInt();
        _fuel = object["fuel"].toInt();
        _net_speed = object["net_speed"].toInt();
        _cartograph_link = object["cartograph_link"].toInt();
        _grab_points = object["grab_points"].toInt();
        _radar_ships = object["radar_ships"].toInt();
        _scaner_predm = object["scaner_predm"].toInt();
        _fire = object["fire"].toInt();
        _fire_speed = object["fire_speed"].toInt();
        _fire_link = object["fire_link"].toInt();
        BufferizeMap();
    }
}

void Net::BufferizeMap()
{
    QString str = QString("getmap");
    _tcp->write(str.toUtf8());
}

void Net::Left()
{
    if (!_fire)
    {
        QString str = "left";
        _tcp->write(str.toUtf8());
        _tcp->flush();
        GetMyPos();
    }
}

void Net::Right()
{
    if (!_fire)
    {
        QString str = "right";
        _tcp->write(str.toUtf8());
        _tcp->flush();
        GetMyPos();
    }
}

void Net::Top()
{
    if (!_fire)
    {
        QString str = "top";
        _tcp->write(str.toUtf8());
        _tcp->flush();
        GetMyPos();
    }
}

void Net::Bottom()
{
    if (!_fire)
    {
        QString str = "bottom";
        _tcp->write(str.toUtf8());
        _tcp->flush();
        GetMyPos();
    }
}

void Net::GetMyPos()
{
    QString str = "getmypos";
    _tcp->write(str.toUtf8());
    _tcp->flush();
    _tcp->waitForReadyRead(3000);
}

void Net::Fire(int pos, Popup *popup)
{
    if (popup == NULL)
    {
        qDebug() << "Error: popup == NULL." ;
        exit(-1);
    }
    _popup = popup;
    _firepos = -1;
    QString str = "fire " + QString::number(pos);
    _tcp->write(str.toUtf8());
    _tcp->flush();
}

void Net::GetResource(int pos)
{
    QString str = "getres " + QString::number(pos);
    _tcp->write(str.toUtf8());
    _tcp->flush();
}

void Net::GetInfo()
{
    QString str1 = "getinfo";
    _tcp->write(str1.toUtf8());
}
