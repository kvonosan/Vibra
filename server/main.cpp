#include <QCoreApplication>
#include <boost/asio.hpp>
#include "player.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Player player;

    return a.exec();
}
