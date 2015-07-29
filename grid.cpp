#include "grid.h"
#include <QDebug>

Grid::Grid(QColor defaultgridcolor, QColor defaulttextcolor, QFont *font)
{
    if (font != NULL)
    {
        _font = font;
    } else
    {
        qDebug() << "Error font == NULL.";
        exit(-1);
    }
    _computed = false;
    _defaultgridcolor = defaultgridcolor;
    _defaulttextcolor = defaulttextcolor;
}

Grid::~Grid()
{
}

void Grid::Paint(QPainter *painter)
{
    if (!painter)
    {
        qDebug() << "Error. Painter == NULL.";
        exit(-1);
    }
    if (!_computed)
    {
        qDebug() << "Please, compute sizes.";
        exit(-1);
    }
    painter->setFont(*_font);
    painter->setRenderHint(QPainter::Antialiasing);
    painter->fillRect(QRect(0, 0, _sizeX*_font->pixelSize()+_font->pixelSize(), _sizeY*_font->pixelSize()+_font->pixelSize()), QBrush(_symbols[0][0].GridColor));
    for (int i = 0; i < _sizeX; i++)
        for(int j = 0; j < _sizeY; j++)
        {
            if (_symbols[i][j].symbol != 0)
            {
                painter->setPen(QPen(_symbols[i][j].TextColor));
                painter->drawText(QRect(i*_font->pixelSize(), j*_font->pixelSize(), i*_font->pixelSize()+_font->pixelSize(), j*_font->pixelSize()+_font->pixelSize()), Qt::AlignAbsolute, _symbols[i][j].symbol);
            }
        }
}

void Grid::ComputeSize(int SizeX, int SizeY)
{
    if (_font == NULL || SizeX == 0 || SizeY == 0)
    {
        qDebug() << "Error. _font == NULL or SizeX<0 or SizeY<0.";
        exit(-1);
    }
#ifdef QT_DEBUG
    //qDebug() << "Screen resolution " << SizeX << "x" << SizeY;
    //qDebug() << "Fontsize " << _font->pixelSize();
#endif
    _width = SizeX;
    _heigth = SizeY;
    _sizeX = SizeX / _font->pixelSize();
    _sizeY = SizeY / _font->pixelSize();
    _centrX = _sizeX / 2;
    _centrY = _sizeY / 2;
#ifdef QT_DEBUG
    //qDebug() << "Screen resolution in grid" << _sizeX << "x" << _sizeY;
    //qDebug() << "Centr in grid" << _centrX << "x" << _centrY;
#endif
    _symbols.resize(_sizeX);
    for(int i=0; i < _sizeX; i++)
    {
        _symbols[i].resize(_sizeY);
        for(int j=0; j < _sizeY; j++)
        {
            _symbols[i][j].GridColor = _defaultgridcolor;
            _symbols[i][j].TextColor = _defaulttextcolor;
            _symbols[i][j].symbol = 0;
        }
    }
    _computed = true;
}

void Grid::SetGridColor(QPainter *painter, QColor gridcolor)
{
    if (!painter)
    {
        qDebug() << "Error. Painter == NULL.";
        exit(-1);
    }
    if (!_computed)
    {
        qDebug() << "Please, compute sizes.";
        exit(-1);
    }
    for(int i=0; i < _sizeX; i++)
        for(int j=0; j < _sizeY; j++)
        {
            _symbols[i][j].GridColor = gridcolor;
        }
    Paint(painter);
}

void Grid::SetTextColor(QPainter *painter, QColor textcolor)
{
    if (!painter)
    {
        qDebug() << "Error. Painter == NULL.";
        exit(-1);
    }
    if (!_computed)
    {
        qDebug() << "Please, compute sizes.";
        exit(-1);
    }
    for(int i=0; i < _sizeX; i++)
        for(int j=0; j < _sizeY; j++)
        {
            _symbols[i][j].TextColor = textcolor;
        }
    Paint(painter);
}

Symbol* Grid::GetSymbolAt(int x, int y)
{
    if (!_computed)
    {
        qDebug() << "Please, compute sizes.";
        exit(-1);
    }
    if ((x > _sizeX) || (y > _sizeY) || x < 0 || y < 0)
    {
        qDebug() << "Error. Out of bounds.";
        exit(-1);
    }
    Symbol *at = &_symbols[x][y];
    return at;
}

Symbol* Grid::GetSymbolAtWH(int width, int heigth)
{
    int x = width / _font->pixelSize();
    int y = heigth / _font->pixelSize();
    if (x >= _sizeX || y >= _sizeY)
    {
        return GetSymbolAt(_sizeX - 1, _sizeY - 1);
    }
    return GetSymbolAt(x, y);
}

