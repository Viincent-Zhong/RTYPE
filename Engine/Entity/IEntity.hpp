/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Entity
*/

#pragma once

#include "CSV.hpp"

class Registry;

namespace EngineEntity {
    enum Faction {
        Ally = 1,
        Enemy = 2,
        Obstacle = 3,
        Bonus = 4
    };

    class IEntity {
        public:
            virtual ~IEntity() = default;
            /** @brief The function is used to parse a default file and then add parsed data to the registry
             */
            virtual std::vector<std::size_t> addEntitiesFromCSV(Registry &r) = 0;
            /** @brief The function is used to parse a file and then add parsed data to the registry
             */
            virtual std::vector<std::size_t> addEntitiesFromCSV(Registry &r, std::string const &file) = 0;
            /** @brief Add entity from json by searching in the json file the given column name
             *  This function use a default json filepath
             */
            virtual std::size_t addEntityFromJSON(Registry &r, std::string const &name) = 0;
            /** @brief Add entity from json by searching in the json file the given column name
             */
            virtual std::size_t addEntityFromJSON(Registry &r, std::string const &file, std::string const &name) = 0;
    };
};
