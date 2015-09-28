#include "loader.h"
#include <QDebug>
#include <QSettings>

Loader::Loader()
{
}

Loader::~Loader()
{
}

void Loader::DatabaseConnect()
{
    _db = QSqlDatabase::addDatabase("QMYSQL");
    _db.setHostName("127.0.0.1");
    _db.setDatabaseName("yotanet768d");
    _db.setUserName("root");
    _db.setPassword("1234");
    bool ok = _db.open();
    if (ok)
    {
        qDebug() << "Соединен с" << _db.databaseName() << ".";
        QSqlQuery q;
        q.prepare("SELECT Count(*) FROM map");
        q.exec();
        int count = 0;
        if (q.next())
        {
            count = q.value(0).toInt();
        }
        if (count == 0)
        {
            GenerateStartMap();
            GenerateTables();
        }
    } else
    {
        qDebug() << "Ошибка соединения с базой данных " << _db.databaseName() << ".";
        exit(-1);
    }
}

void Loader::GenerateTables()
{
    if (!_db.isOpen())
    {
        if (!_db.open())
        {
            qDebug() << "Error when connecting to db:" << _db.lastError();
            exit(-1);
        }
    }
    QSqlQuery q;
    q.prepare("SELECT Count(*) FROM race");
    q.exec();
    int count = 0;
    if (q.next())
    {
        count = q.value(0).toInt();
    }
    if (count == 0)
    {
        qDebug() << "Пожалуйста, заполните таблицы данными, они пусты.";
        exit(1);
    }
    qDebug() << "Начальные таблицы заполнены.";
}

void Loader::GenerateStartMap()
{
    if (!_db.isOpen())
    {
        if (!_db.open())
        {
            qDebug() << "Error when connecting to db:" << _db.lastError();
            exit(-1);
        }
    }
    QSqlQuery q;
    q.prepare("SELECT sector_length FROM world");
    q.exec();
    int sector_len=0;
    if (q.next())
    {
        sector_len = q.value(0).toInt();
    }
    if (sector_len == 0)
    {
        sector_len = 768;
        QSqlQuery q1;
        q1.prepare("INSERT INTO world (sector_length, penta, yota) VALUES(:sector,12,100)");
        q1.bindValue(":sector", sector_len);
        q1.exec();
        qDebug() << "Создан сектор " << QString::number(sector_len) << ".";
    }
    QString newmap = Generate768d();
    QSqlQuery q2;
    q2.prepare("INSERT INTO map (inleft, inright, intop, inbottom, infront, inbehind, data) VALUES(0,0,0,0,0,0,:data)");
    q2.bindValue(":data", newmap);
    q2.exec();
    QSqlQuery q3;
    q3.prepare("SELECT map_id FROM map ORDER BY map_id DESC LIMIT 1");
    q3.exec();
    int last = 0;
    if (q3.next())
    {
        last = q3.value(0).toInt();
    }
    qDebug() << "Создана новая карта с id = " << last << ".";
}

QString Loader::Generate768d()
{
    if (!_db.isOpen())
    {
        if (!_db.open())
        {
            qDebug() << "Error when connecting to db:" << _db.lastError();
            exit(-1);
        }
    }
    int i=0, g=0;
    QString str;
    QChar symbol = ' ';
    while (i<768)
    {
        g = rand()%100;
        //qDebug() << g <<"\n";
        if (g >= 0 && g <=80)
        {
            symbol = ' ';//No
        } else if (g == 81 || g == 82)
        {
            symbol = 'A';
        } else if (g == 83 ||g == 84)
        {
            symbol = 'B';
        } else if (g == 85 || g == 86)
        {
            symbol = 'C';
        } else if (g == 87 || g == 88)
        {
            symbol = 'D';
        } else if (g == 89 || g==90)
        {
            symbol = 'E';
        } else if (g == 91 || g == 92)
        {
            symbol = 'p';//Planet
        } else if (g == 93 || g == 94)
        {
            symbol = 'b';//Base
        } else if (g == 95 || g == 96)
        {
            symbol = 's';//Star
        } else if (g == 97 || g == 98)
        {
            //symbol = 'a';//Asteroid
        } else if (g == 99 || g == 100)
        {
            symbol = 'r';//Resource
        }
        str += QString(symbol);
        i++;
    }
    return str + '.';
}

