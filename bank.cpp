#include "bank.h"

Bank::Bank(QWindow *parent, Base *base)
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
    _credit500 = QRect(10, 10, _parent->geometry().width()-20, _parent->geometry().height()/8-10);
    _credit300 = QRect(10, _parent->geometry().height()/8+10, _parent->geometry().width()-20, _parent->geometry().height()/8-10);
    _credit100 = QRect(10, _parent->geometry().height()/8*2+10, _parent->geometry().width()-20, _parent->geometry().height()/8-10);
    _gold500 = QRect(10, _parent->geometry().height()/8*3+10, _parent->geometry().width()-20, _parent->geometry().height()/8-10);
    _exp2 = QRect(10, _parent->geometry().height()/8*4+10, _parent->geometry().width()-20, _parent->geometry().height()/8-10);
    _exp3 = QRect(10, _parent->geometry().height()/8*5+10, _parent->geometry().width()-20, _parent->geometry().height()/8-10);
    _exp5 = QRect(10, _parent->geometry().height()/8*6+10, _parent->geometry().width()-20, _parent->geometry().height()/8-10);
}

Bank::~Bank()
{}

void Bank::Paint(QPainter *painter)
{
    if (painter == NULL)
    {
        qDebug() << "Error. Painter == NULL.";
        exit(-1);
    }
    QPainterPath path;
    path.addRoundedRect(_back, 10, 10);
    path.addRoundedRect(_credit500, 10, 10);
    path.addRoundedRect(_credit300, 10, 10);
    path.addRoundedRect(_credit100, 10, 10);
    path.addRoundedRect(_gold500, 10, 10);
    path.addRoundedRect(_exp2, 10, 10);
    path.addRoundedRect(_exp3, 10, 10);
    path.addRoundedRect(_exp5, 10, 10);
    QPen pen(Qt::red, 4);
    painter->setPen(pen);
    painter->fillPath(path, Qt::lightGray);
    painter->drawPath(path);
    painter->setPen(QPen(Qt::black));
    QFont font;
    font.setPixelSize(32);
    painter->setFont(font);
    painter->drawText(_back, Qt::AlignCenter, QStringLiteral("Назад"));
    painter->drawText(_credit500, Qt::AlignCenter, QStringLiteral("500 кредитов"));
    painter->drawText(_credit300, Qt::AlignCenter, QStringLiteral("300 кредитов"));
    painter->drawText(_credit100, Qt::AlignCenter, QStringLiteral("100 кредитов"));
    painter->drawText(_gold500, Qt::AlignCenter, QStringLiteral("500.000 золота"));
    painter->drawText(_exp2, Qt::AlignCenter, QStringLiteral("Двойной опыт на месяц"));
    painter->drawText(_exp3, Qt::AlignCenter, QStringLiteral("Тройной опыт на месяц"));
    painter->drawText(_exp5, Qt::AlignCenter, QStringLiteral("Пятерной опыт на месяц"));
}

void Bank::Click(int x, int y)
{
    if (_back.contains(x, y))
    {
        _base->_state = 0;
    }
}
