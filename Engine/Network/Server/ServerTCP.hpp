/*
** EPITECH PROJECT, 2022
** ServerTCP.hpp
** File description:
** ServerTCP.hpp
*/

#ifndef SERVERTCP_HPP_
#define SERVERTCP_HPP_

#include <functional>
#include "Queue.hpp"
#include "ServerTCPHandler.hpp"
#include "INetwork.hpp"

namespace EngineNetwork {
class ServerTCP : public INetwork {
    public:
        ServerTCP(asio::io_context& io_context, short port);
        ServerTCP();
        ~ServerTCP();
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
        void accept();

    private:
        void checkClientDisconnection();
        bool _end = false;
        std::thread _ioThread;
        asio::io_context _ioContext;

        asio::ip::tcp::tcp::acceptor _acceptor;
        unsigned int _nbrClient = 0;
        TCPDataStructure::DataTCPServer _data;

        std::vector<std::shared_ptr<EngineNetwork::ServerTCPHandler>> _clients;
    };
}

#endif /* !SERVERTCP_HPP_ */
