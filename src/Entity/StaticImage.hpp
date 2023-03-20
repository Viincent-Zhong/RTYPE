/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** StaticImage
*/

#pragma once

#include "IEntity.hpp"
#include "Registry.hpp"

namespace Entity {
    class StaticImage : public EngineEntity::IEntity {
        public:
            StaticImage();
            ~StaticImage();
            std::vector<std::size_t> addEntitiesFromCSV(Registry &r, std::string const &file) override;
            std::vector<std::size_t> addEntitiesFromCSV(Registry &r) override;
            std::size_t addEntityFromJSON(Registry &r, std::string const &name) override;
            std::size_t addEntityFromJSON(Registry &r, std::string const &file, std::string const &name) override;
    };
};