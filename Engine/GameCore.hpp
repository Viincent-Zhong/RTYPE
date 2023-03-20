/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** GameCore
*/

#pragma once

#include "IGame.hpp"

namespace Engine {
    class GameCore {
        public:
            GameCore();
            ~GameCore();
            template<class T, class ... Params>
            void setGame(Params &&...params)
            {
                _game = std::make_unique<T>(params...);
            }
            void init();
            void run();

        private:
            std::unique_ptr<IGame> _game;
    };
};