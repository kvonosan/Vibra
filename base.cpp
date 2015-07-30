#include "base.h"

Base::Base()
{
    _font.setPixelSize(32);
    _bank = QRect(10, 10, 80, 70);
    //_magazine = QRect();
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
    QPen pen(Qt::red, 4);
    painter->setPen(pen);
    painter->fillPath(path, Qt::green);
    painter->drawPath(path);
    painter->setPen(QPen(Qt::black));
    painter->setFont(_font);
    painter->drawText(_bank, Qt::AlignCenter, QStringLiteral("Банк"));
}
