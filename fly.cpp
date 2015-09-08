#include "fly.h"
#include "symbol.h"

Fly::Fly(Net *net, QWindow *parent, Base *base)
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
    if (net == NULL)
    {
        qDebug() << "Error. net == NULL.";
        exit(-1);
    }
    _net = net;
    _net->_fire = false;
    _menu = false;
    _attack = false;
    int menu_num = 8;
    _compute = false;
    _grid = new Grid(Qt::black, Qt::white);
    _state = QRect(10, 10, _parent->geometry().width()-20, _parent->geometry().height()/menu_num-10);
    _exp = QRect(10, _parent->geometry().height()/menu_num*1+10, _parent->geometry().width()-20, _parent->geometry().height()/menu_num-10);
    _energy = QRect(10, _parent->geometry().height()/menu_num*2+10, _parent->geometry().width()-20, _parent->geometry().height()/menu_num-10);
    _attack_menu = QRect(10, _parent->geometry().height()/menu_num*2+10, _parent->geometry().width()-20, _parent->geometry().height()/menu_num-10);
    _radar = QRect(10, _parent->geometry().height()/menu_num*3+10, _parent->geometry().width()-20, _parent->geometry().height()/menu_num-10);
    _duel_menu = QRect(10, _parent->geometry().height()/menu_num*3+10, _parent->geometry().width()-20, _parent->geometry().height()/menu_num-10);
    _cartograph = QRect(10, _parent->geometry().height()/menu_num*4+10, _parent->geometry().width()-20, _parent->geometry().height()/menu_num-10);
    _scaner = QRect(10, _parent->geometry().height()/menu_num*5+10, _parent->geometry().width()-20, _parent->geometry().height()/menu_num-10);
    _hold = QRect(10, _parent->geometry().height()/menu_num*6+10, _parent->geometry().width()-20, _parent->geometry().height()/menu_num-10);
    _quit = QRect(10, _parent->geometry().height()/menu_num*7+10, _parent->geometry().width()-20, _parent->geometry().height()/menu_num-10);

}

Fly::~Fly()
{
    delete _grid;
}

void Fly::Paint(QPainter *painter)
{
    if (painter == NULL)
    {
        qDebug() << "Error. Painter == NULL.";
        exit(-1);
    }
    if (!_compute)
    {
        _grid->ComputeSize(_parent->geometry().width(), _parent->geometry().height());
    }
    _compute = true;
    _grid->Paint(painter);
    if (_menu)
    {
        QPainterPath path;
        path.addRoundedRect(_state, 10, 10);
        path.addRoundedRect(_exp, 10, 10);
        path.addRoundedRect(_energy, 10, 10);
        path.addRoundedRect(_radar, 10, 10);
        path.addRoundedRect(_cartograph, 10, 10);
        path.addRoundedRect(_scaner, 10, 10);
        path.addRoundedRect(_hold, 10, 10);
        path.addRoundedRect(_quit, 10, 10);
        QPen pen(Qt::red, 4);
        painter->setPen(pen);
        painter->fillPath(path, Qt::lightGray);
        painter->drawPath(path);
        painter->setPen(QPen(Qt::black));
        QFont font;
        font.setPixelSize(32);
        painter->setFont(font);
        painter->drawText(_state, Qt::AlignCenter, QStringLiteral("Состоние корабля"));
        painter->drawText(_exp, Qt::AlignCenter, QStringLiteral("Опыт"));
        painter->drawText(_energy, Qt::AlignCenter, QStringLiteral("Энергия"));
        painter->drawText(_radar, Qt::AlignCenter, QStringLiteral("Радар"));
        painter->drawText(_cartograph, Qt::AlignCenter, QStringLiteral("Картограф"));
        painter->drawText(_scaner, Qt::AlignCenter, QStringLiteral("Сканер"));
        painter->drawText(_hold, Qt::AlignCenter, QStringLiteral("Трюм"));
        painter->drawText(_quit, Qt::AlignCenter, QStringLiteral("Выход"));
    } else if (_attack)
    {
        QPainterPath path;
        path.addRoundedRect(_attack_menu, 10, 10);
        path.addRoundedRect(_duel_menu, 10, 10);
        QPen pen(Qt::red, 4);
        painter->setPen(pen);
        painter->fillPath(path, Qt::lightGray);
        painter->drawPath(path);
        painter->setPen(QPen(Qt::black));
        QFont font;
        font.setPixelSize(32);
        painter->setFont(font);
        painter->drawText(_attack_menu, Qt::AlignCenter, QStringLiteral("Уничтожить"));
        painter->drawText(_duel_menu, Qt::AlignCenter, QStringLiteral("Уничтожить в режиме дуэль"));
    } else if (_net->_fire)
    {
        NextTime(painter);
    }
}

