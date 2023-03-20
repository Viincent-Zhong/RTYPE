/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** VisualEffect
*/

#pragma once

#include "ISystem.hpp"

namespace System {
    class VisualEffect : public EngineSystem::ISystem {
        public:
            VisualEffect();
            ~VisualEffect() {};
            void run(Registry &r, EngineComponent::Singletons &singletons);
        private:
            std::list<EngineSystem::systemFunc> _visualEffectSystems;
    };
}
