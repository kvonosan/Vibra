#ifndef WINDOW_H
#define WINDOW_H

#include <QtGui>
#include <QtWebKitWidgets>
#include "buttonpanel.h"
#include "base.h"
#include "net.h"

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
    explicit MainWindow(int _width, int _height, bool game_mode, bool edit_mode, QWindow *parent = 0);
    void resizeEvent(QResizeEvent *resizeEvent);
    bool _edit_mode, _game_mode;
private slots:
    void OnExit();
private:
    void keyPressEvent(QKeyEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void timerEvent(QTimerEvent *event) Q_DECL_OVERRIDE;
    Base *_base;
    Grid *_grid;
    int _width, _height;
    ButtonPanel *_panel;
    QBackingStore *_m_backingStore;
    QBasicTimer _timer_edit;
    bool _start_timer_edit, _end_timer_edit, _m_update_pending, _started;
    int _state;
    QProcess _process;
    Net *_net;
};

#endif // WINDOW_H
