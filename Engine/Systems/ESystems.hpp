/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Systems
*/

#pragma once

#include "ISystem.hpp"
#include "Registry.hpp"
#include "Singletons.hpp"

namespace EngineSystem {
    class Systems {
        public:
            Systems();
            ~Systems();


            void runSystem(Registry &r, EngineComponent::Singletons &singletons, int type);

            template <class T, class ... Params>
            void setSystem(int type, Params &&...params)
            {
                auto sys = _systems.find(type);

                if (sys == _systems.end()) {
                    _systems.insert({type, std::unique_ptr<EngineSystem::ISystem>(new T(params...))});
                } else {
                    sys->second.reset(new T);
                }
            }

        private:
            std::unordered_map<int, std::unique_ptr<EngineSystem::ISystem>> _systems;
    };
}