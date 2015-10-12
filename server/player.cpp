#include <QtSql>
#include "player.h"

Player::Player(Loader *loader)
{
    if (loader == NULL)
    {
        qDebug() << "Ошибка: loader == NULL.";
        exit(-1);
    }
    _loader = loader;
}

Player::~Player()
{
}

void Player::News()
{
    if (!_loader->_db.isOpen())
    {
        if (!_loader->_db.open())
        {
            qDebug() << "Ошибка соединения к базе данных:" << _loader->_db.lastError();
            exit(-1);
        }
    }
    QSqlQuery q;
    q.prepare("SELECT count(news_id) FROM news");
    q.exec();
    int count = 0;
    if (q.next())
    {
        count = q.value(0).toInt();
    }
    qDebug() << q.lastError();
    if (count == 0)
    {
        QSqlQuery q1;
        q1.prepare("INSERT INTO news (name, text) VALUES(:name, :text)");
        q1.bindValue(":name", "Вселенная");
        q1.bindValue(":text", "После того как галогены узнали все технологии человечества "
                              "они уничтожили планету земля вместе со всеми людьми. "
                              "Вселенная людей исчезла с карт и радаров. Началась научная "
                              "гонка. Поговаривали что галогены увеличили мощность своих "
                              "кораблей за счет наращивания пропускной способности. Также"
                              " тот кто раздобудет все секреты галогенов сможет "
                              "смоделировать и возродить человеческую расу. Корабли "
                              "плавают по вселенной работая на органической плазме, "
                              "плазма содержит в себе следующую ветвь интернета - "
                              "йотанет, с большими скоростями, и большим радиусом "
                              "действия. Плазма добывается из субституции. "
                              "Субституция это необработанные космические объекты. "
                              "Чтобы возродить человеческую расу, кораблю необходим"
                              " плазмоид. На вашем корабле нет плазмоида!"
                              " Вперед на поиски!"
                              " Управление кораблем на клавиши w,a,s,d. "
                              "Классы кораблей: A,B,C,D,E. "
                              "r - органическая плазма, "
                              "b - база, "
                              "p - планета, "
                              "s - звезда."
                              " Уничтожить вражеский корабль вы можете кликнув на нем!");
        q1.exec();
        qDebug() << q1.lastError();
    } else
    {
        qDebug() << "Новость Вселенная йотанет добавлена.";
    }
}

void Player::Search()
{
    if (!_loader->_db.isOpen())
    {
        if (!_loader->_db.open())
        {
            qDebug() << "Ошибка соединения к базе данных:" << _loader->_db.lastError();
            exit(-1);
        }
    }
    QSqlQuery q;
    q.prepare("SELECT count(player_id),player_id,pos FROM player WHERE vk_id=:id");
    q.bindValue(":id", _player_id_vk);
    q.exec();
    int count = 0;
    if (q.next())
    {
        count = q.value(0).toInt();
        _player_id = q.value(1).toInt();
        _pos = q.value(2).toInt();
    }
    qDebug() << q.lastError();
    if (count == 0)
    {
        QSqlQuery q1;
        q1.prepare("INSERT INTO player (vk_id, gold, credits, race, ship, spec, rank, escadra, "
                   "rating, screen, level, map, pos) VALUES(:id, 0,0,0,0,0,0,0,0,0,0,0,0)");
        q1.bindValue(":id", _player_id_vk);
        q1.exec();
        q.bindValue(":id", _player_id_vk);
        q.exec();
        if (q.next())
        {
            _player_id = q.value(1).toInt();
            qDebug() << "Добавлен новый игрок с id = " + QString::number(_player_id);
        }
    } else
    {
        qDebug() << "player_id = " + QString::number(_player_id);
    }
}

