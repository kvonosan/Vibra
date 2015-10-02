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
    _life_enemy = 0;
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
        QRect popup(_parent->width()-400, _parent->height()-140, 300, 120);
        painter->fillRect(popup, Qt::black);
        painter->drawRect(popup);
        painter->drawText(popup, Qt::AlignCenter, "Противник " + QString::number(_life_enemy) + "\nСвой " + QString::number(_life));
    } else
    {
        if (_leftBottom)
        {
            QRect popup(100, 20, 300, 120);
            painter->fillRect(popup, Qt::black);
            painter->drawRect(popup);
            painter->drawText(popup, Qt::AlignCenter, "Противник " + QString::number(_life_enemy) + "\nСвой " + QString::number(_life));
        } else
        {
            QRect popup(_parent->width()-400, 20, 300, 120);
            painter->fillRect(popup, Qt::black);
            painter->drawRect(popup);
            painter->drawText(popup, Qt::AlignCenter, "Противник " + QString::number(_life_enemy) + "\nСвой " + QString::number(_life));
        }
    }
}
