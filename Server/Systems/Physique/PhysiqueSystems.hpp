/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Physique
*/

#pragma once

#include "ISystem.hpp"

namespace System {
    class Physique : public EngineSystem::ISystem{
        public:
            Physique();
            ~Physique() {};
            void run(Registry &r, EngineComponent::Singletons &singletons);
        private:
            std::list<EngineSystem::systemFunc> _physiqueSystems;
    };
};

void collisionSystem(Registry &r, EngineComponent::Singletons &singletons);
void moveSystem(Registry &r, EngineComponent::Singletons &singletons);

/** @brief Destroy out of bound entities
 */
void outOfBoundSystem(Registry &r, EngineComponent::Singletons &singletons);
