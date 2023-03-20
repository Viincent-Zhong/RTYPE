/*
** EPITECH PROJECT, 2022
** Client.hpp
** File description:
** ClientUDP.hpp
*/

#pragma once

#include <string>
#include <asio.hpp>
#include <queue>
#include <functional>
#include "INetwork.hpp"

namespace EngineNetwork {

    class ClientUDP : public EngineNetwork::INetwork {
        public:
            ClientUDP(std::string const &host, std::string const &port);
            ~ClientUDP();
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

        private:
            void handleWrite(asio::error_code const &error, std::size_t size);
	        void handleRead(const asio::error_code &error, std::size_t size);
            void endRead(const asio::error_code &error, std::size_t size);

            bool _end = false;
            asio::io_context _ioContext;
            asio::ip::udp::resolver::results_type _receiverEndpoint;
            asio::ip::udp::udp::endpoint _senderEndpoint;
            asio::ip::udp::udp::socket _socket;
            std::array<uint16_t, 50> _recvBuffer;
            std::function<void()> _callbackHandleRead;
			std::thread _ioThread;
            EngineUtils::Queue<std::pair<std::array<uint16_t, 50>, std::pair<std::size_t, unsigned int>>> _actionList;
    };
}
