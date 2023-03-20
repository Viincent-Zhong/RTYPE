/*
** EPITECH PROJECT, 2022
** ClientTCP.cpp
** File description:
** ClientTCP.cpp
*/

#include "ClientTCP.hpp"
#include "ErrorLoader.hpp"
#include "Serialization.hpp"

EngineNetwork::ClientTCP::ClientTCP(std::string const &host, std::string const &port)
: _stopped(false), _socket(_ioContext)
{
    asio::ip::tcp::resolver resolver(_ioContext);
    _endpoints = resolver.resolve(host, port);
}

EngineNetwork::ClientTCP::ClientTCP()
: _stopped(false), _socket(_ioContext)
{
}

EngineNetwork::ClientTCP::~ClientTCP()
{
    stop();
}

/**
 * @brief 
 * Connect to the endpoint given at the constructor and start the communication thread (IO)
 */
void EngineNetwork::ClientTCP::start()
{
    bool init = false;

    for (auto endpoint = _endpoints.begin(); endpoint != _endpoints.end(); ++endpoint) {
        try {
            _socket.connect(*endpoint);
            init = true;
            break;
        } catch (asio::system_error const &error) {
        }
    }

    if (init) {
	    _ioThread = std::thread([this]() {_ioContext.run();});
    } else {
        throw ErrorConnection("Couldn't connect to server\n");
    }
}

/**
 * @brief 
 * Connect to the endpoint with host and port given and start the communication thread (IO)
 * 
 */
void EngineNetwork::ClientTCP::startOn(std::string const &host, std::string const &port)
{
    bool init = false;

    try { // Try connecting to a endpoint
        asio::ip::tcp::resolver resolver(_ioContext);
        _endpoints = resolver.resolve(host, port);
        for (auto endpoint = _endpoints.begin(); endpoint != _endpoints.end(); ++endpoint) {
                _socket.connect(*endpoint);
                init = true;
                break;
        }
    }
    catch (asio::system_error const &error) {
    }

    if (init) {
	    _ioThread = std::thread([this]() {_ioContext.run();});
    } else {
        throw ErrorConnection("Couldn't connect to server\n");
    }
}

/**
 * @brief 
 * Disconnect the client from the TCP Server
 * 
 */
void EngineNetwork::ClientTCP::stop()
{
    _stopped = true;
    if (!_ioContext.stopped())
        _ioContext.stop();
    if (_ioThread.joinable())
        _ioThread.join();
    if (_socket.is_open())
        _socket.close();
}

/**
 * @brief 
 * Read for the TCP Server
 * 
 */
void EngineNetwork::ClientTCP::read()
{
    // Clear buffer
    _recvBuffer.fill(0);
    // Read a std::array<uint16_t, 50>
    asio::async_read(_socket, asio::buffer(_recvBuffer, _recvBuffer.size()),
    std::bind(&EngineNetwork::ClientTCP::handleRead, this, std::placeholders::_1, std::placeholders::_2));
}

/**
 * @brief 
 * General function to read message from the TCP Server
 * 
 * @param error 
 * @param size 
 */
void EngineNetwork::ClientTCP::handleRead(asio::error_code const &error, std::size_t size)
{
    if (_stopped) {
        return;
    }
    if (error) {
        _recvBuffer.at(0) = EngineNetwork::DataStructure::networkCode::DECONNECTION;
		_actionList.push({_recvBuffer, {size, 0}});
        _callbackHandleRead();
        return;
    }

    // If has a header (header of size 2) push the message
    if (size > 2) {
        _actionList.push({_recvBuffer, {size, 0}});
        _callbackHandleRead();
    }
    read();
}

/**
 * @brief 
 * Send a message to All (for the client, All is only the TCP Server)
 * 
 * @param message 
 */
void EngineNetwork::ClientTCP::writeToAll(std::pair<std::array<uint16_t, 50>, std::size_t> &message)
{
    asio::async_write(_socket, asio::buffer(message.first, message.first.size()),
        std::bind(&EngineNetwork::ClientTCP::handleWrite, this, std::placeholders::_1));
}

/**
 * @brief 
 * Send a message to All (for the client, All is only the TCP Server) except for one ID
 * 
 * @param message 
 * @param exception 
 */
void EngineNetwork::ClientTCP::writeToAllExceptFor(std::pair<std::array<uint16_t, 50>, std::size_t> &message, std::vector<unsigned int> &exception)
{
    asio::async_write(_socket, asio::buffer(message.first, message.first.size()),
        std::bind(&EngineNetwork::ClientTCP::handleWrite, this, std::placeholders::_1));
}

/**
 * @brief 
 * Send a message to All (for the client, All is only the TCP Server) except for one ID given by reference
 * 
 * @param message 
 * @param exception 
 */
void EngineNetwork::ClientTCP::writeToAllExceptFor(std::pair<std::array<uint16_t, 50>, std::size_t> &message, std::vector<unsigned int> &&exception)
{
    asio::async_write(_socket, asio::buffer(message.first, message.first.size()),
        std::bind(&EngineNetwork::ClientTCP::handleWrite, this, std::placeholders::_1));
}

/**
 * @brief 
 * Client-Side, Send a message to TCP Server
 * 
 * @param id 
 * @param message 
 */
void EngineNetwork::ClientTCP::writeToID(unsigned int id, std::pair<std::array<uint16_t, 50>, std::size_t> &message)
{
    asio::async_write(_socket, asio::buffer(message.first, message.first.size()),
        std::bind(&EngineNetwork::ClientTCP::handleWrite, this, std::placeholders::_1));
}

/**
 * @brief 
 * General function to write message to the TCP Server 
 * 
 * @param error 
 */
void EngineNetwork::ClientTCP::handleWrite(asio::error_code const &error)
{
    if (_stopped)
        return;
    if (error) {
        // Server doesn't received message
        stop();
    }
}

/**
 * @brief 
 * Recursively read message from TCP Server
 * 
 */
void EngineNetwork::ClientTCP::loopRead(std::function<void()> &callbackHandleRead)
{
    _callbackHandleRead = callbackHandleRead;
    read();
}

/**
 * @brief 
 * Recursively read message from TCP Server
 * 
 */
void EngineNetwork::ClientTCP::loopRead(std::function<void()> &&callbackHandleRead)
{
    _callbackHandleRead = callbackHandleRead;
    read();
}

/**
 * @brief 
 * Get the List of Actions
 * 
 * @return EngineUtils::Queue<std::pair<std::array<uint16_t, 50>, std::pair<std::size_t, unsigned int>>>& 
 */
EngineUtils::Queue<std::pair<std::array<uint16_t, 50>, std::pair<std::size_t, unsigned int>>> &EngineNetwork::ClientTCP::getReadList()
{
    return _actionList;
}

/**
 * @brief 
 * Delete first read message of the list
 * 
 */
void EngineNetwork::ClientTCP::delElemListAction()
{
    _actionList.pop();
}