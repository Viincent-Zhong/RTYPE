/*
** EPITECH PROJECT, 2022
** Server.cpp
** File description:
** Server.cpp
*/

#include <iostream>
#include "UDPDataStructure.hpp"
#include "DataStructure.hpp"
#include "ServerUDP.hpp"

EngineNetwork::ServerUDP::ServerUDP(uint16_t port)
	: _ioService(), _socket(_ioService, asio::ip::udp::endpoint(asio::ip::udp::v4(), port))
{
	std::cout << "Created udp server on port " << port << "\n";
}

EngineNetwork::ServerUDP::~ServerUDP()
{
	_end = true;
	if (!_ioService.stopped())
		_ioService.stop();
	if (_ioThread.joinable())
		_ioThread.join();
	if (_socket.is_open())
		_socket.close();
}

/**
 * @brief 
 * Send a message/string to a client(endpoint)
 * 
 * @param endpoint 
 * @param message 
 */
void EngineNetwork::ServerUDP::send(asio::ip::udp::endpoint &endpoint, std::pair<std::array<uint16_t, 50>, std::size_t> &message)
{
	if (!_socket.is_open())
        return;
	_socket.async_send_to(asio::buffer(message.first, message.first.size()), endpoint,
		std::bind(&EngineNetwork::ServerUDP::handleSend, this, std::placeholders::_1, std::placeholders::_2));
}

void EngineNetwork::ServerUDP::handleSend(const asio::error_code &error, std::size_t size)
{
}

/**
 * @brief 
 * Write a message/string from the UDP Server to all the clients
 * 
 * @param message 
 */
void EngineNetwork::ServerUDP::writeToAll(std::pair<std::array<uint16_t, 50>, std::size_t> &message)
{
	for (auto &cli : _listClient)
		send(cli, message);
}

/**
 * @brief 
 * Write a message/string from the UDP Server to all the clients except one of them
 * 
 * @param message 
 * @param exception 
 */
void EngineNetwork::ServerUDP::writeToAllExceptFor(std::pair<std::array<uint16_t, 50>, std::size_t> &message, std::vector<unsigned int> &exception)
{
	bool except = false;

	for (unsigned int i = 1; i < _listClient.size(); ++i) {
		for (auto exceptID : exception) {
			std::cout << "Except id " << except << "\n";
			if (i == exceptID) {
				std::cout << "Player " << i << " is cancelled\n";
				except = true;
				break;
			}
		}
		if (!except)
			send(_listClient.at(i - 1), message);
		except = false;
	}
}

/**
 * @brief 
 * Write a message/string from the UDP Server to all the clients except one of them given by reference
 * 
 * @param message 
 * @param exception 
 */
void EngineNetwork::ServerUDP::writeToAllExceptFor(std::pair<std::array<uint16_t, 50>, std::size_t> &message, std::vector<unsigned int> &&exception)
{
	bool except = false;

	for (unsigned int i = 1; i < _listClient.size(); ++i) {
		for (auto exceptID : exception)
			if (i == exceptID) {
				except = true;
				break;
			}
		if (!except)
			send(_listClient.at(i - 1), message);
		except = false;
	}
}

/**
 * @brief 
 * Write a message/string from the UDP Server to a single Client
 * 
 * @param id 
 * @param message 
 */
void EngineNetwork::ServerUDP::writeToID(unsigned int id, std::pair<std::array<uint16_t, 50>, std::size_t> &message)
{
	// 0 is reserved for errors
	if (id != 0 && id - 1 < _listClient.size()) {
		send(_listClient.at(id - 1), message);
	}
}

/**
 * @brief 
 * Add a client to the list of Clients in a launched Game
 * 
 */
void EngineNetwork::ServerUDP::addClientToVec()
{
	bool inList = false;
	if (_endpoint.port() != 0) {
		for (auto const &cli : _listClient)
			if (cli.address() == _endpoint.address() && cli.port() == _endpoint.port()) {
				inList = true;
			}
		if (!inList) {
			_listClient.push_back(_endpoint);
		}
	}
}