void Player::newPlayer()
{
    if (!_loader->_db.isOpen())
    {
        if (!_loader->_db.open())
        {
            qDebug() << "Ошибка соединения к базе данных:" << _loader->_db.lastError();
            exit(-1);
        }
    }
    QSqlQuery q;
    q.prepare("SELECT level FROM player WHERE player_id=:id");
    q.bindValue(":id", _player_id);
    q.exec();
    int level = 0;
    if (q.next())
    {
        level = q.value(0).toInt();
    }
    if (level == 0)
    {
        QSqlQuery q1;
        q1.prepare("INSERT INTO ship(player_id, engine, fuel_tank, ship_body, generator,"
                   " cartograph, yotanet, radar, scaner, chinilka, grab, "
                   "weapons, improvement, accelerator) VALUES(:id, 1, 1, 1, 0, 0, 0"
                   ", 0, 0, 0, 0, 1, 0, 0)");
        q1.bindValue(":id", _player_id);
        q1.exec();
        QSqlQuery q2;
        q2.prepare("INSERT INTO rating(player_id, exp, kills, death, mission, credits,"
                   "fights) VALUES(:id,0,0,0,0,0,0)");
        q2.bindValue(":id", _player_id);
        q2.exec();
        QSqlQuery q3;
        q3.prepare("SELECT ship_id FROM ship WHERE player_id=:id");
        q3.bindValue(":id", _player_id);
        q3.exec();
        int ship_id = 0;
        if (q3.next())
        {
            ship_id = q3.value(0).toInt();
        }
        if (ship_id == 0)
        {
            qDebug() << "Ошибка ship_id = 0.";
            return;
        }
        QSqlQuery q4;
        q4.prepare("SELECT rating_id FROM rating WHERE player_id=:id");
        q4.bindValue(":id", _player_id);
        q4.exec();
        int rating1 = 0;
        if (q4.next())
        {
            rating1 = q4.value(0).toInt();
        }
        if (rating1 == 0)
        {
            qDebug() << "Ошибка rating1 = 0.";
            return;
        }
        QSqlQuery q5;
        q5.prepare("UPDATE player SET race=1, ship=:ship, spec=1, rating=:rating1,"
                   " level=1 WHERE player_id = :id");
        q5.bindValue(":ship", ship_id);
        q5.bindValue(":rating1", rating1);
        q5.bindValue(":id", _player_id);
        q5.exec();
        QSqlQuery q7;
        q7.prepare("SELECT life FROM ship_body WHERE body_id=1");
        q7.exec();
        int life = 0;
        if (q7.next())
        {
            life = q7.value(0).toInt();
        }
        if (life == 0)
        {
            qDebug() << "Ошибка life = 0.";
            exit(-1);
        }
        QSqlQuery q8;
        q8.prepare("SELECT penta FROM fuel_tank WHERE fuel_tank_id=1");
        q8.exec();
        int fuel = 0;
        if (q8.next())
        {
            fuel = q8.value(0).toInt();
        }
        if (fuel == 0)
        {
            qDebug() << "Ошибка fuel = 0.";
            exit(-1);
        }
        life = (life - 100) + rand()%100;
        QSqlQuery q6;
        q6.prepare("INSERT INTO ship_point(ship_id, life, energy, armor, fuel, life_gen, "
                   "energy_gen, armor_gen, net_speed, cartograph_link, grab_points, "
                   "radar_ships, scaner_predm, fire, fire_speed, fire_link, map, pos) VALUES("
                   ":ship_id, :life, 0, 0, 0, 0, 0,0,0,0,0,0,0,0,0,0,0,0)");
        q6.bindValue(":ship_id", ship_id);
        q6.bindValue(":life", life);
        q6.exec();
        QSqlQuery q9;
        q9.prepare("UPDATE ship_point SET fire=10, fire_speed=1, fire_link=768 WHERE ship_id=:ship_id");
        q9.bindValue(":ship_id", ship_id);
        q9.exec();
        QJsonObject obj;
        obj["kill1"] = "A";
        obj["kill2"] = "B";
        obj["kill3"] = "C";
        obj["priz"] = "cartograph";
        QJsonDocument doc(obj);
        QString json = QString::fromUtf8(doc.toJson(QJsonDocument::Compact).toStdString().c_str());
        QSqlQuery q10;
        q10.prepare("INSERT INTO mission(player_id, params_json, end) VALUES(:id, :json, 0)");
        q10.bindValue(":id", _player_id);
        q10.bindValue(":json", json);
        q10.exec();
        QJsonObject obj1;
        obj1["kill1"] = "D";
        obj1["kill2"] = "E";
        obj1["priz"] = "droid";
        QJsonDocument doc1(obj1);
        QString json1 = QString::fromUtf8(doc1.toJson(QJsonDocument::Compact).toStdString().c_str());
        q10.bindValue(":json", json1);
        q10.exec();
    } else
    {
        qDebug() << "player_id = " + QString::number(_player_id) << " такой игрок есть в базе.";
    }
}

