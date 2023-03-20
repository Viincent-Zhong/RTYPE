/*
** EPITECH PROJECT, 2022
** Project R-TYPE
** File description:
** ServerTCPHandler.hpp
*/

#ifndef SERVERTCPHANDLER_HPP_
#define SERVERTCPHANDLER_HPP_

#include <asio.hpp>
#include <functional>
#include "TCPDataStructure.hpp"
#include "ServerMenu.hpp"

#define MAX_LENGTH  1024

namespace EngineNetwork {

class ServerTCPHandler : public std::enable_shared_from_this<ServerTCPHandler> {
    public:
        ServerTCPHandler(asio::ip::tcp::tcp::socket socket, unsigned int id, TCPDataStructure::DataTCPServer &data);
        ~ServerTCPHandler();
        void start();
        void read();
        void stop();
        void write(std::pair<std::array<uint16_t, 50>, std::size_t> &message);
        unsigned int getID() const;

    private:
        void handle_read(const asio::error_code& err, size_t size);
        void handle_write(const asio::error_code& err, size_t size);

        bool _end = false;
        asio::ip::tcp::tcp::socket _socket;
        std::array<char, MAX_LENGTH> _data;
        unsigned int _id;
        std::string _receiveData;
        std::string _response;

        std::array<uint16_t, 50> _recvBuffer;

        TCPDataStructure::DataTCPServer &_dataServer;
    };
}

#endif /* !SERVERTCPHANDLER_HPP_ */
