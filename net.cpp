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
    _tcp->connectToHost("91.215.138.69", _port);
    _tcp->waitForConnected(2000);
    _tcp->connectToHost("127.0.0.1", _port);
    _connected = true;
    _authorized = false;
}

void Net::Connected()
{
    QString str = "token " + _access_token;
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
    QByteArray array = _tcp->readAll();
    QString str = QString::fromUtf8(array.toStdString().c_str());
    if (str.startsWith("id"))
    {
        QStringList list = str.split(" ");
        bool ok;
        _player_id = list[1].toInt(&ok, 16);
        if (!ok)
        {
            qDebug() << "Net read error.";
            exit(-1);
        }
        if (_player_id != 0)
        {
            _authorized = true;
            GetVKName();
            _base->_hero_obj->_name = _firstName + " "+ _lastName;
            QString str1 = "getinfo";
            _tcp->write(str1.toUtf8());
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
        for(int j=0; j < _base->_fly->_grid->GetSizeY(); j++)
            for(int i=0; i < _base->_fly->_grid->GetSizeX(); i++)
            {
                Symbol *sym = _base->_fly->_grid->GetSymbolAt(i, j);
                sym->_symbol = str[g];
                if (str[g] == 'A' || str[g] == 'B' || str[g] == 'C'
                        || str[g] == 'D' || str[g] == 'E')
                {
                    sym->_attacked = true;
                    sym->_hp = 1000;
                    sym->_armor = 1000;
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
        _firepos = str.toInt();
    } else if (str.startsWith("killed"))
    {
        _killed = true;
    }
}

void Net::BufferizeMap()
{
    QString str = QString("getmap");
    _tcp->write(str.toUtf8());
}

void Net::Left()
{
    QString str = "left";
    _tcp->write(str.toUtf8());
    _tcp->flush();
}

void Net::Right()
{
    QString str = "right";
    _tcp->write(str.toUtf8());
    _tcp->flush();
}

void Net::Top()
{
    QString str = "top";
    _tcp->write(str.toUtf8());
    _tcp->flush();
}

void Net::Bottom()
{
    QString str = "bottom";
    _tcp->write(str.toUtf8());
    _tcp->flush();
}

void Net::GetMyPos()
{
    QString str = "getmypos";
    _tcp->write(str.toUtf8());
    _tcp->flush();
    _tcp->waitForReadyRead(3000);
}

void Net::Fire(int pos)
{
    _firepos = -1;
    QString str = "fire " + QString::number(pos);
    _tcp->write(str.toUtf8());
    _tcp->flush();
}
