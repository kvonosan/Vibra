#include "loader.h"
#include <QDebug>

Loader::Loader()
{
}

Loader::~Loader()
{}

void Loader::Generate(InfiniteWorld *map)
{
    if (map!=NULL)
    {
        //map->_map = Random();
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
        Generate(map_left);
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
        Generate(map_right);
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
        Generate(map_top);
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
        Generate(map_bottom);
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
        Generate(map_in_front);
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
        Generate(map_behind);
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
        //database connect
        //if not found
        //!generate map
        //destroy
        //else
        //get params
        QSqlQuery query("SELECT Count(*) FROM map");
        if (query.exec())
        {
            int count = query.record().value(0).toInt();
            qDebug() << "Count = " << count;
        }
    } else
    {
        qDebug() << "Connect to database error.";
        //exit(-1);
    }
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

void Loader::BufferizeLeft()
{
    //load from database
}
