/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Auxiliaries
*/

#include "DrawC.hpp"
#include "GameplayC.hpp"
#include "ServerGame.hpp"
#include "EntityCache.hpp"

namespace System {
    /**
     * @brief 
     * Spawn an Auxiliary for the player (little bonus)
     * 
     * @param r 
     * @param indexPlayer 
     * @param aux 
     * @param initEntities 
     */
    void spawnAuxiliaries(Registry &r, std::size_t indexPlayer, std::string const &aux, EngineEntity::EntityCache &initEntities)
    {
        auto &positions = r.getComponents<EngineComponent::Position>();
        auto &factions = r.getComponents<EngineComponent::Faction>();
        auto &attached = r.getComponents<EngineComponent::AttachedID>();

        if (indexPlayer < positions.size() && indexPlayer < factions.size()) {
            std::size_t id;

            id = initEntities.addEntityFromJSON(r, EngineServer::Init::IAUXILIARY, aux);
            if (!(id < positions.size() && id < factions.size() && id < attached.size()))
                return;
            // Set auxiliary to player position
            auto const &pos = positions[indexPlayer];
            auto &aPos = positions[id];
            if (aPos && pos) {
                aPos.value().pos.x += pos.value().pos.x;
                aPos.value().pos.y += pos.value().pos.y;
            }
            // Set auxiliary faction to player
            auto &aFac = factions[id];
            auto const &fac = factions[indexPlayer];
            if (aFac && fac)
                aFac.value().faction = fac.value().faction;
            // Set player as this auxiliary parent
            auto &parentID = attached[id];
            if (parentID)
                parentID.value().parentID = indexPlayer;
        }
    }
};
