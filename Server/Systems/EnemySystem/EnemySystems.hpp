/*
** EPITECH PROJECT, 2022
** Project R-TYPE
** File description:
** BackgroundSystems
*/

#pragma once

#include "ISystem.hpp"

namespace System {
    class Enemy : public EngineSystem::ISystem {
        public:
            Enemy();
            ~Enemy() {};
            void run(Registry &r, EngineComponent::Singletons &singletons);
        private:
            std::list<EngineSystem::systemFunc> _EnemySystems;
    };
}