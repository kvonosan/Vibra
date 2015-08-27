#include <QDebug>
#include <QGLFormat>
#include <QApplication>
#include <QDesktopWidget>
#include "mainwindow.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    QCoreApplication::setApplicationName("Yotanet 768d");
    QCoreApplication::setApplicationVersion("1.0");

    QCommandLineParser parser;
    parser.setApplicationDescription("Игра йотанет - создай свою человеческую расу!");
    parser.addHelpOption();
    parser.addVersionOption();
    QCommandLineOption redactOption(QStringList() << "r" << "redact",
            QCoreApplication::translate("main", "Режим рисования."));
    parser.addOption(redactOption);
    parser.process(app);

    MainWindow *window;
    QRect rec = QApplication::desktop()->screenGeometry();
    int height = rec.height();
    int width = rec.width();

    if (parser.isSet(redactOption))
    {
        window = new MainWindow(width, height, false, true);
    } else
    {
        window = new MainWindow(width, height, true, false);
    }
    window->showFullScreen();

#ifdef QT_DEBUG
    QGLFormat glFormat;
    qDebug() << "openGL version" << glFormat.majorVersion() << "." << glFormat.minorVersion();

    if (!(QGLFormat::openGLVersionFlags() & QGLFormat::OpenGL_Version_4_3))
    {
       qDebug() << "Your platform does not support OpenGL 4.3";
    }

    if (!(QGLFormat::openGLVersionFlags() & QGLFormat::OpenGL_Version_4_2))
    {
       qDebug() << "Your platform does not support OpenGL 4.2";
    }

    if (!(QGLFormat::openGLVersionFlags() & QGLFormat::OpenGL_Version_4_1))
    {
       qDebug() << "Your platform does not support OpenGL 4.1";
    }

    if (!(QGLFormat::openGLVersionFlags() & QGLFormat::OpenGL_Version_4_0))
    {
       qDebug() << "Your platform does not support OpenGL 4.0";
    }

    if (!(QGLFormat::openGLVersionFlags() & QGLFormat::OpenGL_Version_3_3))
    {
       qDebug() << "Your platform does not support OpenGL 3.3";
    }

    if (!(QGLFormat::openGLVersionFlags() & QGLFormat::OpenGL_Version_3_2))
    {
       qDebug() << "Your platform does not support OpenGL 3.2";
    }

    if (!(QGLFormat::openGLVersionFlags() & QGLFormat::OpenGL_Version_3_1))
    {
       qDebug() << "Your platform does not support OpenGL 3.1";
    }

    if (!(QGLFormat::openGLVersionFlags() & QGLFormat::OpenGL_Version_3_0))
    {
       qDebug() << "Your platform does not support OpenGL 3.0";
    }

    if (!(QGLFormat::openGLVersionFlags() & QGLFormat::OpenGL_Version_2_1))
    {
       qDebug() << "Your platform does not support OpenGL 2.1";
    }

    if (!(QGLFormat::openGLVersionFlags() & QGLFormat::OpenGL_Version_2_0))
    {
       qDebug() << "Your platform does not support OpenGL 2.0";
    }
#endif

    int result = app.exec();
    delete window;
    return result;
}
