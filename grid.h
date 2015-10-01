#ifndef GRID_H
#define GRID_H

#include <QFont>
#include "symbol.h"
#include <QVector>

class Grid
{
public:
    ~Grid();
    Grid(QWindow *parent);
    void Clear();
    void Paint(QPainter *painter);
    Symbol *GetSymbolAt(int x, int y);
    Symbol *GetSymbolInPos(int mypos);
    QVector<int> GetCoordForXY(int x, int y);
    Symbol *GetSymbolAtWH(int width, int heigth);
    QFont _font;
    QWindow *_parent;
    int _otstupX, _otstupY;
    QVector <QVector<Symbol> > _symbols;
};

#endif // GRID_H