void Fly::Click(int x, int y)
{
    if (_net->_fire)
    {
        return;
    }
    if (_menu)
    {
        _attack = false;
        if (_quit.contains(x, y))
        {
            _net->_disconnect = false;
            _parent->close();
        }
    } else if (!_attack)
    {
        _net->GetMyPos();
        _current = _grid->GetSymbolAtWH(x, y);
        if (_current->_number!=_net->_mypos)
        {
            if (_current->_symbol == 'A' || _current->_symbol == 'B' || _current->_symbol == 'C' ||
                    _current->_symbol == 'D' || _current->_symbol == 'E')
            {
                _attack = true;
            }
        }
    }else if (_attack)
    {
        if (_attack_menu.contains(x,y))
        {
            _firecoords = _grid->GetCoordForXY(_current->_x, _current->_y);
            Symbol *my = _grid->GetSymbolInPos(_net->_mypos);
            if (my != NULL)
            {
                _mycoords = _grid->GetCoordForXY(my->_x, my->_y);
                _net->_fire = true;
                _time.restart();
            }
        }
        _attack = false;
        _net->Fire(_current->_number);
    }
}

void Fly::KeyPress(int key)
{
    if (_base->_state == 6)
    {
        if (!_net->_fire)
        {
            if (key == Qt::Key_Escape)
            {
                _menu = !_menu;
                _attack = false;
            }
            if (key == Qt::Key_W)
            {
                _net->Top();
                _net->BufferizeMap();
            }
            if (key == Qt::Key_S)
            {
                _net->Bottom();
                _net->BufferizeMap();
            }
            if (key == Qt::Key_A)
            {
                _net->Left();
                _net->BufferizeMap();
            }
            if (key == Qt::Key_D)
            {
                _net->Right();
                _net->BufferizeMap();
            }
        }
    }
}

void Fly::NextTime(QPainter *painter)
{
    if (_net->_fire && _net->_firepos == _current->_number)
    {
        int centrX = (_mycoords[1] - _mycoords[0])/2;
        int centrFireX = (_firecoords[1] - _firecoords[0])/2;
        int time, lineX, lineY, posX, posY;
        if (_time.elapsed() < 1000)
        {
            time = _time.elapsed()/100;//1..10
            lineX = abs((_mycoords[0] + centrX) - (_firecoords[0] + centrFireX));
            lineY = abs((_mycoords[2] + centrX) - (_firecoords[2] + centrFireX));
            posX = lineX / 10 * time;
            posY = lineY / 10 * time;
        }
        if (_net->_fire)
        {
            int mnX, mnY;
            if (_mycoords[0] <= _firecoords[0])
            {
                mnX = 1;
            } else
            {
                mnX = -1;
            }
            if (_mycoords[2] <= _firecoords[2])
            {
                mnY = 1;
            } else
            {
                mnY = -1;
            }
            painter->drawText(QRect(_mycoords[0]+posX*mnX, _mycoords[2]+posY*mnY, 32, 32),"*");
            if (posX >= lineX && posY >= lineY)
            {
                _net->Fire(_current->_number);
                _time.restart();

            }
        }
    }
    if (_net->_killed)
    {
        _current->_symbol = ' ';
        _net->_fire = false;
        _net->_killed = false;
    }
}
