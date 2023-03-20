/*
** EPITECH PROJECT, 2022
** B-CPP-500-PAR-5-1-rtype-pierre-alexandre.delgado-arevalo
** File description:
** Background.hpp
*/

#pragma once

#include "IEntity.hpp"
#include "Registry.hpp"

namespace Entity {
    class Background : public EngineEntity::IEntity {
        public:
            Background();
            Background(std::string const &file);
            ~Background();
            std::vector<std::size_t> addEntitiesFromCSV(Registry &r, std::string const &file) override;
            std::vector<std::size_t> addEntitiesFromCSV(Registry &r) override;
            std::size_t addEntityFromJSON(Registry &r, std::string const &name) override;
            std::size_t addEntityFromJSON(Registry &r, std::string const &file, std::string const &name) override;
        private:
            std::vector<std::vector<std::string>> _content;
    };
}