/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** GameCore
*/

#include <iostream>
#include "GameCore.hpp"

namespace Engine {
    GameCore::~GameCore()
    {
    }

    GameCore::GameCore()
    {
    }

    /**
     * @brief 
     * Initialize the main loop of the Game 
     * 
     */
    void GameCore::init()
    {
        try {
            _game.get()->initGame();
            _game.get()->initNetwork();
            _game.get()->initNetworkRead();
            _game.get()->initNetworkSend();
        } catch (std::exception &e) {
            std::cerr << e.what() << std::endl;
        }
    }

    /**
     * @brief 
     * Run the game Loop
     * 
     */
    void GameCore::run()
    {
        while (_game.get()->endCondition() == false) {
            _game.get()->gameLoop();
        }
        std::cout << "Game ended\n";
    }
};