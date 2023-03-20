/*
** EPITECH PROJECT, 2022
** Project R-TYPE
** File description:
** ClientMenu.hpp
*/

#ifndef CLIENT_MENU_HPP_
#define CLIENT_MENU_HPP_

#include <string>
#include <map>
#include <thread>
#include "TCPDataStructure.hpp"

#include "Registry.hpp"
#include "ESystems.hpp"
#include "IGame.hpp"
#include "IGraphical.hpp"
#include "Iinteraction.hpp"
#include "ISound.hpp"
#include "INetwork.hpp"
#include "DataStructure.hpp"
#include "Singletons.hpp"

namespace EngineClient {

    class ClientMenu : public Engine::IGame {
        public:
            ClientMenu(EngineNetwork::INetwork *server);
            ~ClientMenu();
            void initGame();
            void gameLoop();
            bool endCondition();
            void initNetwork();
            void initNetworkSend();
            void initNetworkRead();
            void stop();

        protected:
        private:
            void handleReadedMessages();
            void handleSendingMessages();
            void loadSingletons();
            void runSingletons();
            void initSoundEffect(std::string const &file, bool music);
            void handleAudio();
            void loadFont();
            void displayLayerOne();
            void displayLayerTwo();
            void displayLayerThree();
            void displayLayerFour();
            void displayLayerFive();
            void displayLayerSix();
            void displayLayerSeven();
            bool _end = false;
            std::unique_ptr<EngineNetwork::INetwork> _client;
            std::string _host;

            // Function have : Message, Party list, MessageToSend list
            typedef void (*ClientReceivePtr)(std::pair<std::array<uint16_t, 50>, std::pair<std::size_t, unsigned int>> &, Registry &, EngineComponent::Singletons &);
            std::unordered_map<char, ClientReceivePtr> _listReceive;

            std::unique_ptr<PadaEngine::IGraphical> _lib;
            std::unique_ptr<PadaEngine::Iinteraction> _inter;
            std::unordered_map<std::string, std::unique_ptr<PadaEngine::ISoundGame>> _audio;

            Registry _register;
            EngineComponent::Singletons _singletons;
    		EngineSystem::Systems _systems;
    };
}

#endif /* !CLIENT_MENU_HPP_ */
