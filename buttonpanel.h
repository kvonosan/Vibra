#ifndef BUTTONPANEL_H
#define BUTTONPANEL_H

#include <QtGui>
#include "grid.h"

class ButtonPanel
{
public:
    ~ButtonPanel();
    void Click(int x, int y);
    void Paint(QPainter *painter);
    void KeyPress(QKeyEvent *event);
    ButtonPanel(QWindow *parent, Grid *grid);
    void SetBoundaries(int width, int height);
    void SetMousePressed(bool pressed, int x, int y);
private:
    QFont _font;
    Grid *_grid;
    QWindow *_parent;
    QString _filename;
    QPainter *_painter;
    QChar _paintsymbol;
    QProcess *_process;
    int _width, _height;
    QColor _gridcolor, _textcolor;
    int _mousex, _mousey, _cursor;
    bool _panelside, _firstpaint, _mousepressed;
    QRect _arrow, _pencil, _rubber, _fill, _letter, _quit, _open, _save;
};

#endif // BUTTONPANEL_H
