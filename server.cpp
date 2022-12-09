#include <http_tcpserver.h>

int main()
{
    using namespace http;

    TcpServer server = TcpServer("127.0.0.1", 3001);
    // server = TcpServer("127.0.0.1", 6969);
    server.startListen();
    return 0;
}
