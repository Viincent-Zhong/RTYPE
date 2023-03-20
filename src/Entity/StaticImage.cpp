/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** StaticImage
*/

#include "StaticImage.hpp"

namespace Entity {
    StaticImage::StaticImage()
    {
    }

    StaticImage::~StaticImage()
    {
    }

    /**
     * @brief 
     * 
     * @param r 
     * @param file 
     * @return std::vector<std::size_t> 
     */
    std::vector<std::size_t> StaticImage::addEntitiesFromCSV(Registry &r, std::string const &file)
    {
        return std::vector<std::size_t>();
    }

    std::vector<std::size_t> StaticImage::addEntitiesFromCSV(Registry &r)
    {
    }

    std::size_t StaticImage::addEntityFromJSON(Registry &r, std::string const &name)
    {
        return std::size_t();
    }

    std::size_t StaticImage::addEntityFromJSON(Registry &r, std::string const &file, std::string const &name)
    {
        return std::size_t();
    }
};