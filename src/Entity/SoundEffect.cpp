/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** SoundEffect
*/

#include <cstdlib>
#include "SoundEffect.hpp"
#include "DrawC.hpp"
#include "GameplayC.hpp"

namespace Entity {
    SoundEffect::SoundEffect()
    {
    }

    SoundEffect::~SoundEffect()
    {
    }

    SoundEffect::SoundEffect(std::string const &file)
    {
        _content = EngineUtils::CSV::readCSV(file);
    }

    /**
     * @brief 
     * Set SoundEffects from a CSV file
     * 
     * @param r 
     * @param file 
     * @return std::vector<std::size_t> 
     */
    std::vector<std::size_t> SoundEffect::addEntitiesFromCSV(Registry &r, std::string const &file)
    {
        std::vector<std::size_t> ids;

        if (_content.size() == 0)
            _content = EngineUtils::CSV::readCSV(file);
        for (auto it : _content) {
            std::size_t id = r.spawnEntity();
            ids.push_back(id);
            r.addComponent<EngineComponent::SoundEffect>(id, {it.at(0), std::atoi(it.at(1).c_str())});
            r.addComponent<EngineComponent::EffectName>(id,{it.at(2)});
        }
        return ids;
    }

    /**
     * @brief 
     * Create SoundEffects based on previous data
     * 
     * @param r 
     * @return std::vector<std::size_t> 
     */
    std::vector<std::size_t> SoundEffect::addEntitiesFromCSV(Registry &r)
    {
        std::vector<std::size_t> ids;

        for (auto it : _content) {
            std::size_t id = r.spawnEntity();
            ids.push_back(id);
            r.addComponent<EngineComponent::SoundEffect>(id, {it.at(0), std::atoi(it.at(1).c_str())});
        }
        return ids;
    }

    std::size_t SoundEffect::addEntityFromJSON(Registry &r, std::string const &name)
    {
        return std::size_t();
    }
    std::size_t SoundEffect::addEntityFromJSON(Registry &r, std::string const &file, std::string const &name)
    {
        return std::size_t();
    }
};