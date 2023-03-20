/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Obstacle
*/

#pragma once

#include "IEntity.hpp"
#include "Registry.hpp"

namespace Entity {
    class Obstacle : public EngineEntity::IEntity {
        public:
            Obstacle();
            ~Obstacle();
            Obstacle(std::string const &file);
            std::vector<std::size_t> addEntitiesFromCSV(Registry &r, std::string const &file) override;
            std::vector<std::size_t> addEntitiesFromCSV(Registry &r) override;
            std::size_t addEntityFromJSON(Registry &r, std::string const &name) override;
            std::size_t addEntityFromJSON(Registry &r, std::string const &file, std::string const &name) override;
    };
};