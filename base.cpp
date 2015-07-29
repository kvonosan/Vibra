#include "base.h"

Base::Base(QWindow *parent, Grid *grid)
{
    if (parent == NULL || grid == NULL)
    {
        qDebug() << "Error. parent == NULL or grid == NULL.";
        exit(-1);
    }
    _parent = parent;
    _grid = grid;
}

Base::~Base()
{}
