/*
** EPITECH PROJECT, 2022
** Project R-TYPE
** File description:
** startClient.cpp
*/

#include <iostream>
#include "ClientUDP.hpp"
#include "ClientTCP.hpp"
#include "ClientGame.hpp"
#include "GameCore.hpp"


/**
 * @brief 
 * Start the UDP server (in lobby) for the client 
 * 
 * @param host 
 * @param port 
 * @return true 
 * @return false 
 */
bool startUDPClient(std::string const &host, std::string const &port)
{
    Engine::GameCore game;

    game.setGame<EngineClient::ClientGame>(new EngineNetwork::ClientUDP(host, port));
    game.init();
    game.run();
    return true;
}

/**
 * @brief 
 * start the TCP server (in Main Menu) for the client
 */
void startTCPClient()
{
    Engine::GameCore game;

    game.setGame<EngineClient::ClientMenu>(new EngineNetwork::ClientTCP());
    game.init();
    game.run();
}
