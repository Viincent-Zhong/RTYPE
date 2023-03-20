/*
** EPITECH PROJECT, 2022
** B-CPP-500-PAR-5-1-rtype-pierre-alexandre.delgado-arevalo
** File description:
** Enemy.cpp
*/

#include "DrawC.hpp"
#include "GameplayC.hpp"
#include "ServerGame.hpp"
#include "EntityCache.hpp"

namespace System {
    /**
     * @brief 
     * Spawn the enemies in the current wave 
     * 
     * @param r 
     * @param singletons 
     * @param indexPlayer 
     */
    void spawnEnemies(Registry &r, EngineComponent::Singletons &singletons, std::size_t indexPlayer)
    {
        auto &positions = r.getComponents<EngineComponent::Position>();
        auto &factions = r.getComponents<EngineComponent::Faction>();
        auto &pstats = r.getComponents<EngineComponent::ProjectileStats>();
        auto const &animations = r.getComponents<EngineComponent::SpriteSheet>();

        if (indexPlayer < positions.size() && indexPlayer < factions.size() && indexPlayer < pstats.size() && indexPlayer < animations.size()) {
            std::size_t id;
            auto &stat = pstats[indexPlayer];
            if (!stat)
                return;
            r.entityCache.addEntityFromJSON(r, EngineServer::Init::IENEMY, stat.value().basicEnemy);
        }
    }
};