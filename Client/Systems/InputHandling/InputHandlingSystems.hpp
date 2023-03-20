/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** InputHandling
*/

#pragma once

#include "ISystem.hpp"

namespace System {
    class InputHandling : public EngineSystem::ISystem {
        public:
            InputHandling();
            ~InputHandling() {};
            void run(Registry &r, Component::Singletons &singletons);
        private:
            std::list<EngineSystem::systemFunc> _inputHandlingSystems;
    };
}

void controlSystem(Registry &r, Component::Singletons &singletons);