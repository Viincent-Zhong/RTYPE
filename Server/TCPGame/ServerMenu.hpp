/*
** EPITECH PROJECT, 2022
** Project R-TYPE
** File description:
** ServerMenu.hpp
*/

#ifndef SERVERMENU_HPP_
#define SERVERMENU_HPP_

#include <unordered_map>
#include <memory>
#include <string>
#include <thread>
#include <array>
#include <thread>
#include <future>
#include "INetwork.hpp"
#include "TCPDataStructure.hpp"
#include "IGame.hpp"
#include "DataStructure.hpp"
#include "Singletons.hpp"

namespace EngineServer {
    class ServerMenu : public Engine::IGame {
        public:
            ServerMenu(EngineNetwork::INetwork *server);
            ~ServerMenu();
            void initGame();
            void gameLoop();
            bool endCondition();
            void initNetwork();
            void initNetworkSend();
            void initNetworkRead();
            void stop();

        private:
            void handleReceivedMessages();
            void handleSendingMessages();
            void launchingRooms();
            void pingStartRoom(unsigned int roomID);
            void threadGameEnded(unsigned int gameIndex);
            bool _end = false;
            std::unique_ptr<EngineNetwork::INetwork> _server;
            EngineComponent::Singletons _singletons;

            EngineUtils::Queue<std::pair<EngineNetwork::DataStructure::Message, EngineNetwork::DataStructure::MessageTarget>> _sendList;

            // Vector of a game with its id
            std::vector<std::pair<std::thread, unsigned int>> _games;

            typedef void(*FuncPtr)(
                std::pair<std::array<uint16_t, 50>, std::pair<std::size_t, unsigned int>> &,
                EngineComponent::Singletons &
            );
            std::unordered_map<uint16_t, FuncPtr> _list;
            uint16_t _startPort = 1235;
            uint16_t _maxPort = 65535;
    };
}

#endif /* !SERVERMENU_HPP_ */
