#include "menu.h"
#include <QDebug>
#include <QSound>

Menu::Menu(Grid *grid, QString title)
{
    if (grid == NULL)
    {
        qDebug() << "Error grid == NULL.";
        exit(-1);
    }
    _grid = grid;
    if (title.length() == 0)
    {
        qDebug() << "Error. title.length = 0.";
        exit(-1);
    }
    _title = title;
    _build = false;
    _nextMenu = NULL;
    _tabstop = false;
    _played = false;
}

Menu::~Menu()
{
}

void Menu::Paint(QPainter *painter)
{
    if (painter == NULL)
    {
        qDebug() << "Error. Painter == NULL.";
        exit(-1);
    }
    if (_build)
    {
        Menu *menu = this;
        while(menu != NULL)
        {
            if (menu->_tabstop)
            {
                if ((_grid->GetCenterX() + menu->_title.length()/2 + 1) < (_grid->GetSizeX()))
                {
                    _grid->PrintWordOnCenter(painter, menu->_title, menu->_line, _grid->_defaultgridcolor, Qt::red);
                    (_grid->GetSymbolAt(_grid->GetCenterX() + menu->_title.length()/2 + 1, menu->_line))->symbol = QChar(0x2190);
                    (_grid->GetSymbolAt(_grid->GetCenterX() + menu->_title.length()/2 + 1, menu->_line))->GridColor = _grid->_defaultgridcolor;
                    (_grid->GetSymbolAt(_grid->GetCenterX() + menu->_title.length()/2 + 1, menu->_line))->TextColor = _grid->_defaulttextcolor;
                } else
                {
                    qDebug() << "Error:long x,y. Please set bigger window size.";
                    exit(-1);
                }
            } else
            {
                if ((_grid->GetCenterX() + menu->_title.length()/2 + 1) < (_grid->GetSizeX()))
                {
                    _grid->PrintWordOnCenter(painter, menu->_title, menu->_line, _grid->_defaultgridcolor, _grid->_defaulttextcolor);
                    (_grid->GetSymbolAt(_grid->GetCenterX() + menu->_title.length()/2 + 1, menu->_line))->symbol = ' ';
                } else
                {
                    qDebug() << "Error:long x,y. Please set bigger window size.";
                    exit(-1);
                }
            }
            menu = menu->_nextMenu;
        }
    } else
    {
        qDebug() << "Plese, build sizes.";
    }
}

void Menu::Build(int width, int height, QFont *font)
{
    _grid->ComputeSize(width, height);
    if (font == NULL)
    {
        qDebug() << "Error font == NULL.";
        exit(-1);
    }
    _grid->_font = font;
    _build = true;
}

void Menu::OnMouseOver(int x, int y)
{
    if (_build)
    {
        Menu *menu = this;
        while (menu != NULL)
        {
            QVector<int> menurect = _grid->GetCoordForWord(menu->_title);
            if (menurect.length() == 4)
            {
                if ((x > menurect.at(0)) && (x < menurect.at(2)) && (y > menurect.at(1)) && (y<menurect.at(3)))
                {
                    menu->_tabstop = true;
                    menu->OnMouseOverSound();
                } else
                {
                    menu->_played = false;
                    menu->_tabstop = false;
                }
            }
            menu = menu->Next();
        }
    } else
    {
        qDebug() << "Plese, build sizes.";
    }
}

void Menu::AddMenu(Menu *menu)
{
    if (menu != NULL)
    {
        _nextMenu = menu;
    }
}

Menu *Menu::Next()
{
    return _nextMenu;
}

void Menu::OnMouseOverSound()
{
    if (!_played)
    {
        QSound::play(":/res/audio/mouseover.wav");
    }
    _played = true;
}
