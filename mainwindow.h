#ifndef WINDOW_H
#define WINDOW_H

#include <QtGui>
#include "net.h"
#include "base.h"
#include <QTimer>
#include "buttonpanel.h"

class Net;

class MainWindow : public QWindow
{
    Q_OBJECT
public:
    ~MainWindow();
    void renderNow();
    bool VKConnected();
    bool event(QEvent *event);
    void render(QPainter *painter);
    void exposeEvent(QExposeEvent *);
    void resizeEvent(QResizeEvent *resizeEvent);
    explicit MainWindow(int _width, int _height, bool game_mode, bool edit_mode, QWindow *parent = 0);
    bool _edit_mode, _game_mode;
private slots:
    void OnExit();
    void update();
private:
    void keyPressEvent(QKeyEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void timerEvent(QTimerEvent *event) Q_DECL_OVERRIDE;
    Net *_net;
    int _state, _sec;
    Base *_base;
    Grid *_grid;
    QTimer _render;
    QProcess _process;
    int _width, _height;
    ButtonPanel *_panel;
    QBasicTimer _timer_edit;
    QBackingStore *_m_backingStore;
    bool _start_timer_edit, _end_timer_edit, _m_update_pending, _started;
};

#endif // WINDOW_H
