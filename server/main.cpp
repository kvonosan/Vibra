#include <QCoreApplication>
#include <boost/asio.hpp>
#include "player.h"
#include "vk_auth.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //Player player;

    vk_auth *auth = new vk_auth("5028316", "bpPr0QAD5gytsbnbGpYK");

    return a.exec();
}
