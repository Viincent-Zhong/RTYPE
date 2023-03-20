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
#include "ClientUDPSingletons.hpp"

/**
 * @brief 
 * Determine collision between which type. Ally / Enemy / Bonus / Obstacle
 * 
 * @param r 
 * @param singletons 
 * @param ids 
 * @param factions 
 * @param pos 
 * @return true 
 * @return false 
 */
static bool determineCollisionType(Registry &r, EngineComponent::Singletons &singletons, std::pair<size_t, size_t> ids,
std::pair<EngineComponent::Faction, EngineComponent::Faction> const &factions, PadaEngine::Position const &pos)
{
    if ((factions.first.faction == EngineEntity::Ally && factions.second.faction == EngineEntity::Enemy)
    || (factions.second.faction == EngineEntity::Ally && factions.first.faction == EngineEntity::Enemy)) {
        return false;
    } else if ((factions.first.faction == EngineEntity::Ally && factions.second.faction == EngineEntity::Bonus)
    || (factions.second.faction == EngineEntity::Ally && factions.first.faction == EngineEntity::Bonus)) {
        return false;
    } else if ((factions.first.faction == EngineEntity::Ally && factions.second.faction == EngineEntity::Obstacle)
    || (factions.second.faction == EngineEntity::Ally && factions.first.faction == EngineEntity::Obstacle)) {
        return true;
    }
    return false;
}

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