/*
** EPITECH PROJECT, 2022
** Project R-TYPE
** File description:
** tcpServerGameLogic.hpp
*/

#pragma once

#include <string>
#include "TCPDataStructure.hpp"
#include "ServerMenu.hpp"


/**
 * @brief Check if the player has a good name, send back yes or no and his id
 */
void RegisterPlayer(std::pair<std::array<uint16_t, 50>, std::pair<std::size_t, unsigned int>> &message,
                EngineComponent::Singletons &singletons);

/**
 * @brief Send all rooms
 */
void sendRoomList(std::pair<std::array<uint16_t, 50>, std::pair<std::size_t, unsigned int>> &message,
                EngineComponent::Singletons &singletons);

/**
 * @brief Creating a new room for the players, send back the new room ID
 */
void playerCreatingRoom(std::pair<std::array<uint16_t, 50>, std::pair<std::size_t, unsigned int>> &message,
                EngineComponent::Singletons &singletons);

/**
 * @brief Player joined or not the room, send back yes or no
 */
void playerJoiningRoom(std::pair<std::array<uint16_t, 50>, std::pair<std::size_t, unsigned int>> &message,
                EngineComponent::Singletons &singletons);

/**
 * @brief Sending from the asked room all the players
 */
void sendRoomPlayers(std::pair<std::array<uint16_t, 50>, std::pair<std::size_t, unsigned int>> &message,
                EngineComponent::Singletons &singletons);

/**
 * @brief Players is launching the game
 */
void playerLaunchGame(std::pair<std::array<uint16_t, 50>, std::pair<std::size_t, unsigned int>> &message,
                EngineComponent::Singletons &singletons);

/**
 * @brief Player is leaving the room
 */
void playerLeaveRoom(std::pair<std::array<uint16_t, 50>, std::pair<std::size_t, unsigned int>> &message,
                EngineComponent::Singletons &singletons);

/**
 * @brief Player is leaving the room
 */
void playerCrash(std::pair<std::array<uint16_t, 50>, std::pair<std::size_t, unsigned int>> &message,
                EngineComponent::Singletons &singletons);

