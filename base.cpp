#include "base.h"

Base::Base(QWindow *parent, Net *net, MainWindow *mainwindow)
{
    if (parent == NULL)
    {
        qDebug() << "Error: parent == NULL.";
        exit(-1);
    }
    _parent = parent;
    if (net == NULL)
    {
        qDebug() << "Error: net == NULL.";
        exit(-1);
    }
    _net = net;
    if (mainwindow == NULL)
    {
        qDebug() << "Error: mainwindow == NULL.";
        exit(-1);
    }
    _mainwindow = mainwindow;
    _font.setPixelSize(32);
    _bank = QRect(10, 10, 80, 70);
    _magazine = QRect(100, 10, 130, 70);
    _hero = QRect(240, 10, 100, 70);
    _bar = QRect(350, 10, 70, 70);
    _honors = QRect(430, 10, 140, 70);
    _rating = QRect(10, 90, 140, 70);
    _flight = QRect(160, 90, 250, 70);
    _quit = QRect(420, 90, 150, 70);
    _generator = QRect(10, 170, 330, 70);
    _news = QRect(350, 170, 220, 70);
    _improvement = QRect(10, 250, 220, 70);
    _state = 0;
    _magazine_obj = new Magazine(_parent, this);
    _hero_obj = new Hero(_parent, this);
    _honors_obj = new Honors(_parent, this);
    _rating_obj = new Rating(_parent, this);
    _bank_obj = new Bank(_parent, this);
    _fly = new Fly(_net, _parent, this);
    _news_obj = new News(_parent, this);
}

Base::~Base()
{
    delete _magazine_obj;
    delete _hero_obj;
    delete _honors_obj;
    delete _rating_obj;
    delete _bank_obj;
    delete _fly;
    delete _news_obj;
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
        QPainterPath path;
        path.addRoundedRect(_bank, 10, 10);
        path.addRoundedRect(_magazine, 10, 10);
        path.addRoundedRect(_hero, 10, 10);
        path.addRoundedRect(_bar, 10, 10);
        path.addRoundedRect(_honors, 10, 10);
        path.addRoundedRect(_rating, 10, 10);
        path.addRoundedRect(_flight, 10, 10);
        path.addRoundedRect(_quit, 10, 10);
        path.addRoundedRect(_generator, 10, 10);
        path.addRoundedRect(_news, 10, 10);
        path.addRoundedRect(_improvement, 10, 10);
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
        painter->drawText(_flight, Qt::AlignCenter, QStringLiteral("Вылет в йотанет"));
        painter->drawText(_quit, Qt::AlignCenter, QStringLiteral("Выход"));
        painter->drawText(_generator, Qt::AlignCenter, QStringLiteral("Генератор человека"));
        painter->drawText(_news, Qt::AlignCenter, QStringLiteral("Справка"));
        painter->drawText(_improvement, Qt::AlignCenter, QStringLiteral("Улучшения"));
    } break;
    case 1:
    {
        _magazine_obj->Paint(painter);
    } break;
    case 2:
    {
        _hero_obj->Paint(painter);
    } break;
    case 3:
    {
        _honors_obj->Paint(painter);
    } break;
    case 4:
    {
        _rating_obj->Paint(painter);
    } break;
    case 5:
    {
        _bank_obj->Paint(painter);
    } break;
    case 6:
    {
        _fly->Paint(painter);
    } break;
    case 7:
    {
        _news_obj->Paint(painter);
    } break;
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
            _state = 5;
        } else if (_magazine.contains(x,y))
        {
            _state = 1;
        } else if (_hero.contains(x,y))
        {
            _net->GetInfo();
            _state = 2;
        }else if (_bar.contains(x,y))
        {
            //_frame->_target = "бар";
        }else if (_honors.contains(x,y))
        {
            _state = 3;
        } else if (_rating.contains(x,y))
        {
            _state = 4;
        } else if (_flight.contains(x,y))
        {
           _state = 6;
           _net->BufferizeMap();
        } else if (_quit.contains(x,y))
        {
            _net->_disconnect = false;
            _parent->close();
        } else if (_generator.contains(x, y))
        {
        } else if (_news.contains(x, y))
        {
            _net->GetNews();
            _state = 7;
        } else if (_improvement.contains(x, y))
        {
        }else
        {
            _state = 0;
        }
    } break;
    case 1:
    {
        _magazine_obj->Click(x, y);
    } break;
    case 2:
    {
        _hero_obj->Click(x, y);
    } break;
    case 3:
    {
        _honors_obj->Click(x, y);
    } break;
    case 4:
    {
        _rating_obj->Click(x, y);
    } break;
    case 5:
    {
        _bank_obj->Click(x, y);
    } break;
    case 6:
    {
        _fly->Click(x, y);
    } break;
    case 7:
    {
        _news_obj->Click(x, y);
    } break;
    }
}

void Base::KeyPress(int key)
{
    switch (_state)
    {
    case 6:
    {
        _fly->KeyPress(key);
    } break;
    }
}
