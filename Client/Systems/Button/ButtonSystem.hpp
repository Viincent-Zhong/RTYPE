/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Button
*/

#pragma once

#include "ISystem.hpp"

namespace System {
    class Button : public EngineSystem::ISystem {
        public:
            Button();
            ~Button() {};
            void run(Registry &r, EngineComponent::Singletons &singletons);
        private:
            std::list<EngineSystem::systemFunc> _buttonSystems;
    };
}