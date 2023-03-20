/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Playable
*/

#include <string>
#include "ClientUDPSingletons.hpp"
#include "GameplayC.hpp"
#include "DrawC.hpp"
#include "EntityGeneration.hpp"
#include "Interaction/Interaction.hpp"

/**
 * @brief 
 * Input handling, player movement and fire when key is downed or released (up / down / left / right arrow and space key)
 * @param r 
 * @param singletons 
 */
void controlSystem(Registry &r, Component::Singletons &singletons) {
    auto const &controllables = r.getComponents<EngineComponent::Controllable>();
    auto &velocities = r.getComponents<EngineComponent::Direction>();
    Interaction key;

    if (singletons.layer != 2)
        return;
    for (size_t i = 0; i < controllables.size() && i < velocities.size(); ++i) {
        auto const &con = controllables[i];
        auto &vel = velocities[i];

        if (con && vel && con.value().controllable) {
            vel.value().xDirection = 0;
            vel.value().yDirection = 0;
            if (key.isKeyDowned(EngineComponent::KEY_VALUE::ARROW_LEFT)) {
                // singletons.inputDowned == EngineComponent::KEY_VALUE::ARROW_LEFT;
                vel.value().xDirection -= 6;
            }
            if (key.isKeyDowned(EngineComponent::KEY_VALUE::ARROW_RIGHT)) {
                // singletons.inputDowned == EngineComponent::KEY_VALUE::ARROW_RIGHT;
                vel.value().xDirection += 6;
            }
            if (key.isKeyDowned(EngineComponent::KEY_VALUE::ARROW_UP)) {
                // singletons.inputDowned == EngineComponent::KEY_VALUE::ARROW_UP;
                vel.value().yDirection -= 3;
            }
            if (key.isKeyDowned(EngineComponent::KEY_VALUE::ARROW_DOWN)) {
                // singletons.inputDowned == EngineComponent::KEY_VALUE::ARROW_DOWN;
                vel.value().yDirection += 3;
            }
            if (key.isKeyDowned(EngineComponent::KEY_VALUE::SPACE)) {
                // singletons.inputDowned = EngineComponent::KEY_VALUE::SPACE;
                System::chargeMissile(r, singletons, i); // Start the missile timer
            }
            if (key.isKeyReleased(EngineComponent::KEY_VALUE::SPACE)) {
                System::spawnMissile(r, singletons, i, singletons.initEntities); // update missile timer
            }
            if (key.isKeyReleased(EngineComponent::KEY_VALUE::B)) {
                System::spawnAuxiliaries(r, i, "ball", singletons.initEntities); // Spawn allies (auxiliaries)
            }
        }
    }
}
