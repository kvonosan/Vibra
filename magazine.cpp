#include "magazine.h"

Magazine::Magazine(QWindow *parent)
{
    if (parent == NULL)
    {
        qDebug() << "Error. parent == NULL.";
        exit(-1);
    }
    _parent = parent;
    _one = QRect(10, 10, _parent->geometry().width()/2-10, _parent->geometry().height()/2-10-50);
    _capt_one = QRect(10, 10, _parent->geometry().width()/2-10, 30);
    _two = QRect(10, _parent->geometry().height()/2+10-50, _parent->geometry().width()/2-10, _parent->geometry().height()/2+10-50);
    _capt_two = QRect(10, _parent->geometry().height()/2+10-50, _parent->geometry().width()/2-10, 30);
    _three = QRect(_parent->geometry().width()/2+10, 10, _parent->geometry().width()/2-20, _parent->geometry().height()/2-10-50);
    _capt_three = QRect(_parent->geometry().width()/2+10, 10, _parent->geometry().width()/2-20, 30);
    _four = QRect(_parent->geometry().width()/2+10, _parent->geometry().height()/2+10-50, _parent->geometry().width()/2-20, _parent->geometry().height()/2+10-50);
    _capt_four = QRect(_parent->geometry().width()/2+10, _parent->geometry().height()/2+10-50, _parent->geometry().width()/2-20, 30);
    _prev = QRect(10, _parent->geometry().height()-20-50, _parent->geometry().width()/3-10, 60);
    _next = QRect(_parent->geometry().width()/3+10, _parent->geometry().height()-20-50, _parent->geometry().width()/3-20, 60);
    _back = QRect(_parent->geometry().width()/3*2, _parent->geometry().height()-20-50, _parent->geometry().width()/3-10, 60);
}

Magazine::~Magazine()
{}

void Magazine::Paint(QPainter *painter)
{
    if (painter == NULL)
    {
        qDebug() << "Error. Painter == NULL.";
        exit(-1);
    }
    QPainterPath path;
    path.addRoundedRect(_one, 10, 10);
    path.addRoundedRect(_capt_one, 10, 10);
    path.addRoundedRect(_two, 10, 10);
    path.addRoundedRect(_capt_two, 10, 10);
    path.addRoundedRect(_three, 10, 10);
    path.addRoundedRect(_capt_three, 10, 10);
    path.addRoundedRect(_four, 10, 10);
    path.addRoundedRect(_capt_four, 10, 10);
    path.addRoundedRect(_prev, 10, 10);
    path.addRoundedRect(_next, 10, 10);
    path.addRoundedRect(_back, 10, 10);
    QPen pen(Qt::red, 4);
    painter->setPen(pen);
    painter->fillPath(path, Qt::green);
    painter->drawPath(path);
    painter->setPen(QPen(Qt::black));
    QFont font;
    font.setPixelSize(32);
    painter->setFont(font);
    painter->drawText(_prev, Qt::AlignCenter, QStringLiteral("Предыдущий"));
    painter->drawText(_next, Qt::AlignCenter, QStringLiteral("Следующий"));
    painter->drawText(_back, Qt::AlignCenter, QStringLiteral("Назад"));
    font.setPixelSize(24);
    painter->setFont(font);
    painter->drawText(_capt_one, Qt::AlignCenter, QStringLiteral("Корабль"));
    painter->drawText(_capt_two, Qt::AlignCenter, QStringLiteral("Двигатель"));
    painter->drawText(_capt_three, Qt::AlignCenter, QStringLiteral("Топливный бак"));
    painter->drawText(_capt_four, Qt::AlignCenter, QStringLiteral("Йотанет"));
}
