#include "base.h"

Base::Base()
{
    _font.setPixelSize(32);
    _bank = QRect(10, 10, 80, 70);
    _magazine = QRect(100, 10, 130, 70);
    _hero = QRect(240, 10, 100, 70);
    _bar = QRect(350, 10, 70, 70);
    _honors = QRect(430, 10, 140, 70);
    _rating = QRect(10, 90, 140, 70);
    _flight = QRect(160, 90, 250, 70);
    _quit = QRect(420, 90, 140, 70);
}

Base::~Base()
{}

void Base::Paint(QPainter *painter)
{
    if (painter == NULL)
    {
        qDebug() << "Error. Painter == NULL.";
        exit(-1);
    }
    QPainterPath path;
    path.addRoundedRect(_bank, 10, 10);
    path.addRoundedRect(_magazine, 10, 10);
    path.addRoundedRect(_hero, 10, 10);
    path.addRoundedRect(_bar, 10, 10);
    path.addRoundedRect(_honors, 10, 10);
    path.addRoundedRect(_rating, 10, 10);
    path.addRoundedRect(_flight, 10, 10);
    path.addRoundedRect(_quit, 10, 10);
    QPen pen(Qt::red, 4);
    painter->setPen(pen);
    painter->fillPath(path, Qt::green);
    painter->drawPath(path);
    painter->setPen(QPen(Qt::black));
    painter->setFont(_font);
    painter->drawText(_bank, Qt::AlignCenter, QStringLiteral("Банк"));
    painter->drawText(_magazine, Qt::AlignCenter, QStringLiteral("Магазин"));
    painter->drawText(_hero, Qt::AlignCenter, QStringLiteral("Герой"));
    painter->drawText(_bar, Qt::AlignCenter, QStringLiteral("Бар"));
    painter->drawText(_honors, Qt::AlignCenter, QStringLiteral("Награды"));
    painter->drawText(_rating, Qt::AlignCenter, QStringLiteral("Рейтинг"));
    painter->drawText(_flight, Qt::AlignCenter, QStringLiteral("Вылет в космос"));
    painter->drawText(_quit, Qt::AlignCenter, QStringLiteral("Выход"));
}
