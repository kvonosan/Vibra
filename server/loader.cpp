#include "loader.h"
#include <QDebug>

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
        qDebug() << "Connect to database error.";
        exit(-1);
    }
}

void Loader::GenerateTables()
{
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
}

void Loader::GenerateStartMap()
{
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
    }
    QString newmap = Generate768d();
    QSqlQuery q2;
    q2.prepare("INSERT INTO map (inleft, inright, intop, inbottom, infront, inbehind, data) VALUES(0,0,0,0,0,0,:data)");
    q2.bindValue(":data", newmap);
    q2.exec();
}

QString Loader::Generate768d()
{
        int i=0, g=0;
        QString str;
        QChar symbol = ' ';
        while (i<768)
        {
            g = rand()%10;
            //qDebug() << g <<"\n";
            switch(g)
            {
            case 0:
            {
                symbol = 'P';//Planet
            }
                break ;
            case 1:
            case 2:
            {
                symbol = ' ';//No
            }
                break;
            case 3:
            {
                symbol = 'B';//Base
            }
                break;
            case 4:
            case 5:
            {
                symbol = 'S';//Star
            }
                break;
            case 6:
            case 7:
            {
                symbol = 'A';//Asteroid
            }
                break;
            case 8:
            case 9:
            {
                symbol = 'R';//Resource
            }
                break;
            }
            //str += QString(symbol);
            str += ' ';
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
    return data;
}
