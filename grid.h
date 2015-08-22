#ifndef GRID_H
#define GRID_H

#include "symbol.h"
#include <QVector>

class Grid{
public:
    ~Grid();
    void Paint(QPainter *painter);
    int GetSizeX(){return _sizeX;}
    int GetSizeY(){return _sizeY;}
    Symbol *GetSymbolAt(int x, int y);
    int GetCenterX(){return _sizeX / 2;}
    int GetCenterY(){return _sizeY / 2;}
    void ComputeSize(int SizeX, int SizeY);
    Symbol *GetSymbolAtWH(int width, int heigth);
    QVector<int> GetCoordForWord(QString word);
    QVector<int> GetCoordForWordInSymbols(QString word);
    void SetGridColor(QPainter *painter, QColor gridcolor);
    void SetTextColor(QPainter *painter, QColor textcolor);
    QVector <QVector<Symbol> >GetSymbols(){return _symbols;}
    void SetSymbols(QVector <QVector<Symbol> > symbols){_symbols = symbols;}
    Grid(QColor defaultgridcolor, QColor defaulttextcolor);
    void PrintWordOnCenter(QPainter *painter, QString word, int line, QColor gridcolor = Qt::black, QColor textcolor = Qt::white);
    void PrintWordOnRight(QPainter *painter, QString word, int line, QColor gridcolor = Qt::black, QColor textcolor = Qt::white);
    void PrintWordOnLeft(QPainter *painter,QString word, int line, QColor gridcolor = Qt::black, QColor textcolor = Qt::white);
    QFont *_font;
    bool _computed;
    QColor _defaultgridcolor, _defaulttextcolor;
    int _width, _heigth;
private:
    QVector <QVector<Symbol> > _symbols;
    int _sizeX, _sizeY, _centrX, _centrY;
};

#endif // GRID_H
