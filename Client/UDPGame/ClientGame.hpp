/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** ClientGame
*/

#pragma once

#include <thread>
#include "IGraphical.hpp"
#include "Iinteraction.hpp"
#include "ISound.hpp"
#include "IGame.hpp"
#include "INetwork.hpp"
#include "Registry.hpp"
#include "ESystems.hpp"
#include "Singletons.hpp"
#include "TextureCache.hpp"
#include "EntityCache.hpp"

namespace EngineClient {
    enum InitEnum {
        BACKGROUND,
        BUTTON,
        TEXT,
        VISUAL_EFFECT,
        FONT
    };
    std::string const defaultEntityPath = "./Initialization/Entity";

    class ClientGame : public Engine::IGame {
        public:
            ClientGame();
            ClientGame(EngineNetwork::INetwork *server);
            ~ClientGame();
            void initGame();
            void gameLoop();
            bool endCondition();
            void initNetwork();
            void initNetworkSend();
            void initNetworkRead();
            void stop();
            enum SystemEnum {
                SDRAW,
                SBACKGROUND,
                SPHYSIQUE,
                SVISUAL_EFFECT,
                SRENDERING,
                STEXT
            };

        private:
            bool _end = false;
            void handleReadedMessages();
            void inputControl();
            void handleAudio();
            void initSoundEffect(std::string const &file, bool music);
            void runSystems();
            void loadSingletons();
            void loadFont();
            std::unique_ptr<PadaEngine::IGraphical> _lib;
            std::unique_ptr<PadaEngine::Iinteraction> _inter;

            Registry _register;
            EngineComponent::Singletons _singletons;
    		EngineSystem::Systems _systems;
            std::unordered_map<std::string, std::unique_ptr<PadaEngine::ISoundGame>> _audio;
            EngineUtils::Timer _timeout;

            std::unique_ptr<EngineNetwork::INetwork> _client;

            typedef void (*ClientReceivePtr)(std::pair<std::array<uint16_t, 50>, std::pair<std::size_t, unsigned int>> &, Registry &, EngineComponent::Singletons &);
            std::unordered_map<char, ClientReceivePtr> _listReceive;
    };
};