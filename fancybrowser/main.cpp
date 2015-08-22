#include <QtWidgets>
#include "mainwindow.h"

int main(int argc, char * argv[])
{
    QApplication app(argc, argv);
    MainWindow browser(QUrl("https://oauth.vk.com/authorize?client_id=5028316&display=page&redirect_uri=https://oauth.vk.com/blank.html&scope=friends&response_type=token&v=5.37"));
    browser.show();
    return app.exec();
}
