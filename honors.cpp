#include "honors.h"

Honors::Honors(QWindow *parent, Base *base)
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
    _back = QRect(_parent->geometry().width()/3*2, _parent->geometry().height()-20-50, _parent->geometry().width()/3-20, 60);
    _ramka1 = QRect(10, 10, _parent->geometry().width()-20, (_parent->geometry().height()-60)/3-30);
    _ramka1_capt = QRect(10, 10, _parent->geometry().width()-20, 30);
    _ramka2 = QRect(10, (_parent->geometry().height()-60)/3-10, _parent->geometry().width()-20, (_parent->geometry().height()-60)/3-10);
    _ramka2_capt = QRect(10, (_parent->geometry().height()-60)/3-10, _parent->geometry().width()-20, 30);
    _ramka3 = QRect(10, (_parent->geometry().height()-60)/3*2-10, _parent->geometry().width()-20, (_parent->geometry().height()-60)/3-10);
    _ramka3_capt = QRect(10, (_parent->geometry().height()-60)/3*2-10, _parent->geometry().width()-20, 30);
}

Honors::~Honors()
{}

void Honors::Paint(QPainter *painter)
{
    if (painter == NULL)
    {
        qDebug() << "Error. Painter == NULL.";
        exit(-1);
    }
    QPainterPath path;
    path.addRoundedRect(_ramka1, 10, 10);
    path.addRoundedRect(_ramka2, 10, 10);
    path.addRoundedRect(_ramka3, 10, 10);
    path.addRoundedRect(_ramka1_capt, 10, 10);
    path.addRoundedRect(_ramka2_capt, 10, 10);
    path.addRoundedRect(_ramka3_capt, 10, 10);
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
    painter->drawText(_ramka1_capt, Qt::AlignCenter, QStringLiteral("В бою"));
    painter->drawText(_ramka2_capt, Qt::AlignCenter, QStringLiteral("За специальность"));
    painter->drawText(_ramka3_capt, Qt::AlignCenter, QStringLiteral("Награды расы"));
}

void Honors::Click(int x, int y)
{
    if (_back.contains(x, y))
    {
        _base->_state = 0;
    }
}
