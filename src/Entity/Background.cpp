/*
** EPITECH PROJECT, 2022
** B-CPP-500-PAR-5-1-rtype-pierre-alexandre.delgado-arevalo
** File description:
** Background.cpp
*/

#include <sstream>
#include "DrawC.hpp"
#include "Background.hpp"
#include "GameplayC.hpp"

namespace Entity {
    Background::Background()
    {
    }

    Background::Background(std::string const &file)
    {
        _content = EngineUtils::CSV::readCSV(file);
    }

    Background::~Background()
    {
    }

    /**
     * @brief 
     * Set Background from a CSV file
     * 
     * @param r 
     * @param file 
     * @return std::vector<std::size_t> 
     */
    std::vector<std::size_t> Background::addEntitiesFromCSV(Registry &r, std::string const &file)
    {
        _content = EngineUtils::CSV::readCSV(file);
        std::vector<std::size_t> ids;

        for (auto it : _content) {
            std::size_t id = r.spawnEntity();
            ids.push_back(id);    
            r.addComponent<EngineComponent::Position>(id, {{(float)std::atoi(it.at(0).c_str()), (float)std::atoi(it.at(1).c_str())}}); // 0 1 | posX posY
            r.addComponent<EngineComponent::SpriteSheet>(id, {true,
            {(float)std::atoi(it.at(3).c_str()), (float)std::atoi(it.at(4).c_str()), (float)std::atoi(it.at(5).c_str()), (float)std::atoi(it.at(6).c_str())}, // 2 3 4 5 | recX recY recWidth recHeigth
            0, 0, // framespeedX framespeedY
            0, 0, // starpointX starpointY
            1}); // frameMax
            r.addComponent<EngineComponent::Drawable>(id, {std::atoi(it.at(7).c_str()) == 0 ? false : true, it.at(2)}); // 6 | isDrawable
            r.addComponent<EngineComponent::Slide>(id, {std::atoi(it.at(8).c_str()) == 0 ? false : true}); // 7 | isSlidable
            r.addComponent<EngineComponent::Direction>(id, {-2, 0});
            std::stringstream sstream(it.at(9));
	        size_t result;
	        sstream >> result;
            r.addComponent<EngineComponent::Layer>(id, {result});
        }
        return ids;
    }

    /**
     * @brief 
     * Create Background based on previous data
     * 
     * @param r 
     * @return std::vector<std::size_t> 
     */
    std::vector<std::size_t> Background::addEntitiesFromCSV(Registry &r)
    {
        std::vector<std::size_t> ids;

        for (auto it : _content) {
            std::size_t id = r.spawnEntity();
            ids.push_back(id);    
            r.addComponent<EngineComponent::Position>(id, {{(float)std::atoi(it.at(0).c_str()), (float)std::atoi(it.at(1).c_str())}}); // 0 1 | posX posY
            r.addComponent<EngineComponent::SpriteSheet>(id, {true,
            {(float)std::atoi(it.at(3).c_str()), (float)std::atoi(it.at(4).c_str()), (float)std::atoi(it.at(5).c_str()), (float)std::atoi(it.at(6).c_str())}, // 2 3 4 5 | recX recY recWidth recHeigth
            0, 0, // framespeedX framespeedY
            0, 0, // starpointX starpointY
            1}); // frameMax
            r.addComponent<EngineComponent::Drawable>(id, {std::atoi(it.at(7).c_str()) == 0 ? false : true, it.at(2)}); // 6 | isDrawable
            r.addComponent<EngineComponent::Slide>(id, {std::atoi(it.at(8).c_str()) == 0 ? false : true}); // 7 | isSlidable
            r.addComponent<EngineComponent::Direction>(id, {-10, 0});
            std::stringstream sstream(it.at(9));
	        size_t result;
	        sstream >> result;
            r.addComponent<EngineComponent::Layer>(id, {result});
        }
        return ids;
    }

    std::size_t Background::addEntityFromJSON(Registry &r, std::string const &name)
    {
        return 0;
    }

    std::size_t Background::addEntityFromJSON(Registry &r, std::string const &file, std::string const &name)
    {
        return 0;
    }
}