/*
** EPITECH PROJECT, 2022
** Project R-TYPE
** File description:
** ServerTCPHandler.cpp
*/

#include <iostream>
#include "ServerTCPHandler.hpp"

EngineNetwork::ServerTCPHandler::ServerTCPHandler(asio::ip::tcp::tcp::socket socket, unsigned int id, TCPDataStructure::DataTCPServer &data) : _socket(std::move(socket)), _dataServer(data), _id(id)
{
}

EngineNetwork::ServerTCPHandler::~ServerTCPHandler()
{
    _end = true;
    _socket.close();
}

/**
 * @brief 
 * Start 
 * 
 */
void EngineNetwork::ServerTCPHandler::start()
{
    read();
}

void EngineNetwork::ServerTCPHandler::write(std::pair<std::array<uint16_t, 50>, std::size_t> &message)
{
    if (!_socket.is_open())
        return;
    asio::async_write(_socket,
        asio::buffer(message.first, message.first.size()),
        std::bind<void>(&ServerTCPHandler::handle_write,
        shared_from_this(),
        std::placeholders::_1, std::placeholders::_2));
}

void EngineNetwork::ServerTCPHandler::stop()
{
    _end = true;
    _socket.close();
}

void EngineNetwork::ServerTCPHandler::read()
{
    if (!_socket.is_open())
        return;
    _socket.async_receive(asio::buffer(_recvBuffer, _recvBuffer.size()),
    std::bind<void>(&ServerTCPHandler::handle_read, shared_from_this(),
    std::placeholders::_1, std::placeholders::_2));
}

void EngineNetwork::ServerTCPHandler::handle_read(const asio::error_code& err, size_t size)
{
    if (err) {
        // Push disconnected client for the server to remove it
        _dataServer._leavedClients.push(_id);
        _dataServer._callbackHandleClientLeaved();

        // Push a message saying the client disconnected for the Server Logic to do its things
        _recvBuffer.at(0) = EngineNetwork::TCPDataStructure::codeTCP::CLIENT_DISCONNECTION;
        _dataServer._readList.push({_recvBuffer, {size, _id}});
        _dataServer._callbackHandleRead();
        return;
    }

	if (size >= 2) {
		_dataServer._readList.push({_recvBuffer, {size, _id}});
        _dataServer._callbackHandleRead();
	}
    if (!_end)
        read();
}

void EngineNetwork::ServerTCPHandler::handle_write(const asio::error_code& err, size_t size)
{
}

unsigned int EngineNetwork::ServerTCPHandler::getID() const
{
    return _id;
}