QString Loader::Bufferize(Player *player)
{
    if (player == NULL)
    {
        qDebug() << "Error player == NULL.";
        exit(-1);
    }
    if (!_db.isOpen())
    {
        if (!_db.open())
        {
            qDebug() << "Error when connecting to db:" << _db.lastError();
            exit(-1);
        }
    }
    QSqlQuery q1;
    q1.prepare("SELECT map FROM player WHERE player_id=:p");
    q1.bindValue(":p", player->_player_id);
    q1.exec();
    int map_id = 0;
    if (q1.next())
    {
        map_id = q1.value(0).toInt();
    }
    if (map_id == 0)
    {
        qDebug() << "Error map_id = 0.";
        exit(-1);
    }
    QSqlQuery q2;
    q2.prepare("SELECT data FROM map WHERE map_id=:m");
    q2.bindValue(":m", map_id);
    q2.exec();
    QString data;
    if (q2.next())
    {
        data = q2.value(0).toString();
    }
    qDebug() << "Игроку id = " << player->_player_id << "Загружена карта с id = " << map_id << ".";
    return data;
}

void Loader::GenerateLeftMap(Player *player)
{
    if (player == NULL)
    {
        qDebug() << "Error player == NULL.";
        exit(-1);
    }
    if (!_db.isOpen())
    {
        if (!_db.open())
        {
            qDebug() << "Error when connecting to db:" << _db.lastError();
            exit(-1);
        }
    }
    QString map = Generate768d();
    QSqlQuery q1;
    q1.prepare("INSERT INTO map (inleft, inright, intop, inbottom, infront, inbehind, data) VALUES(0,:inright,0,0,0,0,:data)");
    q1.bindValue(":data", map);
    q1.bindValue(":inright", player->_map);
    q1.exec();
    QSqlQuery q2;
    q2.prepare("SELECT map_id FROM map ORDER BY map_id DESC LIMIT 1");
    q2.exec();
    int last = 0;
    if (q2.next())
    {
        last = q2.value(0).toInt();
    }
    QSqlQuery q4;
    q4.prepare("UPDATE map SET inleft=:inleft WHERE map_id=:map_id");
    q4.bindValue(":inleft", last);
    q4.bindValue(":map_id", player->_map);
    q4.exec();
    QSqlQuery q6;
    q6.prepare("SELECT data FROM map WHERE map_id=:map");
    q6.bindValue(":map", player->_map);
    q6.exec();
    QString data;
    QChar symbol;
    if (q6.next())
    {
        data = q6.value(0).toString();
    }
    symbol = data[player->_pos];
    data[player->_pos] = ' ';
    //
    QSqlQuery q5;
    q5.prepare("SELECT data FROM map WHERE map_id=:map");
    q5.bindValue(":map", last);
    q5.exec();
    QString data1;
    if (q5.next())
    {
        data1 = q5.value(0).toString();
    }
    int pos = player->_pos-1;
    if (pos == -1)
    {
        player->_pos = 31;
        pos = 31;
    } else
    {
        player->_pos = player->_pos+31;
        pos = player->_pos;
    }
    if (data1[pos] != ' ')
    {
        data1[pos] = ' ';
    }
    QSqlQuery q7;
    q7.prepare("UPDATE map SET data=:data WHERE map_id=:map");
    q7.bindValue(":map", player->_map);
    q7.bindValue(":data", data);
    q7.exec();
    //
    data1[pos] = symbol;
    player->_map = last;
    QSqlQuery q8;
    q8.prepare("UPDATE map SET data=:data WHERE map_id=:map");
    q8.bindValue(":map", player->_map);
    q8.bindValue(":data", data1);
    q8.exec();
    QSqlQuery q3;
    q3.prepare("UPDATE player SET map=:map, pos=:pos WHERE player_id=:id");
    q3.bindValue(":map", last);
    q3.bindValue(":id", player->_player_id);
    q3.bindValue(":pos", player->_pos);
    q3.exec();
}

