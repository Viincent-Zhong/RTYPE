/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** System
*/

#include "ESystems.hpp"

namespace EngineSystem {
    Systems::Systems()
    {
    }

    Systems::~Systems()
    {
    }

    /**
     * @brief 
     * Run all the systems from the ECS
     * 
     * @param r 
     * @param singletons 
     * @param type 
     */
    void Systems::runSystem(Registry &r, EngineComponent::Singletons &singletons, int type)
    {
        auto sys = _systems.find(type);

        if (sys != _systems.end())
            sys->second.get()->run(r, singletons);
    }
};