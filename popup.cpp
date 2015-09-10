#include "popup.h"
#include <QDebug>

Popup::Popup(QWindow *parent)
{
    if (parent == NULL)
    {
        qDebug() << "Error: parent == NULL";
        exit(-1);
    }
    _parent = parent;
    _rightBottom = true;
    _life = 20;
}

Popup::~Popup()
{}

void Popup::Paint(QPainter *painter)
{
    if (painter == NULL)
    {
        qDebug() << "Error: painter == NULL";
        exit(-1);
    }
    if (_rightBottom)
    {
        QRect popup(_parent->width()-250, _parent->height()-100, 200, 60);
        painter->fillRect(popup, Qt::black);
        painter->drawRect(popup);
        painter->drawText(popup, Qt::AlignCenter, "life = " + QString::number(_life));
    } else
    {
        QRect popup(_parent->width()-250, 20, 200, 60);
        painter->fillRect(popup, Qt::black);
        painter->drawRect(popup);
        painter->drawText(popup, Qt::AlignCenter, "life = " + QString::number(_life));
    }
}
