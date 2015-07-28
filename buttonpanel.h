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
    Grid *_grid;
    QWindow *_parent;
    QString _filename;
    QPainter *_painter;
    QChar _paintsymbol;
    int _width, _height;
    QProcess *_process;
    QFont _font, _brush_font;
    QFontMetrics *_fntmetrics;
    QColor _gridcolor, _textcolor;
    int _mousex, _mousey, _cursor;
    bool _panelside, _firstpaint, _mousepressed;
    QRect _open, _save, _anim_prev, _anim, _anim_next;
    QRect _one, _two, _three, _four, _five, _six, _seven, _eight, _nine;
};

#endif // BUTTONPANEL_H
