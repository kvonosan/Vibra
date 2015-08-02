#include "buttonpanel.h"
#include <QProcess>
#include <QFileDialog>

ButtonPanel::ButtonPanel(QWindow *parent, Grid *grid)
{
    _font.setPixelSize(30);
    _arrow = QRect(10, 10, 50, 30);
    _pencil = QRect(70, 10, 50, 30);
    _rubber = QRect(130, 10, 50, 30);
    _fill = QRect(190, 10, 50, 30);
    _letter = QRect(250, 10, 90, 30);
    _quit = QRect(350, 10, 80, 30);
    _open = QRect(10, 70, 80, 30);
    _save = QRect(100, 70, 80, 30);
    _gridcolor = Qt::black;
    _textcolor = Qt::white;
    if (grid == NULL)
    {
        qDebug() << "Error grid == NULL.";
        exit(-1);
    }
    _grid = grid;
    _width = -1;
    _height = -1;
    _panelside = false;
    if (parent == NULL)
    {
        qDebug() << "Error. parent == NULL.";
        exit(-1);
    }
    _parent = parent;
    _firstpaint = true;
    _cursor = 1;
    _process = new QProcess();
    _filename = QStringLiteral("file001.ani");
}

ButtonPanel::~ButtonPanel()
{
    delete _process;
}

void ButtonPanel::Paint(QPainter *painter)
{
    if (_width == -1 || _height == -1)
    {
        qDebug() << "Please, set boundaries.";
        exit(-1);
    }
    if (painter == NULL)
    {
        qDebug() << "Error. Painter == NULL.";
        exit(-1);
    }
    _painter = painter;
    QString filename="char.txt";
    QFile file(filename);
    if (file.open(QIODevice::ReadOnly))
    {
        QTextStream stream(&file);
        stream >> _paintsymbol;
    }
    file.close();
    if (_panelside)
    {
        QPainterPath path;
        path.addRoundedRect(_arrow, 10, 10);
        path.addRoundedRect(_pencil, 10, 10);
        path.addRoundedRect(_rubber, 10, 10);
        path.addRoundedRect(_fill, 10, 10);
        path.addRoundedRect(_letter, 10, 10);
        path.addRoundedRect(_quit, 10, 10);
        path.addRoundedRect(_open, 10, 10);
        path.addRoundedRect(_save, 10, 10);
        QPen pen(Qt::red, 4);
        painter->setPen(pen);
        painter->fillPath(path, Qt::green);
        painter->drawPath(path);
        painter->setPen(QPen(Qt::black));
        painter->setFont(_font);
        painter->drawPixmap(_arrow, QPixmap(":/res/icons/standart.png"));//brush
        painter->drawPixmap(_pencil, QPixmap(":/res/icons/pencil.png"));//brush
        painter->drawPixmap(_rubber, QPixmap(":/res/icons/rubber.png"));//brush
        painter->drawPixmap(_fill, QPixmap(":/res/icons/fill.png"));//brush
        painter->drawText(_letter, Qt::AlignCenter, QStringLiteral("Letter"));//letter
        painter->drawText(_quit, Qt::AlignCenter, QStringLiteral("Quit"));//quit
        painter->drawText(_open, Qt::AlignCenter, QStringLiteral("Open"));//open file
        painter->drawText(_save, Qt::AlignCenter, QStringLiteral("Save"));//save file
    } else
    {
        QVector <QVector<Symbol> > mass;
        if (_grid->_computed)
        {
            mass.resize(_grid->GetSizeX());
            for(int i=0; i < _grid->GetSizeX(); i++)
            {
                mass[i].resize(_grid->GetSizeY());
                for(int j=0; j < _grid->GetSizeY(); j++)
                {
                    mass[i][j].GridColor = _grid->GetSymbolAt(i,j)->GridColor;
                    mass[i][j].TextColor = _grid->GetSymbolAt(i,j)->TextColor;
                    mass[i][j].symbol = _grid->GetSymbolAt(i,j)->symbol;
                }
            }
        }
        _grid->ComputeSize(_width, _height);
        _grid->SetGridColor(painter, _gridcolor);
        _grid->SetTextColor(painter, _textcolor);
        if (!_firstpaint)
        {
            for(int i=0; i < _grid->GetSizeX(); i++)
                for(int j=0; j < _grid->GetSizeY(); j++)
                {
                    _grid->GetSymbolAt(i,j)->GridColor = mass[i][j].GridColor;
                    _grid->GetSymbolAt(i,j)->TextColor = mass[i][j].TextColor;
                    _grid->GetSymbolAt(i,j)->symbol = mass[i][j].symbol;
                }
        }
        _firstpaint = false;
        if (_mousepressed && _mousex >= 0 && _mousey >= 0 && _cursor == 2)
        {
            (_grid->GetSymbolAtWH(_mousex, _mousey))->symbol = _paintsymbol;
            (_grid->GetSymbolAtWH(_mousex, _mousey))->GridColor = _gridcolor;
            (_grid->GetSymbolAtWH(_mousex, _mousey))->TextColor = _textcolor;
        }
        if (_mousepressed && _mousex >= 0 && _mousey >= 0 && _cursor == 4)
        {
            _grid->ComputeSize(_width, _height);
            _grid->SetGridColor(painter, _gridcolor);
            _grid->SetTextColor(painter, _textcolor);
        }
        if (_mousepressed && _mousex >= 0 && _mousey >= 0 && _cursor == 3)
        {
            (_grid->GetSymbolAtWH(_mousex, _mousey))->symbol = ' ';
            (_grid->GetSymbolAtWH(_mousex, _mousey))->GridColor = _gridcolor;
            (_grid->GetSymbolAtWH(_mousex, _mousey))->TextColor = _textcolor;
        }
        _grid->Paint(painter);
    }
}

