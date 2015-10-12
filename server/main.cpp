#include "net.h"
#include "loader.h"
#include "myserver.h"
#include <QCoreApplication>
#include <QSettings>

//copy c:\MySQL\lib\opt\libmysql.dll to build path
//LD_LIBRARY_PATH=/usr/lib64

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "Russian");
    QCoreApplication a(argc, argv);
    //Net *net = new Net("5028316", "bpPr0QAD5gytsbnbGpYK");

    Loader *loader = new Loader();
    loader->DatabaseConnect();

    MyServer *server = new MyServer(loader);
    server->startServer();

    int result = a.exec();

    //delete net;
    delete loader;
    delete server;

    return result;
}
