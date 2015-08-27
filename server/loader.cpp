#include "loader.h"
#include <QDebug>

Loader::Loader()
{
}

Loader::~Loader()
{
    QVectorIterator <InfiniteWorld* > i(_map);
    while(i.hasNext())
    {
        delete i.next();
    }
}

void Loader::Generate768d(InfiniteWorld *map)
{
    if (map!=NULL)
    {
        int i=0, g=0;
        QChar symbol = ' ';
        while (i<_sector_len)
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
            map->_map.push_back(symbol);
            //qDebug() << map->_map[i];
            i++;
        }
    } else
    {
        qDebug() << "Error: map=NULL.";
    }
}

void Loader::GenerateLeft(InfiniteWorld *map)
{
    if (map->_left != NULL)
    {
        qDebug() << "Error: map_left already exist.";
    }
    if (map!=NULL&&map->_left == NULL)
    {
        InfiniteWorld *map_left = new InfiniteWorld();
        Generate768d(map_left);
        map->_left = map_left;
        _map.push_back(map_left);
    }
}

void Loader::GenerateRight(InfiniteWorld *map)
{
    if (map->_right != NULL)
    {
        qDebug() << "Error: map_right already exist.";
    }
    if (map!=NULL&&map->_right == NULL)
    {
        InfiniteWorld *map_right = new InfiniteWorld();
        Generate768d(map_right);
        map->_right = map_right;
        _map.push_back(map_right);
    }
}

void Loader::GenerateTop(InfiniteWorld *map)
{
    if (map->_top != NULL)
    {
        qDebug() << "Error: map_top already exist.";
    }
    if (map!=NULL&&map->_top == NULL)
    {
        InfiniteWorld *map_top = new InfiniteWorld();
        Generate768d(map_top);
        map->_top = map_top;
        _map.push_back(map_top);
    }
}

void Loader::GenerateBottom(InfiniteWorld *map)
{
    if (map->_bottom != NULL)
    {
        qDebug() << "Error: map_bottom already exist.";
    }
    if (map!=NULL&&map->_bottom == NULL)
    {
        InfiniteWorld *map_bottom = new InfiniteWorld();
        Generate768d(map_bottom);
        map->_bottom = map_bottom;
        _map.push_back(map_bottom);
    }
}

void Loader::GenerateInFront(InfiniteWorld *map)
{
    if (map->_in_front != NULL)
    {
        qDebug() << "Error: _in_front already exist.";
    }
    if (map!=NULL&&map->_in_front == NULL)
    {
        InfiniteWorld *map_in_front = new InfiniteWorld();
        Generate768d(map_in_front);
        map->_in_front = map_in_front;
        _map.push_back(map_in_front);
    }
}

void Loader::GenerateBehind(InfiniteWorld *map)
{
    if (map->_behind != NULL)
    {
        qDebug() << "Error: _behind already exist.";
    }
    if (map!=NULL&&map->_behind == NULL)
    {
        InfiniteWorld *map_behind = new InfiniteWorld();
        Generate768d(map_behind);
        map->_behind = map_behind;
        _map.push_back(map_behind);
    }
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
            GenerateMap();
            GenerateTables();
        }
    } else
    {
        qDebug() << "Connect to database error.";
        exit(-1);
    }
}

void Loader::GenerateMap()
{
    QSqlQuery q;
    q.prepare("SELECT sector_length FROM world");
    q.exec();
    _sector_len=0;
    if (q.next())
    {
        _sector_len = q.value(0).toInt();
    }
    if (_sector_len == 0)
    {
        _sector_len = 768;
        QSqlQuery q1;
        q1.prepare("INSERT INTO world (sector_length, penta, yota) VALUES(:sector,0,0)");
        q1.bindValue(":sector", _sector_len);
        q1.exec();
    }
    InfiniteWorld *map = new InfiniteWorld();
    GenerateInFront(map);
    SaveMapToDatabase(map->_in_front);
    delete map;
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

void Loader::SaveMapToDatabase(InfiniteWorld *map)
{
    QString str;
    for (int i=0; i<map->_map.length(); i++)
    {
        str += map->_map[i];
    }
    QSqlQuery q;
    q.prepare("INSERT INTO map (inleft, inright, intop, inbottom, infront, inbehind, data) VALUES(0,0,0,0,0,0,:data)");
    q.bindValue(":data", str);
    q.exec();
}

void Loader::LoadToBuffer(int id, int radius)
{
}

void Loader::ListenPlayers()
{
    //listen port 2244
    //if connect
    //if level = 0
    //addplayertomap
    //else getcoords from database
    //bufferize or generate player map
}

int Loader::BufferizeLeft(int id, int radius)
{
    if (radius > 0)
    {
        radius--;
        int map_id_left = 0;
        //selectinleft
        QSqlQuery q;
        q.prepare("SELECT inleft,data FROM map WHERE map_id=:id");
        q.bindValue(":id", id);
        q.exec();
        if (q.next())
        {
            //LoadData to infinite_world
            //push_back infinite_world to queue
            if (q.value(0).toInt() == 0)
            {
                return 0;
            } else
            {
                BufferizeLeft(map_id_left, radius);
            }
        } else
        {
            qDebug() << "Error: bufferize left error.";
            exit(-1);
        }
    } else
    {

        return 0;
    }
    return 0;
}
