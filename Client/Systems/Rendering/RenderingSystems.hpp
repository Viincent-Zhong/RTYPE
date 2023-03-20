/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Rendering
*/

#pragma once

#include "ISystem.hpp"

namespace System {
    class Rendering : public EngineSystem::ISystem {
        public:
            Rendering();
            ~Rendering() {};
            void run(Registry &r, EngineComponent::Singletons &singletons);
        private:
            std::list<EngineSystem::systemFunc> _renderingSystems;
    };
}