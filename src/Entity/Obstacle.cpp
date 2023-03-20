/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Obstacle
*/

#include "Obstacle.hpp"
namespace Entity {
    Obstacle::Obstacle()
    {
    }

    Obstacle::~Obstacle()
    {
    }

    Obstacle::Obstacle(std::string const &file)
    {
    }

    /**
     * @brief 
     * 
     * @param r 
     * @param file 
     * @return std::vector<std::size_t> 
     */
    std::vector<std::size_t> Obstacle::addEntitiesFromCSV(Registry &r, std::string const &file)
    {
        return std::vector<std::size_t>();
    }

    std::vector<std::size_t> Obstacle::addEntitiesFromCSV(Registry &r)
    {
        return std::vector<std::size_t>();
    }

    std::size_t Obstacle::addEntityFromJSON(Registry &r, std::string const &name)
    {
        return std::size_t();
    }

    std::size_t Obstacle::addEntityFromJSON(Registry &r, std::string const &file, std::string const &name)
    {
        return std::size_t();
    }
};