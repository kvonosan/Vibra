#ifndef BASE
#define BASE

#include <QtGui>
#include "grid.h"

class Base
{
public:
    Base(QWindow *parent, Grid *grid);
    ~Base();
private:
    QRect _quit;
    Grid *_grid;
    QWindow *_parent;
};

#endif // BASE