void ButtonPanel::Click(int x, int y)
{
    if (_width == -1 || _height == -1)
    {
        qDebug() << "Please, set boundaries.";
        exit(-1);
    }
    if (_panelside)
    {
        if (_arrow.contains(x, y))
        {
            _parent->setCursor(QCursor(QPixmap(":/res/icons/standart.png")));
            _cursor = 1;
        }
        if (_pencil.contains(x, y))
        {
            _parent->setCursor(QCursor(QPixmap(":/res/icons/pencil.png")));
            _cursor = 2;
        }
        if (_rubber.contains(x, y))
        {
            _parent->setCursor(QCursor(QPixmap(":/res/icons/rubber.png")));
            _cursor = 3;
        }
        if (_fill.contains(x, y))
        {
            _parent->setCursor(QCursor(QPixmap(":/res/icons/fill.png")));
            _cursor = 4;
        }
        if (_letter.contains(x, y))
        {
#ifdef Q_OS_WIN
            _process->start("charactermap.exe");
#else
            _process->start("./charactermap");
#endif
        }
        if (_quit.contains(x, y))
        {
            exit(0);
        }
        if (_open.contains(x,y))
        {
            _filename = QFileDialog::getOpenFileName(0, "Open Animation File", "./", "Animate Files (*.ani)");
            QFileInfo fileInfo(_filename);
            QString filename(fileInfo.fileName());
            _filename = filename;
            QFile file(_filename);
            if (file.open(QIODevice::ReadWrite))
            {
                QTextStream stream(&file);
                for (int i=0; i<_grid->GetSizeX();i++)
                    for (int j=0;j<_grid->GetSizeY();j++)
                    {
                        stream >> (_grid->GetSymbolAt(i,j)->symbol);
                    }
                file.close();
            }
        }
        if (_save.contains(x,y))
        {
            _filename = QFileDialog::getSaveFileName(0, "Save Animation File", "./" + _filename, "Animate Files (*.ani)");
            QFileInfo fileInfo(_filename);
            QString filename(fileInfo.fileName());
            _filename = filename;
            QFile file(_filename);
            if (file.exists())
            {
                file.remove();
            }
            if (file.open(QIODevice::ReadWrite))
            {
                QTextStream stream(&file);
                for (int i=0;i<_grid->GetSizeX();i++)
                    for (int j=0;j<_grid->GetSizeY();j++)
                    {
                        stream << (_grid->GetSymbolAt(i,j)->symbol);
                    }
                file.close();
            }
        }
    } else
    {
        //click on grid!!!
    }
}

void ButtonPanel::KeyPress(QKeyEvent *event)
{
    if (_width == -1 || _height == -1)
    {
        qDebug() << "Please, set boundaries.";
        exit(-1);
    }
    if (event->key() == Qt::Key_F1)
    {
        _panelside = !_panelside;
    }
    if (event->key() == Qt::Key_L || event->key() == 0x414 || event->key() == 0x434)
    {
        QProcess *process = new QProcess();
#ifdef Q_OS_WIN
        process->start("charactermap.exe");
#else
        process->start("./charactermap");
#endif
    }
    if (event->key() == Qt::Key_Q || event->key() == 0x419 || event->key() == 0x439)
    {
        exit(0);
    }
}

void ButtonPanel::SetBoundaries(int width, int height)
{
    _width = width;
    _height = height;
}

void ButtonPanel::SetMousePressed(bool pressed, int x, int y)
{
    _mousepressed = pressed;
    _mousex = x;
    _mousey = y;
}
