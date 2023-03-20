/*
** EPITECH PROJECT, 2022
** ClientTCP.hpp
** File description:
** ClientTCP.hpp
*/

#ifndef CLIENTTCP_HPP_
#define CLIENTTCP_HPP_

#include <asio.hpp>
#include <thread>
#include <functional>
#include "ClientMenu.hpp"
#include "Queue.hpp"
#include "INetwork.hpp"

namespace EngineNetwork {
    class ClientTCP : public EngineNetwork::INetwork {
        public:
            ClientTCP(std::string const &host, std::string const &port);
            ClientTCP();
            ~ClientTCP();

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
            void handleRead(asio::error_code const &error, std::size_t size);
            void handleWrite(asio::error_code const &error);

            bool _stopped;
            std::string _port;
            std::function<void()> _callbackHandleRead;
			std::thread _ioThread;
            asio::io_context _ioContext;
            asio::ip::tcp::resolver::results_type _endpoints;
            asio::ip::tcp::socket _socket;

            std::array<uint16_t, 50> _recvBuffer;
            /* Describing a message with :
              action.first = message
              action.second.first = size
              action.second.second = id of who sent the message
            */
            EngineUtils::Queue<std::pair<std::array<uint16_t, 50>, std::pair<std::size_t, unsigned int>>> _actionList;
    };
}

#endif /* !CLIENTTCP_HPP_ */
