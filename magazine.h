#ifndef MAGAZINE
#define MAGAZINE

#include <QtGui>

class Magazine
{
public:
    Magazine(QWindow *parent);
    ~Magazine();
    void Paint(QPainter *painter);
private:
    QRect _one, _two, _three, _four, _next, _prev, _back;
    QRect _capt_one, _capt_two, _capt_three, _capt_four;
    int _state;
    QWindow *_parent;
};

#endif // MAGAZINE
