/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** EntityGeneration
*/

#pragma once

#include "Registry.hpp"
#include "Singletons.hpp"
#include "EntityCache.hpp"
#include "Queue.hpp"

namespace System {
    void spawnAuxiliaries(Registry &r, std::size_t indexPlayer, std::string const &aux, EngineEntity::EntityCache &initEntities);
    void spawnMissile(Registry &r, EngineComponent::Singletons &singletons, std::size_t indexPlayer, bool shootStyle);
    void spawnEnemies(Registry &r, EngineComponent::Singletons &singletons, std::size_t indexPlayer);
    void setMissilePosition(Registry &r, std::size_t indexPlayer, std::size_t indexMissile);
};