void Player::AddToMap()
{
    if (!_loader->_db.isOpen())
    {
        if (!_loader->_db.open())
        {
            qDebug() << "Ошибка соединения в базе данных:" << _loader->_db.lastError();
            exit(-1);
        }
    }
    QSqlQuery q4;
    q4.prepare("SELECT map, ship FROM player WHERE player_id=:id");
    q4.bindValue(":id", _player_id);
    q4.exec();
    int map = 0;
    if (q4.next())
    {
        map = q4.value(0).toInt();
    }
    if (map == 0)
    {
        QSqlQuery q1;
        q1.prepare("SELECT ship_body FROM ship WHERE player_id=:id");
        q1.bindValue(":id", _player_id);
        q1.exec();
        int body = 0;
        if (q1.next())
        {
            body = q1.value(0).toInt();
        }
        QSqlQuery q2;
        q2.prepare("SELECT class FROM ship_body WHERE body_id=:body");
        q2.bindValue(":body", body);
        q2.exec();
        QString class1;
        if (q2.next())
        {
            class1 = q2.value(0).toString();
        }
        QSqlQuery q;
        q.prepare("SELECT map_id FROM map ORDER BY map_id DESC LIMIT 1");
        q.exec();
        int last = 0;
        if (q.next())
        {
            last = q.value(0).toInt();
        }
        QSqlQuery q3;
        q3.prepare("SELECT data FROM map WHERE map_id=:id");
        q3.bindValue(":id", last);
        q3.exec();
        QString data;
        if (q3.next())
        {
            data = q3.value(0).toString();
        }
        int i=0;
        for (i=0; i<data.size(); i++)
        {
            if (data[i] == ' ')
            {
                break;
            }
        }
        data[i] = class1[0];
        _pos = i;
        _map = last;
        QSqlQuery q6;
        q6.prepare("UPDATE map SET data=:data WHERE map_id=:id");
        q6.bindValue(":id", last);
        q6.bindValue(":data", data);
        q6.exec();
        QSqlQuery q5;
        q5.prepare("UPDATE player SET map=:map, pos=:pos WHERE player_id=:id");
        q5.bindValue(":map", last);
        q5.bindValue(":pos", i);
        q5.bindValue(":id", _player_id);
        q5.exec();
    } else
    {
        _map = map;
        QSqlQuery q1;
        q1.prepare("SELECT pos FROM player WHERE player_id=:id");
        q1.bindValue(":id", _player_id);
        q1.exec();
        if (q1.next())
        {
            _pos = q1.value(0).toInt();
        }
        QSqlQuery q4;
        q4.prepare("SELECT ship_body FROM ship WHERE player_id=:id");
        q4.bindValue(":id", _player_id);
        q4.exec();
        int body = 0;
        if (q4.next())
        {
            body = q4.value(0).toInt();
        }
        QSqlQuery q2;
        q2.prepare("SELECT class FROM ship_body WHERE body_id=:body");
        q2.bindValue(":body", body);
        q2.exec();
        QString class1;
        if (q2.next())
        {
            class1 = q2.value(0).toString();
        }
        QSqlQuery q3;
        q3.prepare("SELECT data FROM map WHERE map_id=:id");
        q3.bindValue(":id", _map);
        q3.exec();
        QString data;
        if (q3.next())
        {
            data = q3.value(0).toString();
        }
        data[_pos] = class1[0];
        QSqlQuery q6;
        q6.prepare("UPDATE map SET data=:data WHERE map_id=:id");
        q6.bindValue(":id", _map);
        q6.bindValue(":data", data);
        q6.exec();
    }
}
