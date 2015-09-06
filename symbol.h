#ifndef SYMBOL_H
#define SYMBOL_H

#include <QtGui>

class Symbol
{
public:
    Symbol();
    ~Symbol();
    QChar _symbol;
    QColor TextColor;
    QColor GridColor;
    int _number, _x, _y;
    bool _attacked;
    int _life, _energy, _armor, _fuel;
};

#endif // SYMBOL_H
