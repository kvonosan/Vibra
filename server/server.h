#ifndef SERVER
#define SERVER

#include <QtNetwork>

class server : public QTcpServer
{
    Q_OBJECT
public:
    explicit server(QObject *parent = 0);
    ~server();
    QTcpSocket server_socket;
public slots:
      void tcpReady();
      void tcpError( QAbstractSocket::SocketError error );
      bool start_listen(int port_no);
protected:
    void incomingConnection( int descriptor );
};

#endif // SERVER
