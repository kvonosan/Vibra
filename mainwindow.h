#ifndef WINDOW_H
#define WINDOW_H

#include <QtGui>
#include "menu.h"
#include "buttonpanel.h"
#include "base.h"

class MainWindow : public QWindow
{
    Q_OBJECT
public:
    ~MainWindow();
    void renderNow();
    bool event(QEvent *event);
    Menu *GetMenu(QString title);
    void render(QPainter *painter);
    void exposeEvent(QExposeEvent *);
    bool MouseOver(Menu *menu, int x, int y);
    explicit MainWindow(int _width, int _height, QWindow *parent = 0);
    void resizeEvent(QResizeEvent *resizeEvent);
private:
    void keyPressEvent(QKeyEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void timerEvent(QTimerEvent *event) Q_DECL_OVERRIDE;
    Base *_base;
    Grid *_grid;
    QFont *_font;
    Menu *_mainMenu;
    int _width, _height;
    ButtonPanel *_panel;
    QBackingStore *_m_backingStore;
    QBasicTimer _timer, _timer_edit;
    QColor _defaultgridcolor, _defaulttextcolor;
    bool _start_timer_edit, _end_timer_edit, _game_mode;
    bool _m_update_pending, _start_timer, _end_timer, _show_help, _edit_mode;
};

#endif // WINDOW_H
