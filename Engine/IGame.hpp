/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** IGame
*/

#pragma once

#include <memory>

namespace Engine {
    class IGame {
        public:
            virtual ~IGame() = default;
            virtual void initGame() = 0;
            virtual void gameLoop() = 0;
            virtual bool endCondition() = 0;
            virtual void initNetwork() = 0;
            virtual void initNetworkSend() = 0;
            virtual void initNetworkRead() = 0;
            virtual void stop() = 0;
    };
};
