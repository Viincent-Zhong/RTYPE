/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Fonts
*/

#include <sstream>
#include <cstdlib>
#include "Fonts.hpp"
#include "DrawC.hpp"
#include "GameplayC.hpp"

namespace Entity {
    Fonts::Fonts()
    {
    }

    Fonts::~Fonts()
    {
    }

    Fonts::Fonts(std::string const &file)
    {
        _content = EngineUtils::CSV::readCSV(file);
    }

    /**
     * @brief 
     * Set Fonts from a CSV file
     * 
     * @param r 
     * @param file 
     * @return std::vector<std::size_t> 
     */
    std::vector<std::size_t> Fonts::addEntitiesFromCSV(Registry &r, std::string const &file)
    {
        std::vector<std::size_t> ids;

        if (_content.size() == 0)
            _content = EngineUtils::CSV::readCSV(file);
        for (auto it : _content) {
            std::size_t id = r.spawnEntity();
            ids.push_back(id);
            r.addComponent<EngineComponent::FontName>(id, {it.at(0)}); // 0 | font
        }
        return ids;
    }

    /**
     * @brief 
     * Create Fonts based on previous data
     * 
     * @param r 
     * @return std::vector<std::size_t> 
     */
    std::vector<std::size_t> Fonts::addEntitiesFromCSV(Registry &r)
    {
        std::vector<std::size_t> ids;

        for (auto it : _content) {
            std::size_t id = r.spawnEntity();
            ids.push_back(id);
            r.addComponent<EngineComponent::FontName>(id, {it.at(0)}); // 0 | font
        }
        return ids;
    }

    std::size_t Fonts::addEntityFromJSON(Registry &r, std::string const &name)
    {
        return std::size_t();
    }
    std::size_t Fonts::addEntityFromJSON(Registry &r, std::string const &file, std::string const &name)
    {
        return std::size_t();
    }
};