/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** ISystem
*/

#pragma once

#include <functional>
#include "Registry.hpp"
#include "Singletons.hpp"

namespace EngineSystem {
    using systemFunc = std::function<void(Registry &, EngineComponent::Singletons &)>;
    class ISystem {
        public:
            virtual ~ISystem() = default;
            virtual void run(Registry &r, EngineComponent::Singletons &singletons) = 0;
    };
};
