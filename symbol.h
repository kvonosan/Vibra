#ifndef SYMBOL_H
#define SYMBOL_H

#include <QtGui>

class Symbol{
public:
    Symbol();
    ~Symbol();
    QChar _symbol;
    QColor TextColor;
    QColor GridColor;
    int _number, _x, _y;
};

#endif // SYMBOL_H
