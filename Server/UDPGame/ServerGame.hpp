/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** ServerGame
*/

#pragma once

#include <mutex>
#include <thread>
#include "Registry.hpp"
#include "ESystems.hpp"
#include "IGame.hpp"
#include "INetwork.hpp"
#include "Singletons.hpp"
#include "EntityCache.hpp"

namespace EngineServer {
    enum Init {
        IAUXILIARY,
        IMISSILE,
        IENEMY,
        IPLAYER,
        IBACKGROUND,
        IBONUS,
        IOBSTACLE
    };

    std::string const defaultEntityPath = "./Initialization/Entity";

    class ServerGame : public Engine::IGame {
        public:
            ServerGame();
            ServerGame(EngineNetwork::INetwork *server, unsigned int id, std::string const &waves);
            ~ServerGame();
            void initGame();
            void gameLoop();
            bool endCondition();
            void initNetwork();
            void initNetworkSend();
            void initNetworkRead();
            void stop();

			typedef void (*FuncPtr)(std::pair<std::array<uint16_t, 50>, std::pair<std::size_t, unsigned int>> &, Registry &, EngineComponent::Singletons &);
            enum SystemEnum {
                SPHYSIQUE,
                SINPUTHANDLING,
                SDRAW,
                SBACKGROUND,
                SNETWORK,
                SENEMY
            };
        private:
            void handleReceivedMessages();
            void handleSendingMessages();
            bool _end = false;
            bool _init = false;
            unsigned int _gameID = 0;
            std::unique_ptr<EngineNetwork::INetwork> _server;
    		Registry _register;
			EngineComponent::Singletons _singletons;
    		EngineSystem::Systems _systems;
            std::string _waves;

            // List to translate incoming messages
            std::unordered_map<char, FuncPtr> _translateList;
    };
};