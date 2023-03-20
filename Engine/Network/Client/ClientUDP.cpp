/*
** EPITECH PROJECT, 2022
** Client.cpp
** File description:
** Client.cpp
*/

#include <iostream>
#include "ClientUDP.hpp"
#include "UDPDataStructure.hpp"

EngineNetwork::ClientUDP::ClientUDP(std::string const &host, std::string const &port) : _socket(_ioContext, asio::ip::udp::endpoint(asio::ip::udp::v4(), 0)), _end(false)
{
    // asio::ip::udp::udp::resolver resolver(_ioContext);

    // _receiverEndpoint = *resolver.resolve(asio::ip::udp::udp::v4(), host, port).begin();
    // _socket.open(asio::ip::udp::udp::v4());
    asio::ip::udp::resolver resolver(_ioContext);
    _receiverEndpoint = resolver.resolve(asio::ip::udp::v4(), host, port);
}

EngineNetwork::ClientUDP::~ClientUDP()
{
    if (!_end)
        stop();
}

/**
 * @brief 
 * Send a message to All (for the client, All is only the UDP Server)
 * 
 * @param message 
 */
void EngineNetwork::ClientUDP::writeToAll(std::pair<std::array<uint16_t, 50>, std::size_t> &message)
{
    if (!_socket.is_open())
        return;
    _socket.async_send_to(asio::buffer(message.first, message.first.size()), *_receiverEndpoint.begin(),
        std::bind(&EngineNetwork::ClientUDP::handleWrite, this,
        std::placeholders::_1, std::placeholders::_2));
}

/**
 * @brief 
 * 
 * @param message 
 * @param exception 
 */
void EngineNetwork::ClientUDP::writeToAllExceptFor(std::pair<std::array<uint16_t, 50>, std::size_t> &message, std::vector<unsigned int> &exception)
{
    if (!_socket.is_open())
        return;
    _socket.async_send_to(asio::buffer(message.first, message.first.size()), *_receiverEndpoint.begin(),
        std::bind(&EngineNetwork::ClientUDP::handleWrite, this,
        std::placeholders::_1, std::placeholders::_2));
}

/**
 * @brief
 * Send a message to All (for the client, All is only the UDP Server) except for one ID
 * 
 * 
 * @param message 
 * @param exception 
 */
void EngineNetwork::ClientUDP::writeToAllExceptFor(std::pair<std::array<uint16_t, 50>, std::size_t> &message, std::vector<unsigned int> &&exception)
{
    if (!_socket.is_open())
        return;
    _socket.async_send_to(asio::buffer(message.first, message.first.size()), *_receiverEndpoint.begin(),
        std::bind(&EngineNetwork::ClientUDP::handleWrite, this,
        std::placeholders::_1, std::placeholders::_2));
}

/**
 * @brief 
 * Client-Side, Send a message to UDP Server
 * 
 * @param id 
 * @param message 
 */
void EngineNetwork::ClientUDP::writeToID(unsigned int id, std::pair<std::array<uint16_t, 50>, std::size_t> &message)
{
    if (!_socket.is_open())
        return;
    _socket.async_send_to(asio::buffer(message.first, message.first.size()), *_receiverEndpoint.begin(),
        std::bind(&EngineNetwork::ClientUDP::handleWrite, this,
        std::placeholders::_1, std::placeholders::_2));
}

/**
 * @brief 
 * Read a message from the UDP Server
 * 
 */
void EngineNetwork::ClientUDP::read()
{
    _recvBuffer.fill(0);
    if (!_socket.is_open())
        return;
    _socket.async_receive_from(asio::buffer(_recvBuffer, _recvBuffer.size()), _senderEndpoint,
        std::bind(&EngineNetwork::ClientUDP::handleRead, this, std::placeholders::_1, std::placeholders::_2));
}

/**
 * @brief 
 * General function to read message from the UDP Server
 * 
 * @param error 
 * @param size 
 */
void EngineNetwork::ClientUDP::handleRead(const asio::error_code &error, std::size_t size)
{
	if (error) {
		return;
	}

    if (size > 2 && !_end) {
        _actionList.push({_recvBuffer, {size, 0}});
        _callbackHandleRead();
    }

    if (!_end)
	    read();
}

/**
 * @brief 
 * General function to write message to the UDP Server 
 * 
 * @param error 
 * @param size 
 */
void EngineNetwork::ClientUDP::handleWrite(asio::error_code const &error, std::size_t size)
{
}

/**
 * @brief 
 * Run the Network connection between Client and UDP Server
 * 
 */
void EngineNetwork::ClientUDP::start()
{
	_ioThread = std::thread([this]() {_ioContext.run();});
}

/**
 * @brief Connect to a server with give host and port
 * 
 * @param host 
 * @param port 
 */
void EngineNetwork::ClientUDP::startOn(std::string const &host, std::string const &port)
{
}

/**
 * @brief 
 * Disconnect the client from the UDP Server
 * 
 */
void EngineNetwork::ClientUDP::stop()
{
    _end = true;
    if (!_ioContext.stopped())
        _ioContext.stop();
    if (_ioThread.joinable())
        _ioThread.join();
    if (_socket.is_open())
        _socket.close();
}

/**
 * @brief 
 * Loop the read function
 * 
 * @param callbackHandleRead 
 */
void EngineNetwork::ClientUDP::loopRead(std::function<void()> &callbackHandleRead)
{
    _callbackHandleRead = callbackHandleRead;
    read();
}

/**
 * @brief 
 * Loop the read function
 * @param callbackHandleRead 
 */
void EngineNetwork::ClientUDP::loopRead(std::function<void()> &&callbackHandleRead)
{
    _callbackHandleRead = callbackHandleRead;
    read();
}

/**
 * @brief 
 * Get the List of Actions to read
 * 
 * @return EngineUtils::Queue<std::pair<std::array<uint16_t, 50>, std::pair<std::size_t, unsigned int>>>& 
 */
EngineUtils::Queue<std::pair<std::array<uint16_t, 50>, std::pair<std::size_t, unsigned int>>> &EngineNetwork::ClientUDP::getReadList()
{
    return _actionList;
}

/**
 * @brief 
 * Delete first read message of the list
 */
void EngineNetwork::ClientUDP::delElemListAction()
{
}
