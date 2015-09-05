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
    }
}

void Fly::Click(int x, int y)
{
    if (_menu)
    {
        _attack = false;
        if (_quit.contains(x, y))
        {
            _net->_disconnect = false;
            _parent->close();
        }
    } else
    {
        _net->GetMyPos();
        _current = _grid->GetSymbolAtWH(x, y);
        if (_current->_number!=_net->_mypos)
        {
            if (_current->_symbol == 'A' || _current->_symbol == 'B' || _current->_symbol == 'C' ||
                    _current->_symbol == 'D' || _current->_symbol == 'E')
            {
                _attack = true;
            } else
            {
                _attack = false;
                _current = NULL;
            }
        }
        if (_attack)
        {
            if (_attack_menu.contains(x,y))
            {
                //anim fire.
                int i = 9;
            }
        }
    }
}

void Fly::KeyPress(int key)
{
    if (_base->_state == 6)
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
