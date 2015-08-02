#include "base.h"

Base::Base(QWindow *parent)
{
    if (parent == NULL)
    {
        qDebug() << "Error. parent == NULL.";
        exit(-1);
    }
    _parent = parent;
    _font.setPixelSize(32);
    _bank = QRect(10, 10, 80, 70);
    _magazine = QRect(100, 10, 130, 70);
    _hero = QRect(240, 10, 100, 70);
    _bar = QRect(350, 10, 70, 70);
    _honors = QRect(430, 10, 140, 70);
    _rating = QRect(10, 90, 140, 70);
    _flight = QRect(160, 90, 250, 70);
    _quit = QRect(420, 90, 140, 70);
    _frame = new Frame(_parent);
    _state = 0;
    _magazine_obj = new Magazine(_parent);
}

Base::~Base()
{
    delete _frame;
    delete _magazine_obj;
}

void Base::Paint(QPainter *painter)
{
    if (painter == NULL)
    {
        qDebug() << "Error. Painter == NULL.";
        exit(-1);
    }
    switch (_state)
    {
    case 0:
    {
        _frame->_action = "стоять";
        _frame->_view = "база";
        _frame->_rank = "новобранец";
        _frame->_ship = "класс А";
        _frame->Paint(painter);
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
        break;
    case 1:
    {
        _magazine_obj->Paint(painter);
    }
        break;
    }
}

void Base::MouseMove(int x, int y)
{
    switch (_state)
    {
    case 0:
    {
        if (_bank.contains(x,y))
        {
            _frame->_target = "банк";
        } else if (_magazine.contains(x,y))
        {
            _frame->_target = "магазин";
        } else if (_hero.contains(x,y))
        {
            _frame->_target="герой";
        }else if (_bar.contains(x,y))
        {
            _frame->_target = "бар";
        }else if (_honors.contains(x,y))
        {
            _frame->_target = "награды";
        } else if (_rating.contains(x,y))
        {
            _frame->_target = "рейтинг";
        } else if (_flight.contains(x,y))
        {
            _frame->_target = "вылет";
        } else if (_quit.contains(x,y))
        {
            _frame->_target = "выход";
        } else
        {
            _frame->_target = "";
        }
    }
        break;
    }

}

void Base::Click(int x, int y)
{
    switch (_state)
    {
    case 0:
    {
        if (_bank.contains(x,y))
        {
            //_frame->_target = "банк";
        } else if (_magazine.contains(x,y))
        {
            _state = 1;
        } else if (_hero.contains(x,y))
        {
            //_frame->_target="герой";
        }else if (_bar.contains(x,y))
        {
            //_frame->_target = "бар";
        }else if (_honors.contains(x,y))
        {
            //_frame->_target = "награды";
        } else if (_rating.contains(x,y))
        {
            //_frame->_target = "рейтинг";
        } else if (_flight.contains(x,y))
        {
            //_frame->_target = "вылет";
        } else if (_quit.contains(x,y))
        {
            _parent->close();
        } else
        {
            _state = 0;
        }
    } break;
    }
}
