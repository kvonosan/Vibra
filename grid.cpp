#include "grid.h"
#include <QDebug>

Grid::Grid(QWindow *parent, Base *base)
{
    if (parent == NULL)
    {
        qDebug() << "Error: parent == NULL.";
        exit(-1);
    }
    _parent = parent;
    _base = base;
    _font.setPixelSize(32);
    if (_parent->width() >= 1024 && _parent->height()>= 768)
    {
        _otstupX = (_parent->width() - 1024)/2;
        _otstupY = (_parent->height() - 768)/2;
    } else
    {
        _otstupX = 0;
        _otstupY = 0;
    }
    _symbols.resize(32);
    for (int i=0; i<_symbols.size(); i++)
    {
        _symbols[i].resize(24);
        for (int j=0; j<_symbols[i].size(); j++)
        {
            _symbols[i][j].GridColor = Qt::black;
            _symbols[i][j].TextColor = Qt::white;
            _symbols[i][j]._symbol = ' ';
            _symbols[i][j]._x = i;
            _symbols[i][j]._y = j;
        }
    }
    int g = 0;
    for(int j=0; j < 24; j++)
        for(int i=0; i < 32; i++)
        {
            _symbols[i][j]._number = g;
            g++;
        }
}

void Grid::Clear()
{
    for (int i=0; i<_symbols.size(); i++)
    {
        for (int j=0; j<_symbols[i].size(); j++)
        {
            _symbols[i][j]._symbol = ' ';
        }
    }
}

Grid::~Grid()
{}

void Grid::Paint(QPainter *painter)
{
    if (painter == NULL)
    {
        qDebug() << "Error: painter = NULL.";
        exit(-1);
    }
    if (_base != NULL)
    {
        for(int j=0; j < 24; j++)
            for(int i=0; i < 32; i++)
            {
                if (_symbols[i][j]._number == _base->_net->_mypos)
                {
                    _symbols[i][j].TextColor = Qt::green;
                }
            }
    }
    painter->setFont(_font);
    painter->setRenderHint(QPainter::Antialiasing);
    for (int i = 0; i < 32; i++)
    {
        for(int j = 0; j < 24; j++)
        {
            painter->setPen(QPen(_symbols[i][j].TextColor));
            painter->drawText(i*32 + _otstupX, j*32 + _otstupY, i*32+32, j*32+32, Qt::AlignAbsolute, _symbols[i][j]._symbol);
        }
    }
}

Symbol *Grid::GetSymbolAt(int x, int y)
{
    if (x>=0 && x<32 && y >=0 && y <24)
    {
        return &_symbols[x][y];
    }
    return NULL;
}

Symbol *Grid::GetSymbolAtWH(int width, int heigth)
{
    int x = (width - _otstupX*2)/32;
    int y = (heigth - _otstupY*2)/32;
    return GetSymbolAt(x, y);
}

QVector<int> Grid::GetCoordForXY(int x, int y)
{
    QVector<int> coord;
    int x0 = _otstupX + x*32;
    int x1 = _otstupX + (x+1)*32;
    int y0 = _otstupY + y*32;
    int y1 = _otstupY + (y+1)*32;
    coord.push_back(x0);//x0
    coord.push_back(x1);//x1
    coord.push_back(y0);//y0
    coord.push_back(y1);//y1
    return coord;
}

Symbol *Grid::GetSymbolInPos(int mypos)
{
    for(int i=0; i < 32; i++)
        for(int j=0; j < 24; j++)
        {
            if (_symbols[i][j]._number == mypos)
            {
                return &_symbols[i][j];
            }
        }
    return NULL;
}
