/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Missile
*/

#include "DrawC.hpp"
#include "GameplayC.hpp"
#include "ServerGame.hpp"
#include "EntityCache.hpp"
#include "UDPSingletons.hpp"
#include "logicGameServer.hpp"

namespace System {

    /**
     * @brief 
     * Set the Missile Position object for the Server
     * 
     * @param r 
     * @param indexPlayer 
     * @param indexMissile 
     */
    void setMissilePosition(Registry &r, std::size_t indexPlayer, std::size_t indexMissile)
    {
        auto &positions = r.getComponents<EngineComponent::Position>();
        auto &factions = r.getComponents<EngineComponent::Faction>();
        auto const &animations = r.getComponents<EngineComponent::SpriteSheet>();

        if (!(indexMissile < positions.size() && indexMissile < factions.size()))
            return;
        auto const &pos = positions[indexPlayer];
        auto const &anim = animations[indexPlayer];
        auto &mPos = positions[indexMissile];
        auto &mAnim = animations[indexMissile];
        if (mPos && pos && anim && mAnim) {
            mPos.value().pos.x += pos.value().pos.x + (anim.value().rec.width / 2) - (mAnim.value().rec.width / 2);
            mPos.value().pos.y += pos.value().pos.y + (anim.value().rec.heigth / 2) - (mAnim.value().rec.heigth / 2);
        }
        // Set missile faction to player
        auto &mFac = factions[indexMissile];
        auto const &fac = factions[indexPlayer];
        if (mFac && fac)
            mFac.value().faction = fac.value().faction;
    }

    void spawnMissile(Registry &r, EngineComponent::Singletons &singletons, std::size_t indexPlayer, bool shootStyle)
    {
        auto &positions = r.getComponents<EngineComponent::Position>();
        auto &pstats = r.getComponents<EngineComponent::ProjectileStats>();

        if (indexPlayer < positions.size() && indexPlayer < pstats.size()) {
            std::size_t id;

            auto &stat = pstats[indexPlayer];
            if (!stat)
                return;

            if (shootStyle) // spawn strong missile
                id = r.entityCache.addEntityFromJSON(r, EngineServer::Init::IMISSILE, stat.value().strong);
            else // spawn normal missile
                id = r.entityCache.addEntityFromJSON(r, EngineServer::Init::IMISSILE, stat.value().normal);
            setMissilePosition(r, indexPlayer, id);
            sendEntity(id, r, singletons); // send to every clients the new missile
        }
    }
};