void Loader::GenerateRightMap(Player *player)
{
    if (player == NULL)
    {
        qDebug() << "Error player == NULL.";
        exit(-1);
    }
    if (!_db.isOpen())
    {
        if (!_db.open())
        {
            qDebug() << "Error when connecting to db:" << _db.lastError();
            exit(-1);
        }
    }
    QString map = Generate768d();
    QSqlQuery q1;
    q1.prepare("INSERT INTO map (inleft, inright, intop, inbottom, infront, inbehind, data) VALUES(:inleft,0,0,0,0,0,:data)");
    q1.bindValue(":data", map);
    q1.bindValue(":inleft", player->_map);
    q1.exec();
    QSqlQuery q2;
    q2.prepare("SELECT map_id FROM map ORDER BY map_id DESC LIMIT 1");
    q2.exec();
    int last = 0;
    if (q2.next())
    {
        last = q2.value(0).toInt();
    }
    QSqlQuery q4;
    q4.prepare("UPDATE map SET inright=:inright WHERE map_id=:map_id");
    q4.bindValue(":inright", last);
    q4.bindValue(":map_id", player->_map);
    q4.exec();
    QSqlQuery q6;
    q6.prepare("SELECT data FROM map WHERE map_id=:map");
    q6.bindValue(":map", player->_map);
    q6.exec();
    QString data;
    QChar symbol;
    if (q6.next())
    {
        data = q6.value(0).toString();
    }
    symbol = data[player->_pos];
    data[player->_pos] = ' ';
    //
    QSqlQuery q5;
    q5.prepare("SELECT data FROM map WHERE map_id=:map");
    q5.bindValue(":map", last);
    q5.exec();
    QString data1;
    if (q5.next())
    {
        data1 = q5.value(0).toString();
    }
    int pos = player->_pos%32;
    if (pos == 31)
    {
        player->_pos = player->_pos-31;
        pos = player->_pos;
    }
    if (data1[pos] != ' ')
    {
        data1[pos] = ' ';
    }
    QSqlQuery q7;
    q7.prepare("UPDATE map SET data=:data WHERE map_id=:map");
    q7.bindValue(":map", player->_map);
    q7.bindValue(":data", data);
    q7.exec();
    //
    data1[pos] = symbol;
    player->_map = last;
    QSqlQuery q8;
    q8.prepare("UPDATE map SET data=:data WHERE map_id=:map");
    q8.bindValue(":map", player->_map);
    q8.bindValue(":data", data1);
    q8.exec();
    QSqlQuery q3;
    q3.prepare("UPDATE player SET map=:map, pos=:pos WHERE player_id=:id");
    q3.bindValue(":map", last);
    q3.bindValue(":id", player->_player_id);
    q3.bindValue(":pos", player->_pos);
    q3.exec();
}

void Loader::GenerateTopMap(Player *player)
{
    if (player == NULL)
    {
        qDebug() << "Error player == NULL.";
        exit(-1);
    }
    if (!_db.isOpen())
    {
        if (!_db.open())
        {
            qDebug() << "Error when connecting to db:" << _db.lastError();
            exit(-1);
        }
    }
    QString map = Generate768d();
    QSqlQuery q1;
    q1.prepare("INSERT INTO map (inleft, inright, intop, inbottom, infront, inbehind, data) VALUES(0,0,0,:inbottom,0,0,:data)");
    q1.bindValue(":data", map);
    q1.bindValue(":inbottom", player->_map);
    q1.exec();
    QSqlQuery q2;
    q2.prepare("SELECT map_id FROM map ORDER BY map_id DESC LIMIT 1");
    q2.exec();
    int last = 0;
    if (q2.next())
    {
        last = q2.value(0).toInt();
    }
    QSqlQuery q4;
    q4.prepare("UPDATE map SET intop=:intop WHERE map_id=:map_id");
    q4.bindValue(":intop", last);
    q4.bindValue(":map_id", player->_map);
    q4.exec();
    QSqlQuery q6;
    q6.prepare("SELECT data FROM map WHERE map_id=:map");
    q6.bindValue(":map", player->_map);
    q6.exec();
    QString data;
    QChar symbol;
    if (q6.next())
    {
        data = q6.value(0).toString();
    }
    symbol = data[player->_pos];
    data[player->_pos] = ' ';
    //
    QSqlQuery q5;
    q5.prepare("SELECT data FROM map WHERE map_id=:map");
    q5.bindValue(":map", last);
    q5.exec();
    QString data1;
    if (q5.next())
    {
        data1 = q5.value(0).toString();
    }
    int pos = player->_pos-32;
    if (pos < 0)
    {
        player->_pos = 768 - 32 + player->_pos;
        pos = player->_pos;
    }
    if (data1[pos] != ' ')
    {
        data1[pos] = ' ';
    }
    QSqlQuery q7;
    q7.prepare("UPDATE map SET data=:data WHERE map_id=:map");
    q7.bindValue(":map", player->_map);
    q7.bindValue(":data", data);
    q7.exec();
    //
    data1[pos] = symbol;
    player->_map = last;
    QSqlQuery q8;
    q8.prepare("UPDATE map SET data=:data WHERE map_id=:map");
    q8.bindValue(":map", player->_map);
    q8.bindValue(":data", data1);
    q8.exec();
    QSqlQuery q3;
    q3.prepare("UPDATE player SET map=:map, pos=:pos WHERE player_id=:id");
    q3.bindValue(":map", last);
    q3.bindValue(":id", player->_player_id);
    q3.bindValue(":pos", player->_pos);
    q3.exec();
}

