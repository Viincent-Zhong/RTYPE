/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Collision
*/

#include "EComponents.hpp"
#include "Utils.hpp"
#include "Singletons.hpp"
#include "Registry.hpp"
#include "logicGameServer.hpp"

/**
 * @brief 
 * Calculate damage deals between ally and enemy, and destroy entity if it has no more hp
 * 
 * @param r 
 * @param ids 
 */
void hurtMeMore(Registry &r, EngineComponent::Singletons &singletons, std::pair<size_t, size_t> ids)
{
    auto &entity_hp = r.getComponents<EngineComponent::HP>();
    auto &entity_damage = r.getComponents<EngineComponent::HitDamage>();

    if (ids.first < entity_hp.size() && ids.first < entity_damage.size() && ids.second < entity_hp.size() && ids.second < entity_damage.size()) {
        auto &ally_hp = entity_hp[ids.first];
        auto const ally_damage = entity_damage[ids.first];

        auto const enemy_damage = entity_damage[ids.second];
        auto &enemy_hp = entity_hp[ids.second];

        if (enemy_hp && ally_damage && enemy_hp.value().hp >= ally_damage.value().dmg) {
            enemy_hp.value().hp = enemy_hp.value().hp - ally_damage.value().dmg;
        }
        if (ally_hp && enemy_damage && ally_hp.value().hp >= enemy_damage.value().dmg) {
            ally_hp.value().hp = ally_hp.value().hp - enemy_damage.value().dmg;
        }
        if (ally_hp && enemy_damage && ally_hp.value().hp <= enemy_damage.value().dmg) {
            r.killEntity(ids.first);
            sendKill(r, singletons, ids.first);
        }
        if (enemy_hp && ally_damage && enemy_hp.value().hp <= ally_damage.value().dmg) {
            r.killEntity(ids.second);
            sendKill(r, singletons, ids.second);
        }
    }
}

/**
 * @brief 
 * Determine collision between wich type. Ally / Enemy / Bonus / Obstacle
 * @param r 
 * @param ids 
 * @param factions 
 * @return true 
 * @return false 
 */
static bool determineCollisionType(Registry &r, EngineComponent::Singletons &singletons, std::pair<size_t, size_t> ids,
std::pair<EngineComponent::Faction, EngineComponent::Faction> const &factions, PadaEngine::Position const &pos)
{
    if ((factions.first.faction == EngineEntity::Ally && factions.second.faction == EngineEntity::Enemy)
    || (factions.second.faction == EngineEntity::Ally && factions.first.faction == EngineEntity::Enemy)) {
        hurtMeMore(r, singletons, ids);
        sendEntity(ids.first, r, singletons);
        sendEntity(ids.second, r, singletons);
        return false;
    } else if ((factions.first.faction == EngineEntity::Ally && factions.second.faction == EngineEntity::Bonus)
    || (factions.second.faction == EngineEntity::Ally && factions.first.faction == EngineEntity::Bonus)) {
        return false;
    } else if ((factions.first.faction == EngineEntity::Ally && factions.second.faction == EngineEntity::Obstacle)
    || (factions.second.faction == EngineEntity::Ally && factions.first.faction == EngineEntity::Obstacle)) {
        sendEntity(ids.first, r, singletons);
        sendEntity(ids.second, r, singletons);
        return true;
    }
    return false;
}

/**
 * @brief 
 * Set the Superior object
 * 
 * @param one 
 * @param two 
 * @param condition 
 */
static void setSuperior(std::size_t &one, std::size_t &two, bool condition)
{
    if (condition) {
        one = 1;
        two = 2;
    } else {
        one = 2;
        two = 1;
    }
}

/**
 * @brief 
 * Check if there is a collision by comparing position, Rectangle (hitbox), Faction (if same faction there is no collision)
 * @param r 
 * @param singletons 
 */
void collisionSystem(Registry &r, EngineComponent::Singletons &singletons)
{
    auto const &positions = r.getComponents<EngineComponent::Position>();
    auto const &factions = r.getComponents<EngineComponent::Faction>();
    auto &spritesheet = r.getComponents<EngineComponent::SpriteSheet>();
    auto &collisions = r.getComponents<EngineComponent::Collision>();

    for (size_t i = 0; i < positions.size() && i < factions.size() && i < spritesheet.size()
    && i < collisions.size(); ++i) {
        auto const &pos1 = positions[i];
        auto const &fac1 = factions[i];
        auto &rec1 = spritesheet[i];
        auto &col1 = collisions[i];
        if (!pos1 || !fac1 || !rec1 || !col1)
            continue;
        // Found i rec, looking for j rec
        for (size_t j = i + 1; rec1 && col1 && pos1 && fac1 && j < positions.size() && j < factions.size() && j < spritesheet.size()
        && j < collisions.size(); ++j) {
            auto const &pos2 = positions[j];
            auto const &fac2 = factions[j];
            auto &rec2 = spritesheet[j];
            auto &col2 = collisions[j];
            if (!pos2 || !fac2 || !rec2 || !col2)
                continue;
            if (EngineUtils::collisionBetweenRec(
            {pos1.value().pos, rec1.value().rec},{pos2.value().pos, rec2.value().rec})
            && determineCollisionType(r, singletons, {i, j}, {fac1.value(), fac2.value()}, pos2.value().pos)) {
                if (col1 && col2) {
                    // singletons.explosionPos.push_back({pos2.value().pos});
                    col1.value().hasCollided = true;
                    col2.value().hasCollided = true;
                    setSuperior(col1.value().lr, col2.value().lr, pos1.value().pos.x > pos2.value().pos.x);
                    setSuperior(col1.value().ud, col2.value().ud, pos1.value().pos.y > pos2.value().pos.y);
                }
                break;
            } else {
                if (col1 && col2) {
                    col1.value().hasCollided = false;
                    col2.value().hasCollided = false;
                    col1.value().lr = 0;
                    col2.value().lr = 0;
                    col1.value().ud = 0;
                    col2.value().ud = 0;
                }
            }
        }
    }
}