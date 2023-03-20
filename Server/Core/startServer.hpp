/*
** EPITECH PROJECT, 2022
** Project R-TYPE
** File description:
** startServer.hpp
*/

#ifndef STARTSERVER_HPP_
#define STARTSERVER_HPP_

#include <future>

/**
 * @brief Launch a game with an UDP Server
 * @param roomID id of its related room
 * @param gameStarted Callback to a function pinging all clients of the room
 * @param gameEnded Callback to a function erasing the game
 * @param waves
 */
bool startUDPServer(uint16_t port, unsigned int roomID, std::function<void(unsigned int)> &&gameStarted, std::function<void(unsigned int)> &&gameEnded, std::string const &waves);

bool startTCPServer();

#endif /* !STARTSERVER_HPP_ */