void Loader::GenerateBottomMap(Player *player)
{
    if (player == NULL)
    {
        qDebug() << "Error player == NULL.";
        exit(-1);
    }
    if (!_db.isOpen())
    {
        if (!_db.open())
        {
            qDebug() << "Error when connecting to db:" << _db.lastError();
            exit(-1);
        }
    }
    QString map = Generate768d();
    QSqlQuery q1;
    q1.prepare("INSERT INTO map (inleft, inright, intop, inbottom, infront, inbehind, data) VALUES(0,0,:intop,0,0,0,:data)");
    q1.bindValue(":data", map);
    q1.bindValue(":intop", player->_map);
    q1.exec();
    QSqlQuery q2;
    q2.prepare("SELECT map_id FROM map ORDER BY map_id DESC LIMIT 1");
    q2.exec();
    int last = 0;
    if (q2.next())
    {
        last = q2.value(0).toInt();
    }
    QSqlQuery q4;
    q4.prepare("UPDATE map SET inbottom=:inbottom WHERE map_id=:map_id");
    q4.bindValue(":inbottom", last);
    q4.bindValue(":map_id", player->_map);
    q4.exec();
    QSqlQuery q6;
    q6.prepare("SELECT data FROM map WHERE map_id=:map");
    q6.bindValue(":map", player->_map);
    q6.exec();
    QString data;
    QChar symbol;
    if (q6.next())
    {
        data = q6.value(0).toString();
    }
    symbol = data[player->_pos];
    data[player->_pos] = ' ';
    //
    QSqlQuery q5;
    q5.prepare("SELECT data FROM map WHERE map_id=:map");
    q5.bindValue(":map", last);
    q5.exec();
    QString data1;
    if (q5.next())
    {
        data1 = q5.value(0).toString();
    }
    int pos = player->_pos+32;
    if (pos > 768)
    {
        player->_pos = player->_pos+32 - 768;
        pos = player->_pos;
    }
    if (data1[pos] != ' ')
    {
        data1[pos] = ' ';
    }
    QSqlQuery q7;
    q7.prepare("UPDATE map SET data=:data WHERE map_id=:map");
    q7.bindValue(":map", player->_map);
    q7.bindValue(":data", data);
    q7.exec();
    //
    data1[pos] = symbol;
    player->_map = last;
    QSqlQuery q8;
    q8.prepare("UPDATE map SET data=:data WHERE map_id=:map");
    q8.bindValue(":map", player->_map);
    q8.bindValue(":data", data1);
    q8.exec();
    QSqlQuery q3;
    q3.prepare("UPDATE player SET map=:map, pos=:pos WHERE player_id=:id");
    q3.bindValue(":map", last);
    q3.bindValue(":id", player->_player_id);
    q3.bindValue(":pos", player->_pos);
    q3.exec();
}
