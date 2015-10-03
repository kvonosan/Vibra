#ifndef GRID_H
#define GRID_H

#include <QFont>
#include "symbol.h"
#include <QVector>
#include "base.h"

class Base;

class Grid
{
public:
    ~Grid();
    Grid(QWindow *parent, Base *base);
    void Clear();
    void Paint(QPainter *painter);
    Symbol *GetSymbolAt(int x, int y);
    Symbol *GetSymbolInPos(int mypos);
    QVector<int> GetCoordForXY(int x, int y);
    Symbol *GetSymbolAtWH(int width, int heigth);
    QFont _font;
    QWindow *_parent;
    Base *_base;
    int _otstupX, _otstupY;
    QVector <QVector<Symbol> > _symbols;
};

#endif // GRID_H
