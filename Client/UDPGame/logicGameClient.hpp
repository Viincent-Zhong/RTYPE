/*
** EPITECH PROJECT, 2022
** Project R-TYPE
** File description:
** logicGameClient.hpp
*/

#pragma once

#include "Singletons.hpp"
#include "Registry.hpp"

void getStatusPlayer(std::pair<std::array<uint16_t, 50>, std::pair<std::size_t, unsigned int>> &data, Registry &r, EngineComponent::Singletons &singleton);
void getStatusGame(std::pair<std::array<uint16_t, 50>, std::pair<std::size_t, unsigned int>> &data, Registry &r, EngineComponent::Singletons &singleton);
void getDestroyed(std::pair<std::array<uint16_t, 50>, std::pair<std::size_t, unsigned int>> &data, Registry &r, EngineComponent::Singletons &singleton);
void getDeconnected(std::pair<std::array<uint16_t, 50>, std::pair<std::size_t, unsigned int>> &data, Registry &r, EngineComponent::Singletons &singleton);