#include "hero.h"

Hero::Hero(QWindow *parent, Base *base)
{
    if (parent == NULL)
    {
        qDebug() << "Error. parent == NULL.";
        exit(-1);
    }
    _parent = parent;
    if (base == NULL)
    {
        qDebug() << "Error. base == NULL.";
        exit(-1);
    }
    _base = base;
    _ramka = QRect(10, 10, _parent->width()-20, _parent->height()-20-20-50);
    _back = QRect(_parent->geometry().width()/3*2, _parent->geometry().height()-20-50, _parent->geometry().width()/3-20, 60);
    _string = "";
    _name = "Лео Месси";
    _experience = "0";
    _gold = "0";
    _credits = "0";
    _race = "Киберг";
    _ship = "Класс А";
    _specialty = "Гуманоид";
    _rank = "новобранец";
    _squadron = "нет";
    _rating = "0";
    _level = "0";
}

Hero::~Hero()
{}

void Hero::Paint(QPainter *painter)
{
    if (painter == NULL)
    {
        qDebug() << "Error. Painter == NULL.";
        exit(-1);
    }
    SetParams();
    QPainterPath path;
    path.addRoundedRect(_ramka, 10, 10);
    path.addRoundedRect(_back, 10, 10);
    QPen pen(Qt::red, 4);
    painter->setPen(pen);
    painter->fillPath(path, Qt::lightGray);
    painter->drawPath(path);
    painter->setPen(QPen(Qt::black));
    QFont font;
    font.setPixelSize(32);
    painter->setFont(font);
    painter->drawText(_back, Qt::AlignCenter, QStringLiteral("Назад"));
    painter->drawText(_ramka, Qt::AlignLeft, _string);
}

void Hero::Click(int x, int y)
{
    if (_back.contains(x, y))
    {
        _base->_state = 0;
    }
}

void Hero::SetParams()
{
    _string = " Имя: " + _name + "\n" + " Опыт: " + _experience + "\n" +
            " Золото: " + _gold + "\n" + " Кредиты: " + _credits + "\n" +
            " Раса: " + _race + "\n" + " Корабль: " + _ship + "\n" +
            /*" Специальность: " + _specialty + "\n" +
            " Звание: " + _rank + "\n" +
            " Эскадрилия: " + _squadron + "\n" +
            " Место в рейтинге: " + _rating + "\n" +*/
            " Уровень: " + _level + "\n";
}
