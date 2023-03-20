/*
** EPITECH PROJECT, 2022
** Project R-TYPE
** File description:
** EnemySystems.cpp
*/

#include "DrawC.hpp"
#include "GameplayC.hpp"
#include "EnemySystems.hpp"
#include "UDPSingletons.hpp"
#include "logicGameServer.hpp"

namespace System {

    /**
     * @brief 
     * Replace an enemy
     * 
     * @param r 
     * @param singletons 
     */
    void replaceEnemy(Registry &r, EngineComponent::Singletons &singletons)
    {
        auto &pos = r.getComponents<EngineComponent::Position>();
        auto const &rect = r.getComponents<EngineComponent::SpriteSheet>();
        auto const &type = r.getComponents<EngineComponent::Faction>();

        for (size_t i = 0; i < pos.size() && i < rect.size() && i < type.size(); ++i) {
            auto &position = pos[i];
            auto const &rectangle = rect[i];
            auto const &faction = type[i];
            if (position && rectangle && faction && faction.value().faction == EngineEntity::Enemy) {
                if (position.value().pos.x <= 0) {
                    position.value().pos.x = static_cast<float>(singletons.getSingleton<std::pair<unsigned int, unsigned int>>(EngineServer::UDP::SingletonsEnum::WINDOW_SIZE).first + 250.0);
                    // std::cout << "windows size: " << singletons.getSingleton<std::pair<unsigned int, unsigned int>>(EngineServer::UDP::SingletonsEnum::WINDOW_SIZE).first << " : " << singletons.getSingleton<std::pair<unsigned int, unsigned int>>(EngineServer::UDP::SingletonsEnum::WINDOW_SIZE).second << std::endl;
                    // position.value().pos.x = 500.0f;
                    sendEntity(i, r, singletons);
                }
            }
        }
    }

    /**
     * @brief 
     * Count all the enemies alive in the current wave
     * 
     * @param r 
     * @param singletons 
     */
    void countEnemy(Registry &r, EngineComponent::Singletons &singletons)
    {
        unsigned int nbr = 0;
        auto &pos = r.getComponents<EngineComponent::Position>();
        auto const &rect = r.getComponents<EngineComponent::SpriteSheet>();
        auto const &type = r.getComponents<EngineComponent::Faction>();

        for (size_t i = 0; i < pos.size() && i < rect.size() && i < type.size(); ++i) {
            auto &position = pos[i];
            auto const &rectangle = rect[i];
            auto const &faction = type[i];
            if (faction && faction.value().faction == EngineEntity::Enemy)
                ++nbr;
        }
        if (nbr == 0)
            singletons.getSingleton<bool>(EngineServer::UDP::SingletonsEnum::WAVER_OVER) = true;
        else
            singletons.getSingleton<bool>(EngineServer::UDP::SingletonsEnum::WAVER_OVER) = false;
    }

    Enemy::Enemy()
    {
        _EnemySystems.push_front(&replaceEnemy);
        _EnemySystems.push_front(&countEnemy);
    }

    /**
     * @brief 
     * Run the Enemy System
     * 
     * @param r 
     * @param singletons 
     */
    void Enemy::run(Registry &r, EngineComponent::Singletons &singletons)
    {
        for (auto it = _EnemySystems.begin(); it != _EnemySystems.end(); ++it)
            (*it)(r, singletons);
    }
};
