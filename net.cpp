#include "net.h"
#include "hero.h"
#include "frame.h"

Net::Net()
{
    _port = 33333;
    _connected = false;
    _tcp = new QTcpSocket();
}

Net::~Net()
{
    delete _tcp;
}

bool Net::VKConnected()
{
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
        //qDebug() << _vk_user_id;
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
                _base->_fly->_grid->GetSymbolAt(i, j)->symbol = str[g];
                g++;
            }
    }
}

void Net::BufferizeMap()
{
    QJsonObject obj;
    obj["screen_width"] = _base->_frame->GetWidth();
    obj["screen_height"] = _base->_frame->GetHeight();
    obj["len"] = 2;
    QJsonDocument doc(obj);
    QString str = QString("getmap") + " " + QString::fromUtf8(doc.toJson(QJsonDocument::Compact).toStdString().c_str());
    _tcp->write(str.toUtf8());
}
