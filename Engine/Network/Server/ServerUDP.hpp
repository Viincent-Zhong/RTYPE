/*
** EPITECH PROJECT, 2022
** ServerUDP.hpp
** File description:
** ServerUDP.hpp
*/

#pragma once

#include <asio.hpp>
#include <iostream>
#include <functional>
#include "INetwork.hpp"

namespace EngineNetwork {
    class ServerUDP : public INetwork {
        public:
	        ServerUDP(uint16_t port);
	        ~ServerUDP();
			void start();
        	void startOn(std::string const &host, std::string const &port);
			void stop();
	        void read();
			void writeToAll(std::pair<std::array<uint16_t, 50>, std::size_t> &message);
			void writeToAllExceptFor(std::pair<std::array<uint16_t, 50>, std::size_t> &message, std::vector<unsigned int> &exception);
			void writeToAllExceptFor(std::pair<std::array<uint16_t, 50>, std::size_t> &message, std::vector<unsigned int> &&exception);
			void loopRead(std::function<void()> &callbackHandleRead);
			void loopRead(std::function<void()> &&callbackHandleRead);
			void writeToID(unsigned int id, std::pair<std::array<uint16_t, 50>, std::size_t> &message);
			EngineUtils::Queue<std::pair<std::array<uint16_t, 50>, std::pair<std::size_t, unsigned int>>> &getReadList();
			void delElemListAction();

			std::vector<asio::ip::udp::endpoint> _listClient;
        private:
        	asio::io_context _ioService;

	        asio::ip::udp::socket _socket;
	        asio::ip::udp::endpoint _endpoint;
			std::array<uint16_t, 50> _recvBuffer;
			std::thread _ioThread;
			EngineUtils::Queue<std::pair<std::array<uint16_t, 50>, std::pair<std::size_t, unsigned int>>> _actionList;
			std::function<void()> _callbackHandleRead;
			bool _end = false;

	        void send(asio::ip::udp::endpoint &endPoint, std::pair<std::array<uint16_t, 50>, std::size_t> &message);
	        void handleRead(const asio::error_code &error, std::size_t size);
			void handleSend(const asio::error_code &error, std::size_t size);
			void addClientToVec();
			void removeClientFromVec();
			unsigned int getClientID(asio::ip::udp::endpoint &endpoint);

			// GAME
    };
}
