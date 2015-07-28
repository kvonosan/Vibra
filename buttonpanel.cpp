#include "buttonpanel.h"
#include <QFontDialog>
#include <QColorDialog>
#include <QProcess>
#include <QFileDialog>
#include <QtXml>

ButtonPanel::ButtonPanel(QWindow *parent, Grid *grid)
{
    _font.setPixelSize(30);
    _brush_font.setPixelSize(32);
    _one = QRect(10, 10, 50, 30);
    _two = QRect(70, 10, 50, 30);
    _three = QRect(130, 10, 50, 30);
    _four = QRect(190, 10, 50, 30);
    _five = QRect(250, 10, 80, 30);
    _six = QRect(340, 10, 150, 30);
    _seven = QRect(500, 10, 150, 30);
    _eight = QRect(660, 10, 90, 30);
    _nine = QRect(760, 10, 80, 30);
    _open = QRect(10, 70, 80, 30);
    _save = QRect(100, 70, 80, 30);
    _anim_prev = QRect(190, 70, 80, 30);
    _anim = QRect(280, 70, 200, 30);
    _anim_next = QRect(490, 70, 80, 30);
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
        path.addRoundedRect(_one, 10, 10);
        path.addRoundedRect(_two, 10, 10);
        path.addRoundedRect(_three, 10, 10);
        path.addRoundedRect(_four, 10, 10);
        path.addRoundedRect(_five, 10, 10);
        path.addRoundedRect(_six, 10, 10);
        path.addRoundedRect(_seven, 10, 10);
        path.addRoundedRect(_eight, 10, 10);
        path.addRoundedRect(_nine, 10, 10);
        path.addRoundedRect(_open, 10, 10);
        path.addRoundedRect(_save, 10, 10);
        path.addRoundedRect(_anim_prev, 10, 10);
        path.addRoundedRect(_anim, 10, 10);
        path.addRoundedRect(_anim_next, 10, 10);
        QPen pen(Qt::red, 4);
        painter->setPen(pen);
        painter->fillPath(path, Qt::green);
        painter->drawPath(path);
        painter->setPen(QPen(Qt::black));
        painter->setFont(_font);
        painter->drawPixmap(_one, QPixmap(":/res/icons/standart.png"));//brush
        painter->drawPixmap(_two, QPixmap(":/res/icons/pencil.png"));//brush
        painter->drawPixmap(_three, QPixmap(":/res/icons/rubber.png"));//brush
        painter->drawPixmap(_four, QPixmap(":/res/icons/fill.png"));//brush
        painter->drawText(_five, Qt::AlignCenter, QStringLiteral("Font"));//font
        painter->drawText(_six, Qt::AlignCenter, QStringLiteral("Text Color"));//text color
        painter->drawText(_seven, Qt::AlignCenter, QStringLiteral("Grid Color"));//grid color
        painter->drawText(_eight, Qt::AlignCenter, QStringLiteral("Letter"));//letter
        painter->drawText(_nine, Qt::AlignCenter, QStringLiteral("Quit"));//letter
        painter->drawText(_open, Qt::AlignCenter, QStringLiteral("Open"));//open file
        painter->drawText(_save, Qt::AlignCenter, QStringLiteral("Save"));//save file
        painter->drawText(_anim_prev, Qt::AlignCenter, QStringLiteral("Prev"));//animate previous
        painter->drawText(_anim, Qt::AlignCenter, _filename);//animate filename
        painter->drawText(_anim_next, Qt::AlignCenter, QStringLiteral("Next"));//animate next
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
        if (_one.contains(x, y))
        {
            _parent->setCursor(QCursor(QPixmap(":/res/icons/standart.png")));
            _cursor = 1;
        }
        if (_two.contains(x, y))
        {
            _parent->setCursor(QCursor(QPixmap(":/res/icons/pencil.png")));
            _cursor = 2;
        }
        if (_three.contains(x, y))
        {
            _parent->setCursor(QCursor(QPixmap(":/res/icons/rubber.png")));
            _cursor = 3;
        }
        if (_four.contains(x, y))
        {
            _parent->setCursor(QCursor(QPixmap(":/res/icons/fill.png")));
            _cursor = 4;
        }

        if (_five.contains(x, y))
        {
            bool bOk;
            QFont fnt = QFontDialog::getFont(&bOk, _brush_font);
            if (bOk)
            {
                _brush_font = fnt;
                _fntmetrics = new QFontMetrics(fnt);
                if (_fntmetrics->height() < 28)
                {
                    _brush_font.setPixelSize(28);
                } else
                {
                    if (_fntmetrics->height() > 87)
                    {
                        _brush_font.setPixelSize(87);
                    } else
                    {
                        _brush_font.setPixelSize(_fntmetrics->height());
                    }
                }
                delete _fntmetrics;
                _grid->_font = &_brush_font;
                _firstpaint = true;
            }
        }
        if (_six.contains(x, y))
        {
            _textcolor = QColorDialog::getColor(_textcolor);
            _firstpaint = true;
        }
        if (_seven.contains(x, y))
        {
            _gridcolor = QColorDialog::getColor(_gridcolor);
            _firstpaint = true;
        }
        if (_eight.contains(x, y))
        {
#ifdef Q_OS_WIN
            _process->start("charactermap.exe");
#else
            _process->start("./charactermap");
#endif
        }
        if (_nine.contains(x, y))
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
                QDataStream stream(&file);
                for (int i=0; i<_grid->GetSizeY();i++)
                    for (int j=0;j<_grid->GetCenterX();j++)
                    {
                        stream >> _grid->GetSymbolAt(i,j)->symbol;
                    }
                file.close();
            }
            /*QFile file1(_filename + "s");
            if (file1.open(QIODevice::ReadWrite))
            {
                QXmlStreamReader xmlReader(file1.readAll());
                while(!xmlReader.atEnd())
                {
                    if(xmlReader.isStartElement())
                    {
                        if (xmlReader.name() == "grid")
                        {
                            foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                            {
                                if (attr.name().toString() == QLatin1String("gridcolor"))
                                {
                                    QString attribute_value = attr.value().toString();
                                    _gridcolor = QColor(attribute_value);
                                }
                                if (attr.name().toString() == QLatin1String("textcolor"))
                                {
                                    QString attribute_value = attr.value().toString();
                                    _textcolor = QColor(attribute_value);
                                }
                            }
                        }
                        if (xmlReader.name() == "font")
                        {
                            _brush_font.fromString(xmlReader.text().toString());
                            _grid->_font = &_brush_font;
                        }
                    }
                    xmlReader.readNext();
                }
                file1.close();
            }*/
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
                QDataStream stream(&file);
                for (int i=0;i<_grid->GetSizeY();i++)
                    for (int j=0;j<_grid->GetCenterX();j++)
                    {
                        stream << _grid->GetSymbolAt(i,j)->symbol;
                    }
                file.close();
            }
            /*QFile file1(_filename + "s");
            if (file1.exists())
            {
                file1.remove();
            }
            if (file1.open(QIODevice::ReadWrite))
            {
                QXmlStreamWriter xmlWriter(&file1);
                xmlWriter.setAutoFormatting(true);
                xmlWriter.writeStartDocument();
                xmlWriter.writeStartElement("grid");
                xmlWriter.writeAttribute("gridcolor", _gridcolor.name());
                xmlWriter.writeAttribute("textcolor", _textcolor.name());
                xmlWriter.writeTextElement("font", _brush_font.toString());
                xmlWriter.writeEndElement();
                xmlWriter.writeEndDocument();
                file1.close();
            }*/
        }
        if (_anim_prev.contains(x,y))
        {}
        if (_anim.contains(x,y))
        {}
        if (_anim_next.contains(x,y))
        {}
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
    if (event->key() == Qt::Key_F || event->key() == 0x410 || event->key() == 0x430)
    {
        bool bOk;
        QFont fnt = QFontDialog::getFont(&bOk, _brush_font);
        if (bOk)
        {
            _brush_font = fnt;
            _fntmetrics = new QFontMetrics(fnt);
            if (_fntmetrics->height() < 28)
            {
                _brush_font.setPixelSize(28);
            } else
            {
                if (_fntmetrics->height() > 87)
                {
                    _brush_font.setPixelSize(87);
                } else
                {
                    _brush_font.setPixelSize(_fntmetrics->height());
                }
            }
            delete _fntmetrics;
            _grid->_font = &_brush_font;
            _firstpaint = true;
        }
    }
    if (event->key() == Qt::Key_T || event->key() == 0x415 || event->key() == 0x435)
    {
        _textcolor = QColorDialog::getColor(_textcolor);
        _firstpaint = true;
    }
    if (event->key() == Qt::Key_G || event->key() == 0x41F || event->key() == 0x43F)
    {
        _gridcolor = QColorDialog::getColor(_gridcolor);
        _firstpaint = true;
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
