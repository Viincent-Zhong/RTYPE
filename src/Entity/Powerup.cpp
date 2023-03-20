/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Powerup
*/

#include "Powerup.hpp"

namespace Entity {
    Powerup::Powerup()
    {
    }

    Powerup::~Powerup()
    {
    }

    /**
     * @brief 
     * 
     * @param r 
     * @param file 
     * @return std::vector<std::size_t> 
     */
    std::vector<std::size_t> Powerup::addEntitiesFromCSV(Registry &r, std::string const &file)
    {
        return std::vector<std::size_t>();
    }

    std::vector<std::size_t> Powerup::addEntitiesFromCSV(Registry &r)
    {
        return std::vector<std::size_t>();
    }

    std::size_t Powerup::addEntityFromJSON(Registry &r, std::string const &name)
    {
        return std::size_t();
    }

    std::size_t Powerup::addEntityFromJSON(Registry &r, std::string const &file, std::string const &name)
    {
        return std::size_t();
    }
};