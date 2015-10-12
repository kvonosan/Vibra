#include "news.h"

News::News(QWindow *parent, Base *base)
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
    _ramka1 = QRect(15, 70, _parent->geometry().width()-25, _parent->geometry().height()-60-100);
    _ramka1_capt = QRect(10, 10, _parent->geometry().width()-20, 50);
}

News::~News()
{}

void News::Paint(QPainter *painter)
{
    if (painter == NULL)
    {
        qDebug() << "Error. Painter == NULL.";
        exit(-1);
    }
    QPainterPath path;
    path.addRoundedRect(_ramka1, 10, 10);
    path.addRoundedRect(_back, 10, 10);
    path.addRoundedRect(_ramka1_capt, 10, 10);
    QPen pen(Qt::red, 4);
    painter->setPen(pen);
    painter->fillPath(path, Qt::lightGray);
    painter->drawPath(path);
    painter->setPen(QPen(Qt::black));
    QFont font;
    font.setPixelSize(32);
    painter->setFont(font);
    painter->drawText(_back, Qt::AlignCenter, QStringLiteral("Назад"));
    font.setPixelSize(24);
    painter->setFont(font);
    painter->drawText(_ramka1, Qt::TextWordWrap, _base->_net->_news);
    font.setPixelSize(32);
    painter->setFont(font);
    painter->setPen(QPen(Qt::black));
    painter->drawText(_ramka1_capt, Qt::AlignCenter, QStringLiteral("Вселенная йотанет 768д:"));
}

void News::Click(int x, int y)
{
    if (_back.contains(x, y))
    {
        _base->_state = 0;
    }
}