/**
 * @brief 
 * Remove a client to the list of Clients in a launched Game
 */
void EngineNetwork::ServerUDP::removeClientFromVec()
{
	if (_endpoint.port() != 0) {
		for (auto client = _listClient.begin(); client != _listClient.end(); ++client) {
			if (client->address() == _endpoint.address() && client->port() == _endpoint.port()) {
				_listClient.erase(client);
				return;
			}
		}
	}
}

/**
 * @brief 
 * Get the id of a client 
 * 
 * @param endpoint 
 * @return unsigned int 
 */
unsigned int EngineNetwork::ServerUDP::getClientID(asio::ip::udp::endpoint &endpoint)
{
	unsigned int i = 1;

	if (_endpoint.port() != 0) {
		for (auto const &cli : _listClient) {
			if (cli.address() == _endpoint.address() && cli.port() == _endpoint.port())
				return i;
			++i;
		}
	}
	return 0;
}

/**
 * @brief 
 * Read a message/string from a Client
 * 
 */
void EngineNetwork::ServerUDP::read()
{
	_recvBuffer.fill(0);
    if (!_socket.is_open())
        return;
	_socket.async_receive_from(asio::buffer(_recvBuffer, _recvBuffer.size()), _endpoint,
		std::bind(&EngineNetwork::ServerUDP::handleRead, this, std::placeholders::_1, std::placeholders::_2));
}

/**
 * @brief 
 * Loop on the read function
 * 
 * @param callbackHandleRead 
 */
void EngineNetwork::ServerUDP::loopRead(std::function<void()> &callbackHandleRead)
{
	_callbackHandleRead = callbackHandleRead;
	read();
}

/**
 * @brief 
 * Loop on the read function given by reference
 * 
 * @param callbackHandleRead 
 */
void EngineNetwork::ServerUDP::loopRead(std::function<void()> &&callbackHandleRead)
{
	_callbackHandleRead = callbackHandleRead;
	read();
}

/**
 * @brief 
 * Remove a message from the list of Actions
 * 
 */
void EngineNetwork::ServerUDP::delElemListAction()
{
	_actionList.pop();
}

/**
 * @brief 
 * Get the list of Actions
 * 
 * @return EngineUtils::Queue<std::pair<std::array<uint16_t, 50>, std::pair<std::size_t, unsigned int>>>& 
 */
EngineUtils::Queue<std::pair<std::array<uint16_t, 50>, std::pair<std::size_t, unsigned int>>> &EngineNetwork::ServerUDP::getReadList()
{
	return _actionList;
}

/**
 * @brief 
 * Handle the message send by the client
 * 
 * @param error 
 * @param size 
 */
void EngineNetwork::ServerUDP::handleRead(const asio::error_code &error, std::size_t size)
{
	if (error) {
		// _socket.close();
        // Push a message saying the client disconnected for the Server Logic to do its things
        _recvBuffer.at(0) = EngineNetwork::DataStructure::networkCode::DECONNECTION;
		_actionList.push({_recvBuffer, {size, getClientID(_endpoint)}});
		_callbackHandleRead();
		removeClientFromVec();
	}
	addClientToVec();
	if (size >= 2) {
		_actionList.push({_recvBuffer, {size, getClientID(_endpoint)}});
		_callbackHandleRead();
	}
	if (!_end)
		read();
}

/**
 * @brief 
 * Start the UDP Server with threads
 * 
 */
void EngineNetwork::ServerUDP::start()
{
	_ioThread = std::thread([this]() {_ioService.run();});
}

/**
 * @brief Start server on given host and port
 * 
 * @param host 
 * @param port 
 */
void EngineNetwork::ServerUDP::startOn(std::string const &host, std::string const &port)
{
}

/**
 * @brief 
 * Disconnect the UDP Server and all the threads
 * 
 */
void EngineNetwork::ServerUDP::stop()
{
	_end = true;
	if (!_ioService.stopped())
		_ioService.stop();
	if (_ioThread.joinable())
		_ioThread.join();
	if (_socket.is_open())
		_socket.close();
}