void Grid::PrintWordOnCenter(QPainter *painter, QString word, int line, QColor gridcolor, QColor textcolor)
{
    int len = word.length();
    if (!_computed)
    {
        qDebug() << "Please, compute sizes.";
        exit(-1);
    }
    if (len > _sizeX)
    {
        qDebug() << "Long word.";
        exit(-1);
    }
    if (line > _sizeY || line < 0)
    {
        qDebug() << "long or short line.";
        exit(-1);
    }
    int start = len/2;
    int ostatok = len%2, i = 0;
    while (start != 0)
    {
        _symbols[_centrX - start][line].symbol = word[i];
        _symbols[_centrX - start][line].GridColor = gridcolor;
        _symbols[_centrX - start][line].TextColor = textcolor;
        start--;
        i++;
    }
    start = len/2;
    if (ostatok)
        start++;
    int j = 0;
    while (j < start)
    {
        _symbols[_centrX + j][line].symbol = word[i];
        _symbols[_centrX + j][line].GridColor = gridcolor;
        _symbols[_centrX + j][line].TextColor = textcolor;
        j++;
        i++;
    }
    Paint(painter);
}

void Grid::PrintWordOnRight(QPainter *painter, QString word, int line, QColor gridcolor, QColor textcolor)
{
    int len = word.length();
    if (!_computed)
    {
        qDebug() << "Please, compute sizes.";
        exit(-1);
    }
    if (len > _sizeX)
    {
        qDebug() << "long word.";
    }
    if (line > _sizeY || line < 0)
    {
        qDebug() << "long or short line.";
        exit(-1);
    }
    int start = len;
    int i = 0;
    while (i < len)
    {
        _symbols[_sizeX - start][line].symbol = word[i];
        _symbols[_sizeX - start][line].GridColor = gridcolor;
        _symbols[_sizeX - start][line].TextColor = textcolor;
        start--;
        i++;
    }
    Paint(painter);
}

void Grid::PrintWordOnLeft(QPainter *painter, QString word, int line, QColor gridcolor, QColor textcolor)
{
    int len = word.length();
    if (word.length() == 0)
    {
        qDebug() << "Empty word.";
        exit(-1);
    }
    if (!_computed)
    {
        qDebug() << "Please, compute sizes.";
        exit(-1);
    }

    if (line > _sizeY || line < 0)
    {
        qDebug() << "long line.";
        exit(-1);
    }
    int start = 0;
    while (start < len)
    {
        _symbols[start][line].symbol = word[start];
        _symbols[start][line].GridColor = gridcolor;
        _symbols[start][line].TextColor = textcolor;
        start++;
    }
    Paint(painter);
}

QVector<int> Grid::GetCoordForWord(QString word)
{
    if (!_computed)
    {
        qDebug() << "Please, compute sizes.";
        exit(-1);
    }
    int len = word.length();
    if (len == 0)
    {
        qDebug() << "Error, short word.";
        exit(-1);
    }
    int k = 0, i, j;
    bool found = false;
    for (i = 0; i < _sizeX; i++)
    {
        for (j = 0; j < _sizeY; j++)
        {
            if (_symbols[i][j].symbol == word[k])
            {
                found = true;
            } else
            {
                found = false;
            }
            if (found)
            {
                int o = i;
                while (k < word.length())
                {
                    k++;
                    o++;
                    if (_symbols[o][j].symbol == word[k])
                    {
                        found = true;
                        if (k == word.length())
                            break;
                    } else
                    {
                        found = false;
                    }
                }
            } else
            {
                k = 0;
            }
            if (found)
            {
                break;
            }
        }
        if (found)
            break;
    }
    if (found)
    {
        QVector<int> coord;
        coord.append(i*_font->pixelSize());
        coord.append(j*_font->pixelSize());
        coord.append(i*_font->pixelSize()+_font->pixelSize()*word.length());
        coord.append(j*_font->pixelSize()+_font->pixelSize());
        return coord;
    } else
    {
        QVector<int> coord;
        return coord;
    }
}

QVector<int> Grid::GetCoordForWordInSymbols(QString word)
{
    if (!_computed)
    {
        qDebug() << "Please, compute sizes.";
        exit(-1);
    }
    QVector<int> coord = GetCoordForWord(word);
    QVector<int> old_coord;
    if (coord.length() == 4)
    {
        old_coord.append(coord.at(0)/_font->pixelSize());
        old_coord.append(coord.at(1)/_font->pixelSize());
        old_coord.append(coord.at(2)/_font->pixelSize());
        old_coord.append(coord.at(3)/_font->pixelSize());
    }
    return old_coord;
}
