/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Button
*/

#include <cstdlib>
#include "Text.hpp"
#include "DrawC.hpp"
#include "GameplayC.hpp"

namespace Entity {

    Text::Text(std::string const &file)
    {
        _content = EngineUtils::CSV::readCSV(file);;
    }
    
    // Text::Text(std::string const &text, float x, float y)
    // {
    //     _content = EngineUtils::CSV::readCSV(file);
    // }

    /**
     * @brief 
     * Set Texts from a CSV file
     * 
     * @param r 
     * @param file 
     * @return std::vector<std::size_t> 
     */
    std::vector<std::size_t> Text::addEntitiesFromCSV(Registry &r, std::string const &file)
    {
        std::vector<std::size_t> ids;

        if (_content.size() == 0)
            _content = EngineUtils::CSV::readCSV(file);
        for (auto it : _content) {
            std::size_t id = r.spawnEntity();
            ids.push_back(id);
            r.addComponent<EngineComponent::Position>(id, {{(float)std::atoi(it.at(0).c_str()), (float)std::atoi(it.at(1).c_str())}}); // 0 1 | posX posY
            r.addComponent<EngineComponent::Drawable>(id, {std::atoi(it.at(2).c_str()) == 0 ? false : true, it.at(5)}); // 2 5 | isDrawable Content
            // r.addComponent<EngineComponent::ContentText>(id, it.at(5)); // 2 5 | isDrawable Content
        }
        return ids;
    }

    /**
     * @brief 
     * Create Texts based on previous data
     * 
     * @param r 
     * @return std::vector<std::size_t> 
     */
    std::vector<std::size_t> Text::addEntitiesFromCSV(Registry &r)
    {
        std::vector<std::size_t> ids;

        for (auto it : _content) {
            std::size_t id = r.spawnEntity();
            ids.push_back(id);
            r.addComponent<EngineComponent::Position>(id, {{(float)std::atoi(it.at(0).c_str()), (float)std::atoi(it.at(1).c_str())}}); // 0 1 | posX posY
            r.addComponent<EngineComponent::Drawable>(id, {std::atoi(it.at(3).c_str()) == 0 ? false : true, it.at(2)}); // 3 2 | isDrawable Texture
        }
        return ids;
    }

    std::size_t Text::addEntityFromJSON(Registry &r, std::string const &name)
    {
        return std::size_t();
    }

    std::size_t Text::addEntityFromJSON(Registry &r, std::string const &file, std::string const &name)
    {
        return std::size_t();
    }
};