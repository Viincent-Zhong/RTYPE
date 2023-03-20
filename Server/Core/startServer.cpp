/*
** EPITECH PROJECT, 2022
** Project R-TYPE
** File description:
** startServer.cpp
*/

#include <iostream>
#include <future>
#include "ServerUDP.hpp"
#include "ServerTCP.hpp"
#include "ServerGame.hpp"
#include "GameCore.hpp"

/**
 * @brief 
 * Start the UDP Server, Server-side
 * 
 * @param port 
 * @param gameStarted 
 * @param roomID 
 * @param gameEnded 
 * @param gameIndex 
 * @param waves 
 * @return true 
 * @return false 
 */
bool startUDPServer(uint16_t port, unsigned int roomID, std::function<void(unsigned int)> &&gameStarted, std::function<void(unsigned int)> &&gameEnded, std::string const &waves)
{
    try {
        Engine::GameCore game;
        // Launch server

        // Init Game
        game.setGame<EngineServer::ServerGame>(new EngineNetwork::ServerUDP(port), roomID, waves);
        game.init();

        // Game is ready for the client to connect to
        std::cout << "Server on port " << port << " finished setup\n";
        gameStarted(roomID);

        // Launch game
        game.run();

        // Game ended
        gameEnded(roomID);
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        gameStarted(roomID);
        gameEnded(roomID);
        return false;
    }
    return true;
}

/**
 * @brief 
 * Start the TCP Server, Server-side
 * 
 * @param port 
 * @return true 
 * @return false 
 */
bool startTCPServer()
{
    try {
        Engine::GameCore game;

        // Set Game
        game.setGame<EngineServer::ServerMenu>(new EngineNetwork::ServerTCP());
        // Init (crash vient de la ?)
        game.init();
        // // Run
        game.run();
    } catch (std::exception &e) {
        std::cerr << "Exception: " << e.what() << "\n";
        return false;
    }
    return true;
}
