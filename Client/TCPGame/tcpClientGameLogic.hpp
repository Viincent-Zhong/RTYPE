/*
** EPITECH PROJECT, 2022
** Project R-TYPE
** File description:
** tcpClientGameLogic.hpp
*/

#pragma once

#include <string>
#include <array>
#include "Registry.hpp"
#include "Singletons.hpp"

// Receiving from server
void Register(std::pair<std::array<uint16_t, 50>, std::pair<std::size_t, unsigned int>> &data, Registry &r, EngineComponent::Singletons &singleton);
void getRoomsList(std::pair<std::array<uint16_t, 50>, std::pair<std::size_t, unsigned int>> &data, Registry &r, EngineComponent::Singletons &singleton);
void createdRoom(std::pair<std::array<uint16_t, 50>, std::pair<std::size_t, unsigned int>> &data, Registry &r, EngineComponent::Singletons &singleton);
void joinedRoom(std::pair<std::array<uint16_t, 50>, std::pair<std::size_t, unsigned int>> &data, Registry &r, EngineComponent::Singletons &singleton);
void getRoomPlayers(std::pair<std::array<uint16_t, 50>, std::pair<std::size_t, unsigned int>> &data, Registry &r, EngineComponent::Singletons &singleton);
void launchedGame(std::pair<std::array<uint16_t, 50>, std::pair<std::size_t, unsigned int>> &data, Registry &r, EngineComponent::Singletons &singleton);
void deconnected(std::pair<std::array<uint16_t, 50>, std::pair<std::size_t, unsigned int>> &data, Registry &r, EngineComponent::Singletons &singleton);

// Sending to server

void askRegister(EngineComponent::Singletons &singleton, unsigned int id);
void askRoomsList(EngineComponent::Singletons &singleton, unsigned int id);
void askCreatingRoom(EngineComponent::Singletons &singleton, unsigned int id);
void askJoiningRoom(EngineComponent::Singletons &singleton, unsigned int id);
void askRoomPlayers(EngineComponent::Singletons &singleton, unsigned int id);
void askLaunchingGame(EngineComponent::Singletons &singleton, unsigned int id);
void sendLeavingRoom(EngineComponent::Singletons &singleton, unsigned int id);
void sendDeconnecting(EngineComponent::Singletons &singleton, unsigned int id);