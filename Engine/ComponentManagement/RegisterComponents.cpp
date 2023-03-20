/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** RegisterComponents
*/

#include "Registry.hpp"
#include "DrawC.hpp"
#include "GameplayC.hpp"

/**
 * @brief 
 * Register all the Components of the engine
 * 
 */
namespace EngineComponent {
    void registerEngineComponents(Registry &r)
    {
        r.registerComponent<Position>();
        r.registerComponent<Drawable>();
        r.registerComponent<SpriteSheet>();
        r.registerComponent<Layer>();
        r.registerComponent<Mouseover>();
        r.registerComponent<Controllable>();
        r.registerComponent<Direction>();
        r.registerComponent<HP>();
        r.registerComponent<HitDamage>();
        r.registerComponent<ProjectileStats>();
        r.registerComponent<Faction>();
        r.registerComponent<Bonus>();
        r.registerComponent<Collision>();
        r.registerComponent<IP>();
        r.registerComponent<Interactible>();
        r.registerComponent<IA>();
        r.registerComponent<WalkAnimation>();
        r.registerComponent<AttachedID>();
        r.registerComponent<Slide>();
        r.registerComponent<FunctionName>();
        r.registerComponent<SoundEffect>();
        r.registerComponent<EffectName>();
        r.registerComponent<ListGame>();
        r.registerComponent<RoomPlayer>();
        r.registerComponent<FontName>();
    }
}
