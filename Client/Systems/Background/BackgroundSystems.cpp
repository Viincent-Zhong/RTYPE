/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** BackgroundSystems
*/

#include "BackgroundSystems.hpp"
#include "GameplayC.hpp"
#include "DrawC.hpp"

namespace System {

    /**
     * @brief 
     * Check if the image is out of the window,
     * if that the case then move the image to x = 1920 to continue the loop
     * 
     * @param r 
     * @param singletons 
     */
    void moveBackgroundSystem(Registry &r, EngineComponent::Singletons &singletons)
    {
        auto &pos = r.getComponents<EngineComponent::Position>();
        auto const &rect = r.getComponents<EngineComponent::SpriteSheet>();
        auto const &slidable = r.getComponents<EngineComponent::Slide>();
        
        for (size_t i = 0; i < pos.size() && i < rect.size() && i < slidable.size(); ++i) {
            auto &position = pos[i];
            auto const &rectangle = rect[i];
            auto const &slide = slidable[i];
            if (position && rectangle && slide) {
                EngineComponent::SpriteSheet const origin = rectangle.value();
                if (!slide && !slide.value().isSlidable)
                    continue;
                if (!position || position.value().pos.x < -origin.rec.width)
                    position.value().pos.x = origin.rec.width - 1;
            }
        }
    }
    
    Background::Background()
    {
        _backgroundSystems.push_front(&moveBackgroundSystem);
    }

    /**
     * @brief 
     * Run the background system for the client
     * 
     * @param r 
     * @param singletons 
     */
    void Background::run(Registry &r, EngineComponent::Singletons &singletons)
    {
        for (auto it = _backgroundSystems.begin(); it != _backgroundSystems.end(); ++it)
            (*it)(r, singletons);
    }
};