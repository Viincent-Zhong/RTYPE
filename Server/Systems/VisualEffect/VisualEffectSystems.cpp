/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** VisualEffect
*/

#include "DrawC.hpp"
#include "GameplayC.hpp"
#include "Element/Element.hpp"
#include "VisualEffectSystems.hpp"
#include "Utils.hpp"

namespace System {

    /**
     * @brief structure avec les information sur un type de particules à afficher
     * 
     */
    struct EffectExplosion {
        EngineComponent::SpriteSheet sprite;
        PadaEngine::Position pos;
        std::string texture;
    };
    /**
     * @brief vecteur avec toutes les particules d'un type a afficher
     * 
     */
    std::vector<EffectExplosion> explosions;

    /**
     * @brief 
     * One Visual Effect that produce an explosion, Server-side
     * 
     * @param singletons 
     * @param texture 
     * @param pad 
     */
    void explosionEffect(EngineComponent::Singletons &singletons, std::string const &texture, EngineComponent::SpriteSheet const &pad)
    {
        // for (auto const &pos : singletons.explosionPos)
            // explosions.push_back({pad, pos, texture});
        for (int j = 0; j != explosions.size(); ++j) {
            if (!explosions.at(j).sprite.isAnimated)
                continue;
            explosions.at(j).sprite.rec.x += explosions.at(j).sprite.xFrameSpeed;
            explosions.at(j).sprite.rec.y += explosions.at(j).sprite.yFrameSpeed;
            if (explosions.at(j).sprite.rec.x > explosions.at(j).sprite.frameMax || explosions.at(j).sprite.rec.y > explosions.at(j).sprite.frameMax) {
                // animation terminée, supprime l'animation
                explosions.erase(explosions.begin() + j);
                --j;
                continue;
            }
            // singletons.tCache.drawTextureRec<Element>(explosions.at(j).texture, {explosions.at(j).pos.x, explosions.at(j).pos.y}, explosions.at(j).sprite.rec);
        }
        // vide les explosions actuelle pour éviter de les afficher plusieurs fois
        // singletons.explosionPos.clear();
    }

    /**
     * @brief 
     * Handle all the Visual Effect, Server-side
     * 
     * @param r 
     * @param singletons 
     */
    void visualEffectSystem(Registry &r, EngineComponent::Singletons &singletons)
    {
        auto &recs = r.getComponents<EngineComponent::SpriteSheet>();
        auto const &files = r.getComponents<EngineComponent::Drawable>();
        auto const &effectNames = r.getComponents<EngineComponent::EffectName>();

        for (size_t i = 0; i < recs.size() && i < effectNames.size() && i < files.size(); ++i) {
            auto &rec = recs[i];
            auto const &effectName = effectNames[i];
            auto const &file = files[i];
            if (rec && effectName && file) {
                if (effectName.value().name == "basicExplosion")
                    explosionEffect(singletons, file.value().texture, rec.value());
            }
        }
    }

    VisualEffect::VisualEffect()
    {
        _visualEffectSystems.push_front(&visualEffectSystem);
    }

    /**
     * @brief 
     * Run the Visual Effect system, Server-side
     * 
     * @param r 
     * @param singletons 
     */
    void VisualEffect::run(Registry &r, EngineComponent::Singletons &singletons)
    {
        for (auto it = _visualEffectSystems.begin(); it != _visualEffectSystems.end(); ++it)
            (*it)(r, singletons);
    }
};