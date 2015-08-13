#include <QCoreApplication>
#include <boost/asio.hpp>
#include "player.h"
#include "vk_auth.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //Player player;

    VkAuth *auth = new VkAuth("5028316", "bpPr0QAD5gytsbnbGpYK");

    return a.exec();
}
