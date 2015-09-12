#include "fly.h"
#include "symbol.h"
#include <QMessageBox>

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
    _grid = new Grid(_parent);
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
    _popup = new Popup(_parent);
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
        painter->drawText(_duel_menu, Qt::AlignCenter, QStringLiteral("Отмена"));
    } else if (_net->_fire)
    {
        NextTime(painter);
        if (_current!= NULL)
        {
            if ((_firecoords[0] > _parent->width()-400 && _firecoords[2] > _parent->height()-160)
                    || (_mycoords[0] > _parent->width()-400 && _mycoords[2] > _parent->height()-160))
            {
                _popup->_rightBottom = false;
            } else
            {
                _popup->_rightBottom = true;
            }
        }
        _popup->Paint(painter);
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
        if (_current != NULL)
        {
            if (_current->_number!=_net->_mypos)
            {
                if (_current->_symbol == 'A' || _current->_symbol == 'B' || _current->_symbol == 'C' ||
                        _current->_symbol == 'D' || _current->_symbol == 'E')
                {
                    _attack = true;
                }
                if (_current->_symbol == 'b')
                {
                    _base->_state = 0;
                }
                if (_current->_symbol == 'r')
                {
                    _net->GetResource(_current->_number);
                }
            }
        }
    }else if (_attack)
    {
        if (_attack_menu.contains(x,y))
        {
            if (_current != NULL)
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
        }
        _attack = false;
        if (_current != NULL)
        {
            _net->Fire(_current->_number, _popup);
        }
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
            if (key == Qt::Key_W || key == 0x426)
            {
                _net->Top();
                _net->BufferizeMap();
            }
            if (key == Qt::Key_S || key == 0x42B)
            {
                _net->Bottom();
                _net->BufferizeMap();
            }
            if (key == Qt::Key_A || key == 0x424)
            {
                _net->Left();
                _net->BufferizeMap();
            }
            if (key == Qt::Key_D || key == 0x412)
            {
                _net->Right();
                _net->BufferizeMap();
            }
        }
    }
}

void Fly::NextTime(QPainter *painter)
{
    if (_current != NULL)
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
                    _net->Fire(_current->_number, _popup);
                    _time.restart();
                }
            }
        }
        if (_net->_killed)
        {
            _current->_symbol = ' ';
            _net->_fire = false;
            _net->_killed = false;
            if (_net->_level > 0)
            {
                QMessageBox* pmbx = new QMessageBox("Повышение уровня!",
                                    "<b>Ваш уровень <i>" + QString::number(_net->_level) + "</i>!</b>",
                                    QMessageBox::Information,
                                    QMessageBox::NoButton,
                                    QMessageBox::Ok,
                                    QMessageBox::NoButton);
                pmbx->exec();
                delete pmbx;
            }
        }
    }
}
