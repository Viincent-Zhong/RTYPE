/*
** EPITECH PROJECT, 2022
** Project R-TYPE
** File description:
** logicGameServer.hpp
*/

#ifndef LOGICGAMESERVER_HPP_
#define LOGICGAMESERVER_HPP_

#include "Registry.hpp"
#include "Singletons.hpp"

/**
 * @brief Give to the client an available id for it to play with
 */
void clientConnection(std::pair<std::array<uint16_t, 50>, std::pair<std::size_t, unsigned int>> &, Registry &r, EngineComponent::Singletons &singletons);
void clientMove(std::pair<std::array<uint16_t, 50>, std::pair<std::size_t, unsigned int>> &, Registry &r, EngineComponent::Singletons &singletons);
/**
 * @brief Spawn a missile
 */
void clientFire(std::pair<std::array<uint16_t, 50>, std::pair<std::size_t, unsigned int>> &, Registry &r, EngineComponent::Singletons &singletons);
void clientDisconnect(std::pair<std::array<uint16_t, 50>, std::pair<std::size_t, unsigned int>> &, Registry &r, EngineComponent::Singletons &singletons);
/**
 * @brief Send back all entities to the client
 */
void clientSendGameDatas(std::pair<std::array<uint16_t, 50>, std::pair<std::size_t, unsigned int>> &read, Registry &r, EngineComponent::Singletons &singletons);

/**
 * @brief Send all entities to all client
 */
void sendEntities(Registry &r, EngineComponent::Singletons &singletons);

/**
 * @brief Send all entities to a client
 * 
 * @param clientID clientID
 * @param r 
 * @param singletons 
 */
void sendEntities(unsigned int clientID, Registry &r, EngineComponent::Singletons &singletons);

/**
 * @brief Send entity to all client
 * 
 * @param i Entity ID
 * @param r 
 * @param singletons 
 */
void sendEntity(unsigned int i, Registry &r, EngineComponent::Singletons &singletons);

/**
 * @brief Send an entity to the client
 * 
 * @param clientID clientID
 * @param i Entity ID
 * @param r 
 * @param singletons 
 */
void sendEntity(unsigned int clientID, unsigned int i, Registry &r, EngineComponent::Singletons &singletons);

/**
 * @brief Send an entity to all client except for a client
 * 
 * @param i EntityID
 * @param r 
 * @param singletons 
 * @param exception ClientID that we don't want to ping
 */
void sendEntity(unsigned int i, Registry &r, EngineComponent::Singletons &singletons, unsigned int exception);

/**
 * @brief Notify all players that a entity got killed
 * 
 * @param r 
 * @param singletons 
 * @param id EntityID
 */
void sendKill(Registry &r, EngineComponent::Singletons &singletons, std::size_t id);

/**
 * @brief Notify all players that the game ended
 */
void pingGameEnded(Registry &r, EngineComponent::Singletons &singletons);

#endif /* !LOGICGAMESERVER_HPP_ */
