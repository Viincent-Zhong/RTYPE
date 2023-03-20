/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Draw
*/

#pragma once

#include "ISystem.hpp"
#include "Singletons.hpp"

namespace System {
    class Draw : public EngineSystem::ISystem {
        public:
            Draw();
            ~Draw() {};
            void run(Registry &r, EngineComponent::Singletons &singletons);
        private:
            std::list<EngineSystem::systemFunc> _drawSystems;
    };
}