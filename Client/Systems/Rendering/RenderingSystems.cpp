/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Rendering
*/

#include "DrawC.hpp"
#include "GameplayC.hpp"
#include "Element/Element.hpp"
#include "RenderingSystems.hpp"
#include "ClientUDPSingletons.hpp"

namespace System {
    /**
     * @brief 
     * Animate an object by moving the rect in the spritesheet
     * 
     * @param r 
     * @param singletons 
     */
    void animationSystem(Registry &r, EngineComponent::Singletons &singletons)
    {
        if (singletons.getSingleton<EngineUtils::Timer>(EngineClient::UDP::SingletonsEnum::ONE_SEC_TIMER).TimerDone())
            return;
        auto &animated = r.getComponents<EngineComponent::SpriteSheet>();

        for (size_t i = 0; i < animated.size(); ++i) {
            auto &anim = animated[i];

            if (anim) {
                EngineComponent::SpriteSheet &spritesheet = anim.value();
                if (!spritesheet.isAnimated)
                    continue;
                spritesheet.rec.x += spritesheet.xFrameSpeed;
                spritesheet.rec.y += spritesheet.yFrameSpeed;
                if (spritesheet.rec.x > spritesheet.frameMax || spritesheet.rec.y > spritesheet.frameMax) {
                    spritesheet.rec.x = spritesheet.xStartPoint;
                    spritesheet.rec.y = spritesheet.yStartPoint;
                }
            }
        }
    }

    /**
     * @brief 
     * Move the rect in a spritesheet in a certain direction
     * 
     * @param r 
     * @param singletons 
     */
    void directionAnimationSystem(Registry &r, EngineComponent::Singletons &singletons)
    {
        auto const &directions = r.getComponents<EngineComponent::Direction>();
        auto &spritesheet = r.getComponents<EngineComponent::SpriteSheet>();
        auto const &walkAnimations = r.getComponents<EngineComponent::WalkAnimation>();

        for (size_t i = 0; i < directions.size() && i < spritesheet.size() && i < walkAnimations.size(); ++i) {
            auto const &dir = directions[i];
            auto &ss = spritesheet[i];
            auto const &wanim = walkAnimations[i];

            if (!(dir && ss && wanim))
                continue;
            size_t walkDirection = 0; // not moving by default

            if (dir.value().yDirection > 0)
                walkDirection = 4;
            else if (dir.value().yDirection < 0)
                walkDirection = 3;
            else if (dir.value().yDirection == 0 && dir.value().xDirection < 0)
                walkDirection = 1;
            else if (dir.value().yDirection == 0 && dir.value().xDirection > 0)
                walkDirection = 2;
            ss.value().rec.x = wanim.value().directionsAnimation.at(walkDirection).x;
            ss.value().rec.y = wanim.value().directionsAnimation.at(walkDirection).y;
        }
    }

    Rendering::Rendering()
    {
        _renderingSystems.push_front(&animationSystem);
        // _renderingSystems.push_front(&directionAnimationSystem);
    }

    /**
     * @brief 
     * Run the Rendering System for spritesheet
     * 
     * @param r 
     * @param singletons 
     */
    void Rendering::run(Registry &r, EngineComponent::Singletons &singletons)
    {
        for (auto it = _renderingSystems.begin(); it != _renderingSystems.end(); ++it)
            (*it)(r, singletons);
    }
};