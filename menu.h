#ifndef MENU_H
#define MENU_H

#include "grid.h"

class Menu
{
public:
    ~Menu();
    Menu *Next();
    void OnMouseOverSound();
    void Setline(int number);
    void AddMenu(Menu *menu);
    void OnMouseOver(int x, int y);
    void Paint(QPainter *_painter);
    Menu(Grid *grid, QString title = "");
    void Build(int width, int height, QFont *font);
    int _line;
    QString _title;
private:
    Grid *_grid;
    Menu *_nextMenu;
    bool _tabstop, _build, _played;
};

#endif // MENU_H
