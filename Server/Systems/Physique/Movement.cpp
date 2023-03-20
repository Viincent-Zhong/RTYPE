/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Position
*/

#include "EComponents.hpp"
#include "Registry.hpp"
#include "Singletons.hpp"
#include "Serialization.hpp"
#include "UDPSingletons.hpp"
#include "DataStructure.hpp"
#include "logicGameServer.hpp"

/**
 * @brief 
 * Kill entities if they go off screen
 * 
 * @param r 
 * @param singletons 
 */
void outOfBoundSystem(Registry &r, EngineComponent::Singletons &singletons)
{
    auto const &positions = r.getComponents<EngineComponent::Position>();
    auto const &factions = r.getComponents<EngineComponent::Faction>();

    for (size_t i = 0; i < positions.size() && i < factions.size(); ++i) {
        auto const &pos = positions[i];
        auto const &fac = factions[i];

        // Comment below lines for dodging crash on Mac
        if (pos && pos.value().isOutOfBoundable && fac && fac.value().faction == EngineEntity::Ally
        && pos.value().pos.x > singletons.getSingleton<std::pair<unsigned int, unsigned int>>(EngineServer::UDP::SingletonsEnum::WINDOW_SIZE).second) {
            r.killEntity(i);
            sendKill(r, singletons, i);
        }
    }
}

/**
 * @brief 
 * Cancel collision if there is any to allow movement
 * 
 * @param move 
 * @param colDir 
 * @param dir 
 */
static void cancelCollision(std::pair<bool&, bool&> move, std::pair<std::size_t, std::size_t> const &colDir,
std::pair<float, float> const &dir)
{
    // lr 1 2 | left right
    // ud 1 2 | up down
    if (colDir.first == 1 && dir.first < 0)
        move.first = false;
    if (colDir.first == 2 && dir.first > 0)
        move.first = false;
    if (colDir.second == 1 && dir.second < 0)
        move.second = false;
    if (colDir.second == 2 && dir.second > 0)
        move.second = false;
}

/**
 * @brief 
 * Try to move to a direction,
 * verifie if movement is posible by checking if there is any collision
 * 
 * @param r 
 * @param singletons 
 */
void moveSystem(Registry &r, EngineComponent::Singletons &singletons)
{
    auto &positions = r.getComponents<EngineComponent::Position>();
    auto const &velocities = r.getComponents<EngineComponent::Direction>();
    auto &collisions = r.getComponents<EngineComponent::Collision>();
    EngineUtils::DeltaTime &deltaTime = singletons.getSingleton<EngineUtils::DeltaTime>(EngineServer::UDP::DELTA_TIME);
    
    for (size_t i = 0; i < positions.size() && i < velocities.size(); ++i) {
        auto &pos = positions[i];
        auto const &vel = velocities[i];

        if (pos && vel) {
            bool moveX = true;
            bool moveY = true;

            if (i < collisions.size()) {
                auto &col = collisions[i];
                if (col && col.value().hasCollided)
                    cancelCollision({moveX, moveY}, {col.value().lr, col.value().ud},
                    {vel.value().xDirection, vel.value().yDirection});
            }
            if (moveX)
                pos.value().pos.x += vel.value().xDirection * (deltaTime.getDeltaTime());
            else
                pos.value().pos.x -= vel.value().xDirection * (deltaTime.getDeltaTime());
            if (moveY)
                pos.value().pos.y += vel.value().yDirection * (deltaTime.getDeltaTime());
            else
                pos.value().pos.y -= vel.value().yDirection * (deltaTime.getDeltaTime());
        }
    }
}