#include <QtDebug>
#include "server.h"

server::server(QObject *parent) :
    QTcpServer(parent)
{
    connect( &server_socket, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(tcpError(QAbstractSocket::SocketError)) );
    connect( &server_socket, SIGNAL(readyRead()),
             this, SLOT(tcpReady()) );
    server_socket.setSocketOption(QAbstractSocket::KeepAliveOption, true );
}

server::~server()
{
    server_socket.disconnectFromHost();
    server_socket.waitForDisconnected();
}

void server::tcpReady()
{
    QByteArray array = server_socket.read( server_socket.bytesAvailable() );
}

void server::tcpError(QAbstractSocket::SocketError error)
{
    qDebug() << "TCP error: " << server_socket.errorString();
}


bool server::start_listen(int port_no)
{
    if( !this->listen( QHostAddress::Any, port_no ) )
    {
        qDebug() << "Cannot listen to port " << port_no;
    }
    else
    {
        return true;
    }
}

void server::incomingConnection(int descriptor)
{
    if( !server_socket.setSocketDescriptor( descriptor ) )
    {
        qDebug() << "Error: socket error.";
        return;
    }
}
