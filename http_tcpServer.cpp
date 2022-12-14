#include <http_tcpServer.h>
#include <get_receipe_by_id.h>
#include <get_receipe_by_ingri.h>
#include <iostream>
#include <sstream>
#include <fstream>

namespace
{
    const int BUFFER_SIZE = 60720;
    void log(const std::string &message)
    {
        std::cout << message << std::endl;
    }

    void exitWithError(const std::string &errorMessage)
    {
        std::cout << WSAGetLastError() << std::endl;
        log("ERROR: " + errorMessage);
        exit(1);
    }
}

namespace http
{

    TcpServer::TcpServer(std::string ip_address, int port)
        : m_ip_address(ip_address), m_port(port), m_socket(), m_socketAddress_len(sizeof(m_socketAddress))
    {
        m_socketAddress.sin_family = AF_INET;
        m_socketAddress.sin_port = htons(m_port);
        m_socketAddress.sin_addr.s_addr = inet_addr(m_ip_address.c_str());
        if (startServer() != 0)
        {
            std::ostringstream ss;
            ss << "Failed to start server with PORT: " << ntohs(m_socketAddress.sin_port);
            log(ss.str());
        }
    }
    TcpServer::~TcpServer()
    {
        closeServer();
    }

    int TcpServer::startServer()
    {
        if (WSAStartup(MAKEWORD(2, 0), &m_wsaData) != 0)
        {
            exitWithError("WSAStartup failed");
        }

        m_socket = socket(AF_INET, SOCK_STREAM, 0);
        if (m_socket < 0)
        {
            exitWithError("Cannot create socket");
            return 1;
        }

        if (bind(m_socket, (sockaddr *)&m_socketAddress, m_socketAddress_len) < 0)
        {
            exitWithError("Cannot connet socket to address");
            return 1;
        }

        return 0;
    }

    void TcpServer::closeServer()
    {
        closesocket(m_socket);
        closesocket(m_new_socket);
        WSACleanup();
        exit(0);
    }

    void TcpServer::startListen()
    {

        if (listen(m_socket, 20) < 0)
        {
            exitWithError("Socket listen failed");
        }

        std::ostringstream ss;
        ss << "\n*** Listening on ADDRESS: " << inet_ntoa(m_socketAddress.sin_addr) << " PORT: " << ntohs(m_socketAddress.sin_port) << " ***\n\n";
        log(ss.str());

        int bytesReceived;

        while (true)
        {
            log("========Waiting for a new connection ========\n\n\n");
            acceptConnection(m_new_socket);

            char buffer[BUFFER_SIZE] = {0};
            bytesReceived = recv(m_new_socket, buffer, BUFFER_SIZE, 0);
            if (bytesReceived < 0)
            {
                exitWithError("Failed to receive any bytes from the client socket connection");
            }

            std::ostringstream ss;
            std::ostringstream send;
            ss << "-------- Received Request from the client --------\n\n";
            log(ss.str());
            // TODO:
            send << buffer;
            log("RESP from Client");
            log(send.str());
            std::cout << std::endl;
            sendResponse(send.str());

            closesocket(m_new_socket);
        }
    }

    void TcpServer::acceptConnection(SOCKET &new_socket)
    {

        new_socket = accept(m_socket, (sockaddr *)&m_socketAddress, &m_socketAddress_len);
        if (new_socket < 0)
        {
            std::ostringstream ss;
            ss << "Server failed to accept incoming connection from ADDRESS: " << inet_ntoa(m_socketAddress.sin_addr) << "; PORT: " << ntohs(m_socketAddress.sin_port);
            exitWithError(ss.str());
        }
    }

    // Calling the func which calls the APIs
    std::string TcpServer::buildResponse(std::string clientReq)
    {
        // std::string res = grbIngri::obj.makeReq(parse(clientReq));
        std::string res = parse(clientReq);
        std::ostringstream ss;

        ss << "HTTP/1.1 200 OK\r\n"
           << "Content-Type: application/json; charset=utf-8\r\n"
           << "Access-Control-Allow-Origin: *\r\n"
           << "content-length: " << res.size() << "\r\n\r\n"
           << res;
        std::cout << ss.str() << std::endl;

        return ss.str();
    }

    void TcpServer::sendResponse(std::string clientReq)
    {
        int bytesSent;
        long totalBytesSent = 0;
        m_serverMessage = buildResponse(clientReq);
        // m_serverMessage = "Hello from server";

        while (totalBytesSent < m_serverMessage.size())
        {
            bytesSent = send(m_new_socket, m_serverMessage.c_str(), m_serverMessage.size(), 0);
            if (bytesSent < 0)
            {
                break;
            }
            totalBytesSent += bytesSent;
        }

        if (totalBytesSent == m_serverMessage.size())
        {
            log("------ Server Response sent to client ------\n\n");
        }
        else
        {
            log("Error sending response to client.");
        }
    }

    /// @brief Parsing the req by client and making the appropriate API call and returning the result from the said call
    /// @param clientReq
    /// @return res
    std::string TcpServer::parse(std::string clientReq)
    {
        std::istringstream stream(clientReq);
        std::string line, r, type, res, t;
        int i = 0;
        std::cout << "=----------==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=";
        while (std::getline(stream, line))
        {
            i++;
            r = line;
            if (i == 20)
            {
                type = r + "\n";
            }
        }
        if (type == "ingri\r\n")
        {
            res = grbIngri::obj.makeReq(r);
        }
        if (type == "id\r\n")
        {
            std::cout << "ID wala pakda" << std::endl;
            std::cout << "ID r-> " << r << std::endl;
            res = grbId::obj.makeReq(r);
            std::cout << res << std::endl;
        }
        return res;
    }

} // namespace http
