#ifndef POPUP
#define POPUP

#include <QtGui>

class Popup
{
public:
    Popup(QWindow *parent);
    ~Popup();
    void Paint(QPainter *painter);
    QWindow *_parent;
    bool _rightBottom, _leftBottom;
    int _life_enemy, _life;
};
#endif // POPUP

