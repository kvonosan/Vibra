#include "mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(int _width, int _height, bool game_mode, bool edit_mode, QWindow *parent) :
    QWindow(parent), _m_update_pending(false)
{
    create();
    setGeometry(0, 0, _width, _height);
    _m_backingStore = new QBackingStore(this);
    _edit_mode = edit_mode;
    _game_mode = game_mode;
    if (_edit_mode)
    {
        _grid = new Grid(this, NULL);
        _panel = new ButtonPanel(this, _grid);
        _end_timer_edit = false;
        _start_timer_edit = true;
    }
    if (_game_mode)
    {
        _net = new Net();
        _base = new Base(this, _net, this);
        _state = 0;
        connect(&_process, SIGNAL(finished(int)), SLOT(OnExit()));
        if (!_net->VKConnected())
        {
#ifdef Q_OS_WIN
        _process.start("fancybrowser.exe");
#else
        _process.start("./fancybrowser");
#endif
            _sec = 40000;
        } else
        {
            _state = 1;
            renderNow();
            _sec = 5000;
        }
        _end_timer_edit = false;
        _start_timer_edit = true;
        _render.setInterval(10);
        _render.start();
        this->connect(&_render, SIGNAL(timeout()), this, SLOT(update()));
    }
}

void MainWindow::update()
{
    renderNow();
    _render.start();
}

MainWindow::~MainWindow()
{
    if (_game_mode)
    {
        delete _base;
        delete _net;
    }
    if (_edit_mode)
    {
        delete _grid;
        delete _panel;
    }
    delete _m_backingStore;
}


void MainWindow::OnExit()
{
    if (_game_mode)
    {
        if (_net->VKConnected())
        {
            _state = 1;
            renderNow();
        } else
        {
#ifdef Q_OS_WIN
            _process.start("fancybrowser.exe");
#else
            _process.start("./fancybrowser");
#endif
        }
    }
}

bool MainWindow::event(QEvent *event)
{
    if (event->type() == QEvent::UpdateRequest)
    {
        _m_update_pending = false;
        renderNow();
        return true;
    }
    return QWindow::event(event);
}

void MainWindow::renderNow()
{
    if (!isExposed())
        return;

    QRect rect(0, 0, width(), height());
    _m_backingStore->beginPaint(rect);

    QPaintDevice *device = _m_backingStore->paintDevice();
    QPainter painter(device);

    painter.setRenderHint(QPainter::Antialiasing);
    painter.fillRect(0, 0, width(), height(), Qt::black);
    render(&painter);

    _m_backingStore->endPaint();
    _m_backingStore->flush(rect);
}

void MainWindow::render(QPainter *painter)
{
    if (painter != NULL)
    {
        if (_game_mode)
        {
            if (_start_timer_edit)
            {
                _timer_edit.start(_sec, this);
                _start_timer_edit = false;
            }
            switch(_state)
            {
            case 0:
            {
                QColor color;
                color.setNamedColor("#00A2E8");
                painter->fillRect(QRect(0,0,width(),height()), color);
                painter->setPen(Qt::black);
                QFont font = QFont("Arial Black", 64);
                font.setUnderline(true);
                painter->setFont(font);
                painter->drawText(QRect(0, 300, width(), height()), Qt::AlignCenter, QStringLiteral("Yotanet 768d"));
            } break;
            case 1:
            {
                _base->Paint(painter);
                if (!_net->_connected)
                {
                    _net->NetConnect(_base);
                }
                if (_end_timer_edit)
                {
                    if (!_net->_authorized)
                    {
                        QMessageBox* pmbx = new QMessageBox("Соединение с сервером",
                                            "<b>Соединение не установлено!</b>"
                                            " Возможно вы долго вводили пароль. Перезапустите игру!",
                                            QMessageBox::Information,
                                            QMessageBox::NoButton,
                                            QMessageBox::Ok,
                                            QMessageBox::NoButton);
                        pmbx->exec();
                        delete pmbx;
                        exit(-1);
                    }
                }
            } break;
            }
        }
        else if (_edit_mode)
        {
            _panel->Paint(painter);
            if (_start_timer_edit)
            {
                _timer_edit.start(10000, this);
                _start_timer_edit = false;
            }
            if (!_end_timer_edit)
            {
                painter->setPen(QPen(Qt::white));
                painter->drawText(QRectF(0, 250, width(), height()), Qt::AlignCenter, QStringLiteral("Press F1 for show/hide paint panel."));
            }
        }
    }
}

void MainWindow::timerEvent(QTimerEvent *event)
{
    if (_edit_mode||_game_mode)
    {
        if (event->timerId() == _timer_edit.timerId())
        {
            _end_timer_edit = true;
            renderNow();
        }
        QWindow::timerEvent(event);
    }
}

void MainWindow::exposeEvent(QExposeEvent *)
{
    if (isExposed())
    {
        renderNow();
    }
}

void MainWindow::resizeEvent(QResizeEvent *resizeEvent)
{
    if (_edit_mode)
    {
        _panel->SetBoundaries(width(), height());
    }
    _m_backingStore->resize(resizeEvent->size());
    if (isExposed())
    {
        renderNow();
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (_edit_mode)
    {
        if (event->buttons() == Qt::LeftButton)
        {
            _panel->SetMousePressed(true, event->x(), event->y());
        } else
        {
            _panel->SetMousePressed(false, event->x(), event->y());
        }
        renderNow();
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (_game_mode)
    {
        switch(_state)
        {
        case 1:
        {
            _base->KeyPress(event->key());
            renderNow();
        } break;
        }
    }
    else if (_edit_mode)
    {
        _panel->KeyPress(event);
        renderNow();
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (_game_mode)
    {
        switch(_state)
        {
        case 1:
        {
            _base->Click(event->x(), event->y());
            renderNow();
        } break;
        }
    }
    else if (_edit_mode)
    {
        _panel->Click(event->x(), event->y());
    }
}
