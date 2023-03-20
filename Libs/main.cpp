/*
** EPITECH PROJECT, 2022
** R-TYPE
** File description:
** main.cpp
*/

#include "Lib.hpp"
#include "Interaction/Interaction.hpp"
#include "EngineComponents.hpp"

#include "Rendering.hpp"
#include "Physique.hpp"
#include "InputHandling.hpp"
#include "Systems.hpp"
#include "ESystems.hpp"

/**
 * @brief 
 * Load some Singletons
 * 
 * @param singletons 
 * @param lib 
 */
void loadSingletons(Component::Singletons &singletons, std::unique_ptr<PadaEngine::IGraphical> &lib)
{
    if (singletons.oneSecTimer.TimerDone())
        singletons.oneSecTimer.RestartTimer();
    singletons.oneSecTimer.UpdateTimer(singletons.deltaTime);

    singletons.windowSize = lib.get()->getWindowSize();
    singletons.deltaTime = lib.get()->getDeltaTime();
    singletons.fps = lib.get()->getFps();
}

/**
 * @brief 
 * Main Loop for the Game
 * 
 * @param systems 
 * @param r 
 * @param singletons 
 */
void gameLoop(EngineSystem::Systems &systems, Registry &r, Component::Singletons &singletons)
{
    systems.runSystem(r, singletons, EngineSystem::Systems::InputHandling);
    systems.runSystem(r, singletons, EngineSystem::Systems::Physique);
    systems.runSystem(r, singletons, EngineSystem::Systems::Rendering);

    System::moveBackgroundSystem(r);
    System::replaceEnemy(r);
}

/**
 * @brief 
 * Initialize all the needs of the Game
 * 
 * @param r 
 * @param singletons 
 * @param systems 
 */
void initGame(Registry &r, Component::Singletons &singletons, EngineSystem::Systems &systems)
{
    systems.setSystem<System::Rendering>(EngineSystem::Systems::Rendering);
    systems.setSystem<System::Physique>(EngineSystem::Systems::Physique);
    systems.setSystem<System::InputHandling>(EngineSystem::Systems::InputHandling);

    EngineComponent::registerEngineComponents(r);
    singletons.initEntities.addEntitiesFromCSV(r, Entity::BackgroundInit);
    std::vector<std::size_t> ids = singletons.initEntities.addEntitiesFromCSV(r, Entity::PlayerInit);
    singletons.initEntities.addEntityFromJSON(r, Entity::EnemyInit, "Enemy1");
}

// int main(void)
// {
//     std::unique_ptr<PadaEngine::IGraphical> lib (new Lib(1920, 1000, 60, "Pada Engine"));
//     Registry r;
//     // Component::Singletons singletons = {std::unique_ptr<PadaEngine::Iinteraction>(new Interaction)};
//     Component::Singletons singletons;
//     EngineSystem::Systems systems;

//     lib->openWindow();
//     initGame(r, singletons, systems);
//     while (!lib->hasCloseWindow()) {
//         lib->startDrawing();
//         lib->clearWindow(RAYWHITE);
//         loadSingletons(singletons, lib);
//         gameLoop(systems, r, singletons);
//         lib->endDrawing();
//     }
//     return 0;
// }
