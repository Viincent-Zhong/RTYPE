/*
** EPITECH PROJECT, 2022
** ServerTCP.cpp
** File description:
** ServerTCP.cpp
*/

#include <iostream>
#include "ServerTCP.hpp"

/**
 * @brief 
 * Check if the port is already in use
 * 
 * @param port 
 * @return true 
 * @return false 
 */
static bool portInUse(uint16_t port)
{
    asio::io_context svc;
    asio::ip::tcp::acceptor a(svc);

    asio::error_code ec;
    a.open(asio::ip::tcp::v4(), ec);
    a.bind({ asio::ip::tcp::v4(), port }, ec);

    return ec == asio::error::address_in_use;
}

EngineNetwork::ServerTCP::ServerTCP(asio::io_context& io_context, short port) : _acceptor(io_context, asio::ip::tcp::tcp::endpoint(asio::ip::tcp::tcp::v4(), port))
{
    _nbrClient = 1;
    _data._callbackHandleClientLeaved = [this]() {
        checkClientDisconnection();
    };
}

EngineNetwork::ServerTCP::ServerTCP() : _ioContext(), _acceptor(_ioContext), _nbrClient(1)
{
    uint16_t port = 1234; // Start port at 1234

    bool freePort = false;
    for (; port < 65535; ++port) // Find an avaiable port
        if (!portInUse(port)) { // Found a port
            freePort = true;
            break;
        }
    if (!freePort)
        throw ErrorConnection("Couldn't find any available port\n");

    asio::ip::tcp::tcp::endpoint endpoint(asio::ip::tcp::tcp::v4(), port);
    _acceptor.open(endpoint.protocol());
    _acceptor.bind(endpoint);
    _acceptor.listen();

    std::cout << "Server starting on port : " << port << "\n";
    _nbrClient = 1;
    _data._callbackHandleClientLeaved = [this]() {
        checkClientDisconnection();
    };
}

EngineNetwork::ServerTCP::~ServerTCP()
{
    _end = true;
    if (_acceptor.is_open())
        _acceptor.close();
    for (auto client : _clients) {
        client.get()->stop();
    }
    if (_ioThread.joinable())
        _ioThread.join();
}

/**
 * @brief 
 * Accept the new client on TCP Server
 * 
 */
void EngineNetwork::ServerTCP::accept()
{
    _acceptor.async_accept(
        [this](std::error_code ec, asio::ip::tcp::tcp::socket socket)
        {
            std::cout << "New client connect" << std::endl;
            if (!ec) {
                _clients.push_back(std::make_shared<EngineNetwork::ServerTCPHandler>(std::move(socket), _nbrClient++, _data));
                _clients.back().get()->start();
                std::cout << "Accepted connection" << std::endl;
            }
            accept();
        });
}

/**
 * @brief 
 * Start the thread for accepting new client
 * 
 */
void EngineNetwork::ServerTCP::start()
{
    accept();
	_ioThread = std::thread([this]() {_ioContext.run();});
}

/**
 * @brief Start server on given host and port
 * 
 * @param host 
 * @param port 
 */
void EngineNetwork::ServerTCP::startOn(std::string const &host, std::string const &port)
{
}

/**
 * @brief 
 * Close all thread when server is closing
 * 
 */
void EngineNetwork::ServerTCP::stop()
{
    _end = true;
    for (auto client : _clients) {
        client.get()->stop();
    }
    if (_ioThread.joinable())
        _ioThread.join();
}

void EngineNetwork::ServerTCP::read() {}

/**
 * @brief 
 * Send a message/string from the TCP Server to all the Clients
 * 
 * @param message 
 */
void EngineNetwork::ServerTCP::writeToAll(std::pair<std::array<uint16_t, 50>, std::size_t> &message)
{
    for (auto client : _clients) {
        client.get()->write(message);
    }
}

/**
 * @brief 
 * Send a message/string from the TCP Server to all the Clients except one of them
 * 
 * @param message 
 * @param exception 
 */
void EngineNetwork::ServerTCP::writeToAllExceptFor(std::pair<std::array<uint16_t, 50>, std::size_t> &message, std::vector<unsigned int> &exception)
{
	bool except = false;

    for (auto client : _clients) {
		for (auto exceptID : exception)
            if (client.get()->getID() == exceptID) {
		    	except = true;
		    	break;
            }
        if (!except)
            client.get()->write(message);
		except = false;
    }
}

/**
 * @brief 
 * Send a message/string from the TCP Server to all the Clients except one of them given by reference
 * 
 * @param message 
 * @param exception 
 */
void EngineNetwork::ServerTCP::writeToAllExceptFor(std::pair<std::array<uint16_t, 50>, std::size_t> &message, std::vector<unsigned int> &&exception)
{
	bool except = false;

    for (auto client : _clients) {
		for (auto exceptID : exception)
            if (client.get()->getID() == exceptID) {
		    	except = true;
		    	break;
            }
        if (!except)
            client.get()->write(message);
		except = false;
    }
}

/**
 * @brief 
 * Write a message/string from the TCP Server to a signle Client
 * 
 * @param id 
 * @param message 
 */
void EngineNetwork::ServerTCP::writeToID(unsigned int id, std::pair<std::array<uint16_t, 50>, std::size_t> &message)
{
    for (auto client : _clients) {
        if (client.get()->getID() == id)
            client.get()->write(message);
    }
}

/**
 * @brief 
 * Loop to read message sent by client
 * 
 */
void EngineNetwork::ServerTCP::loopRead(std::function<void()> &callbackHandleRead)
{
    _data._callbackHandleRead = callbackHandleRead;
}

/**
 * @brief 
 * Loop to read message sent by client, given by reference
 * 
 * @param callbackHandleRead 
 */
void EngineNetwork::ServerTCP::loopRead(std::function<void()> &&callbackHandleRead)
{
    _data._callbackHandleRead = callbackHandleRead;
}

/**
 * @brief 
 * return all messages to read from the Client
 * 
 * @return EngineUtils::Queue<std::pair<std::array<uint16_t, 50>, std::pair<std::size_t, unsigned int>>>& 
 */
EngineUtils::Queue<std::pair<std::array<uint16_t, 50>, std::pair<std::size_t, unsigned int>>> &EngineNetwork::ServerTCP::getReadList()
{
    return _data._readList;
}

/**
 * @brief 
 * Delete first read message of the list
 * 
 */
void EngineNetwork::ServerTCP::delElemListAction()
{
    _data._readList.pop();
}

/**
 * @brief 
 * Check if a client is disconnected
 */
void EngineNetwork::ServerTCP::checkClientDisconnection()
{
    while (_data._leavedClients.size() != 0) {
        for (auto it = _clients.begin(); it != _clients.end(); ++it) {
            if ((*it).get()->getID() == _data._leavedClients.front()) {
                _clients.erase(it);
                break;
            }
        }
        _data._leavedClients.pop();
    }
}
