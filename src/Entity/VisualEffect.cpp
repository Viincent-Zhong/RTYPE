/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** VisualEffect
*/

#include <cstdlib>
#include "VisualEffect.hpp"
#include "DrawC.hpp"
#include "GameplayC.hpp"

namespace Entity {
    VisualEffect::VisualEffect()
    {
    }

    VisualEffect::~VisualEffect()
    {
    }

    VisualEffect::VisualEffect(std::string const &file)
    {
        _content = EngineUtils::CSV::readCSV(file);
    }

    /**
     * @brief 
     * Set VisualEffects from a CSV file
     * 
     * @param r 
     * @param file 
     * @return std::vector<std::size_t> 
     */
    std::vector<std::size_t> VisualEffect::addEntitiesFromCSV(Registry &r, std::string const &file)
    {
        std::vector<std::size_t> ids;

        if (_content.size() == 0)
            _content = EngineUtils::CSV::readCSV(file);
        for (auto it : _content) {
            std::size_t id = r.spawnEntity();
            ids.push_back(id);
            r.addComponent<EngineComponent::Position>(id, {{(float)std::atoi(it.at(0).c_str()), (float)std::atoi(it.at(1).c_str())}}); // 0 1 | posX posY
            r.addComponent<EngineComponent::Drawable>(id, {std::atoi(it.at(3).c_str()) == 0 ? false : true, it.at(2)}); // 3 2 | isDrawable Texture
            r.addComponent<EngineComponent::SpriteSheet>(id, {true,
            {(float)std::atoi(it.at(4).c_str()), (float)std::atoi(it.at(5).c_str()), (float)std::atoi(it.at(6).c_str()), (float)std::atoi(it.at(7).c_str())}, // 4 5 6 7 | recX recY recWidth recHeigth
            (float)std::atoi(it.at(8).c_str()), (float)std::atoi(it.at(9).c_str()), // 8 9 | framespeedX framespeedY
            (float)std::atoi(it.at(4).c_str()), (float)std::atoi(it.at(5).c_str()), // 4 5 | starpointX starpointY
            (float)std::atoi(it.at(10).c_str())}); // 10 | frameMax
            r.addComponent<EngineComponent::EffectName>(id, {it.at(11)});
        }
        return ids;
    }

    /**
     * @brief 
     * Create VisualEffects based on previous data
     * 
     * @param r 
     * @return std::vector<std::size_t> 
     */
    std::vector<std::size_t> VisualEffect::addEntitiesFromCSV(Registry &r)
    {
        std::vector<std::size_t> ids;

        for (auto it : _content) {
            std::size_t id = r.spawnEntity();
            ids.push_back(id);
            r.addComponent<EngineComponent::Position>(id, {{(float)std::atoi(it.at(0).c_str()), (float)std::atoi(it.at(1).c_str())}}); // 0 1 | posX posY
            r.addComponent<EngineComponent::Drawable>(id, {std::atoi(it.at(3).c_str()) == 0 ? false : true, it.at(2)}); // 3 2 | isDrawable Texture
            r.addComponent<EngineComponent::SpriteSheet>(id, {true,
            {(float)std::atoi(it.at(4).c_str()), (float)std::atoi(it.at(5).c_str()), (float)std::atoi(it.at(6).c_str()), (float)std::atoi(it.at(7).c_str())}, // 4 5 6 7 | recX recY recWidth recHeigth
            (float)std::atoi(it.at(8).c_str()), (float)std::atoi(it.at(9).c_str()), // 8 9 | framespeedX framespeedY
            (float)std::atoi(it.at(4).c_str()), (float)std::atoi(it.at(5).c_str()), // 4 5 | starpointX starpointY
            (float)std::atoi(it.at(10).c_str())}); // 10 | frameMax
            r.addComponent<EngineComponent::EffectName>(id, {it.at(11)});
        }
        return ids;
    }

    std::size_t VisualEffect::addEntityFromJSON(Registry &r, std::string const &name)
    {
        return std::size_t();
    }
    std::size_t VisualEffect::addEntityFromJSON(Registry &r, std::string const &file, std::string const &name)
    {
        return std::size_t();
    }
};
