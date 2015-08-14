#include <QCoreApplication>
#include <boost/asio.hpp>
#include "player.h"
#include "vk_auth.h"
#include "loader.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //Player player;

    //VkAuth *auth = new VkAuth("5028316", "bpPr0QAD5gytsbnbGpYK");

    Loader loader;
    loader.DatabaseConnect();

    return a.exec();
}
