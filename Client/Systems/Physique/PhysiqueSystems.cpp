/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Physique
*/

#include "PhysiqueSystems.hpp"

namespace System {
    Physique::Physique()
    {
        _physiqueSystems.push_front(&moveSystem);
        _physiqueSystems.push_front(&collisionSystem);
    }

    /**
     * @brief 
     * Run all the Physique System (Collision, Movement)
     * 
     * @param r 
     * @param singletons 
     */
    void Physique::run(Registry &r, EngineComponent::Singletons &singletons)
    {
        for (auto it = _physiqueSystems.begin(); it != _physiqueSystems.end(); ++it)
            (*it)(r, singletons);
    }
};
