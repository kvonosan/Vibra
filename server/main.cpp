#include <QCoreApplication>
#include "player.h"
#include "net.h"
#include "loader.h"
#include "myserver.h"

//copy c:\MySQL\lib\opt\libmysql.dll to build path
//LD_LIBRARY_PATH=/usr/lib64

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Net *net = new Net("5028316", "bpPr0QAD5gytsbnbGpYK");

    Loader loader;
    loader.DatabaseConnect();

    MyServer *server = new MyServer();
    server->startServer();

    return a.exec();
}
