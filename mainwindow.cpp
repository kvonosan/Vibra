#include "mainwindow.h"

MainWindow::MainWindow(int _width, int _height, QWindow *parent) :
    QWindow(parent), _m_update_pending(false)
{
    create();
    _font = new QFont();
    _font->setPixelSize(32);
    _edit_mode = false;
    _end_timer = false;
    _show_help = false;
    _start_timer = true;
    _end_timer_edit = false;
    _start_timer_edit = true;
    _defaultgridcolor = Qt::gray;
    _defaulttextcolor = Qt::black;
    _m_backingStore = new QBackingStore(this);
    setGeometry(0, 0, _width, _height);
    _grid = new Grid(_defaultgridcolor, _defaulttextcolor, _font);
    _panel = new ButtonPanel(this, _grid);
    _mainMenu = new Menu(_grid, "Play");
    _mainMenu->AddMenu(new Menu(_grid, "Redact"));
    _mainMenu->Next()->AddMenu(new Menu(_grid, "Exit"));
    _mainMenu->Build(width(), height(), _font);
    _mainMenu->_line = (_grid->GetSizeY()/2);
    (_mainMenu->Next())->_line = (_grid->GetSizeY()/2 + 1);
    (_mainMenu->Next()->Next())->_line = (_grid->GetSizeY()/2 + 2);
}

MainWindow::~MainWindow()
{
    delete _font;
    delete _m_backingStore;
    delete _grid;
    delete _panel;
    delete _mainMenu;
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
    painter.fillRect(0, 0, width(), height(), _defaultgridcolor);
    render(&painter);

    _m_backingStore->endPaint();
    _m_backingStore->flush(rect);
}

void MainWindow::render(QPainter *painter)
{
    if (painter != NULL)
    {
        if (!_edit_mode)
        {
            _mainMenu->Paint(painter);
            if (_start_timer)
            {
                _timer.start(10000, this);
                _start_timer = false;
            }
            if (!_end_timer)
            {
                painter->setPen(QPen(Qt::black));
                painter->drawText(QRectF(0, 250, width(), height()), Qt::AlignCenter, QStringLiteral("Press F1 for help."));
            }
            if (_show_help)
            {
                painter->setPen(QPen(Qt::black));
#ifdef Q_OS_WIN
                painter->drawText(QRectF(0, height()/2 -1*_font->pixelSize(), width(), height()), Qt::AlignLeft, QStringLiteral("                        Start playing - "));
                painter->drawText(QRectF(0, (height()/2), width(), height()), Qt::AlignLeft, QStringLiteral("        Start games redactor - "));
                painter->drawText(QRectF(0, (height()/2 + 1*_font->pixelSize()), width(), height()), Qt::AlignLeft, QStringLiteral("                    Exit from game - "));
#else
                painter->drawText(QRectF(0, height()/2, width(), height()), Qt::AlignLeft, QStringLiteral("                        Start playing - "));
                painter->drawText(QRectF(0, (height()/2 + 1*_font->pixelSize()), width(), height()), Qt::AlignLeft, QStringLiteral("        Start games redactor - "));
                painter->drawText(QRectF(0, (height()/2 + 2*_font->pixelSize()), width(), height()), Qt::AlignLeft, QStringLiteral("                    Exit from game - "));
#endif
            }
        } else
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
    if (event->timerId() == _timer.timerId())
    {
        _end_timer = true;
        renderNow();
    } else
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
    _panel->SetBoundaries(width(), height());
    _m_backingStore->resize(resizeEvent->size());
    if (isExposed())
    {
        renderNow();
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (!_edit_mode)
    {
        _mainMenu->OnMouseOver(event->x(), event->y());
        renderNow();
    } else
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
    if (!_edit_mode)
    {
        switch(event->key())
        {
        case Qt::Key_Escape:
        {
            this->close();
        } break;
        case Qt::Key_F1:
        {
            _show_help = !_show_help;
            renderNow();
        } break;
        }
    } else
    {
        _panel->KeyPress(event);
        renderNow();
    }
}

bool MainWindow::MouseOver(Menu *menu, int x, int y)
{
    if (menu != NULL)
    {
        if (!_edit_mode)
        {
            QVector<int> menurect = _grid->GetCoordForWord(menu->_title);
            if (menurect.length() == 4)
            {
                if ((x > menurect.at(0)) && (x < menurect.at(2)) && (y > menurect.at(1)) && (y<menurect.at(3)))
                {
                    return true;
                } else
                {
                    return false;
                }
            }
        } else
        {}
    }
    return false;
}

Menu *MainWindow::GetMenu(QString title)
{
    Menu *menu = _mainMenu;
    while(menu != NULL)
    {
        if (menu->_title == title)
            return menu;
        menu = menu->Next();
    }
    return NULL;
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (!_edit_mode)
    {
        Menu *menu = GetMenu("Exit");
        if (menu != NULL)
        {
            if (MouseOver(menu, event->x(), event->y()))
            {
                this->close();
            }
        }
        menu = NULL;
        menu = GetMenu("Redact");
        if (menu != NULL)
        {
            if (MouseOver(menu, event->x(), event->y()))
            {
                _edit_mode = true;
                renderNow();
            }
        }
    } else
    {
        _panel->Click(event->x(), event->y());
    }
}
