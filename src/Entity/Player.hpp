/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Player
*/

#pragma once

#include "IEntity.hpp"
#include "Registry.hpp"

namespace Entity {
    class Player : public EngineEntity::IEntity {
        public:
            Player();
            ~Player();
            Player(std::string const &file);
            std::vector<std::size_t> addEntitiesFromCSV(Registry &r) override;
            std::vector<std::size_t> addEntitiesFromCSV(Registry &r, std::string const &file) override;
            std::size_t addEntityFromJSON(Registry &r, std::string const &name) override;
            std::size_t addEntityFromJSON(Registry &r, std::string const &file, std::string const &name) override;
        private:
            std::vector<std::vector<std::string>> _content;
    };
};