/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** UpdateClientsData
*/

#pragma once

#include "ISystem.hpp"

namespace System {
    class Network : public EngineSystem::ISystem {
        public:
            Network();
            ~Network() {};
            void run(Registry &r, EngineComponent::Singletons &singletons);

        private:
            std::list<EngineSystem::systemFunc> _networkSystems;
    };
};
