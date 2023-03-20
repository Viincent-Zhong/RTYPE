/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** BackgroundSystems
*/

#pragma once

#include "ISystem.hpp"

namespace System {
    class Background : public EngineSystem::ISystem {
        public:
            Background();
            ~Background() {};
            void run(Registry &r, EngineComponent::Singletons &singletons);
        private:
            std::list<EngineSystem::systemFunc> _backgroundSystems;
    };
}