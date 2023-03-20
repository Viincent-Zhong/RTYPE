/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Draw
*/

#include "DrawC.hpp"
#include "GameplayC.hpp"
#include "Element/Element.hpp"
#include "DrawSystems.hpp"
#include "Singletons.hpp"
#include "TextureCache.hpp"
#include "ClientTCPSingletons.hpp"
#include "Queue.hpp"

namespace System {
    /**
     * @brief 
     * General handling for Drawind System
     * 
     * @param r 
     * @param singletons 
     */
    void drawSystem(Registry &r, EngineComponent::Singletons &singletons)
    {
        auto const &positions = r.getComponents<EngineComponent::Position>();
        auto const &drawable = r.getComponents<EngineComponent::Drawable>();
        auto const &spritesheet = r.getComponents<EngineComponent::SpriteSheet>();
        auto const &layers = r.getComponents<EngineComponent::Layer>();

        for (size_t i = 0; i < positions.size() && i < drawable.size() && i < spritesheet.size() && i < layers.size(); ++i) {
            auto const &pos = positions[i];
            auto const &drw = drawable[i];
            auto const &layer = layers[i];

            if (pos && drw && drw.value().isDrawable && layer && (layer.value().layer == 0 ||
            layer.value().layer == singletons.getSingleton<std::size_t>(EngineClient::TCP::SingletonEnum::LAYER))) {
                auto const &ss = spritesheet[i];
                if (ss && ss.value().isAnimated) {
                    r.textureCache.drawTextureRec<Element>(drw.value().texture, pos.value().pos, ss.value().rec);
                } else {
                    r.textureCache.drawTexture<Element>(drw.value().texture, pos.value().pos);
                }
            }
        }
    }

    Draw::Draw()
    {
        _drawSystems.push_front(&drawSystem);
    }

    /**
     * @brief 
     * Run the Drawing system
     * 
     * @param r 
     * @param singletons 
     */
    void Draw::run(Registry &r, EngineComponent::Singletons &singletons)
    {
        for (auto it = _drawSystems.begin(); it != _drawSystems.end(); ++it)
            (*it)(r, singletons);
    }
};