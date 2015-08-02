#include "frame.h"

Frame::Frame(QWindow *parent)
{
    if (parent == NULL)
    {
        qDebug() << "Error. parent == NULL.";
        exit(-1);
    }
    _parent = parent;
    _font.setPixelSize(32);
    _grid = new Grid(Qt::black, Qt::white, &_font);
}

Frame::~Frame()
{}

void Frame::Paint(QPainter *painter)
{
    if (painter == NULL)
    {
        qDebug() << "Error. Painter == NULL.";
        exit(-1);
    }
    _painter = painter;
    _grid->ComputeSize(_parent->width(), _parent->height());
    QFile file(":/res/frame/cosmos_panel.ani");
    if (file.open(QIODevice::ReadOnly))
    {
        QTextStream stream(&file);
        for (int i=0; i<_grid->GetSizeX();i++)
            for (int j=0;j<_grid->GetSizeY();j++)
            {
                stream >> (_grid->GetSymbolAt(i,j)->symbol);
                qDebug() << _grid->GetSymbolAt(i,j)->symbol;
            }
        file.close();
    }
    _grid->Paint(painter);
}
