#include "frame.h"

Frame::Frame(QWindow *parent)
{
    if (parent == NULL)
    {
        qDebug() << "Error. parent == NULL.";
        exit(-1);
    }
    _parent = parent;
    _grid = new Grid(Qt::black, Qt::white);
}

Frame::~Frame()
{
    delete _grid;
}

void Frame::Paint(QPainter *painter)
{
    if (painter == NULL)
    {
        qDebug() << "Error. Painter == NULL.";
        exit(-1);
    }
    _painter = painter;
    _grid->ComputeSize(_parent->width(), _parent->height());
    SetAction();
    SetTarget();
    SetView();
    SetRank();
    SetShip();
    _grid->Paint(painter);
}

void Frame::SetAction()
{
    int posx = 1;
    int posy = _grid->GetSizeY() - 3;
    QString result = "Д:" + _action;
    int g = 0;
    while(g!=result.length())
    {
        (_grid->GetSymbolAt(posx+g, posy)->symbol) = result[g];
        g++;
    }
}

void Frame::SetTarget()
{
    int posx = _grid->GetSizeX()/3;
    int posy = _grid->GetSizeY() - 3;
    QString result = "Ц:" + _target;
    int g = 0;
    while(g!=result.length())
    {
        (_grid->GetSymbolAt(posx+g, posy)->symbol) = result[g];
        g++;
    }
}

void Frame::SetView()
{
    int posx = _grid->GetSizeX()/3*2+3;
    int posy = _grid->GetSizeY() - 3;
    QString result = "В:" + _view;
    int g = 0;
    while(g!=result.length())
    {
        (_grid->GetSymbolAt(posx+g, posy)->symbol) = result[g];
        g++;
    }
}

void Frame::SetRank()
{
    int posx = 1;
    int posy = _grid->GetSizeY() - 2;
    QString result = "З:" + _rank;
    int g = 0;
    while(g!=result.length())
    {
        (_grid->GetSymbolAt(posx+g, posy)->symbol) = result[g];
        g++;
    }
}

void Frame::SetShip()
{
    int posx = _grid->GetCenterX();
    int posy = _grid->GetSizeY() - 2;
    QString result = "К:" + _ship;
    int g = 0;
    while(g!=result.length())
    {
        (_grid->GetSymbolAt(posx+g, posy)->symbol) = result[g];
        g++;
    }
}
