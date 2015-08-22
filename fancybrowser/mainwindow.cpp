#include <QtWidgets>
#include <QtNetwork>
#include <QtWebKitWidgets>
#include "mainwindow.h"

//! [1]

MainWindow::MainWindow(const QUrl& url)
{
    progress = 0;

//! [1]

    QNetworkProxyFactory::setUseSystemConfiguration(true);

//! [2]
    view = new QWebView(this);
    view->load(url);
    connect(view, SIGNAL(titleChanged(QString)), SLOT(adjustTitle()));
    connect(view, SIGNAL(loadProgress(int)), SLOT(setProgress(int)));
    connect(view, SIGNAL(loadFinished(bool)), SLOT(finishLoading(bool)));

//! [2]

    setCentralWidget(view);
    setUnifiedTitleAndToolBarOnMac(true);
}


//! [5]
void MainWindow::adjustTitle()
{
    if (progress <= 0 || progress >= 100)
        setWindowTitle(view->title());
    else
        setWindowTitle(QString("%1 (%2%)").arg(view->title()).arg(progress));
}

void MainWindow::setProgress(int p)
{
    progress = p;
    adjustTitle();
}
//! [5]

//! [6]
void MainWindow::finishLoading(bool)
{
    progress = 100;
    adjustTitle();
    QString url = view->url().toString();
    if (url.startsWith("https://oauth.vk.com/blank.html"))
    {
        QStringList params = url.split('#');
        QString access_token = params.at(1);
        QStringList access_token_param = access_token.split('&');
        QString token = access_token_param.at(0);

        QString filename = "token.txt";
        QFile::remove(filename);
        QFile file( filename );
        if ( file.open(QIODevice::ReadWrite) )
        {
            QTextStream stream( &file );
            stream << token << endl;
        }
        setWindowTitle("Для продолжения закройте окно!");
    }
}
//! [6]
