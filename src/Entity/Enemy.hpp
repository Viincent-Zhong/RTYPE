/*
** EPITECH PROJECT, 2022
** B-CPP-500-PAR-5-1-rtype-pierre-alexandre.delgado-arevalo
** File description:
** Enemy.hpp
*/
#pragma once

#include <fstream>
#include <json/json.h>
#include "IEntity.hpp"
#include "Registry.hpp"

namespace Entity {
    class Enemy : public EngineEntity::IEntity {
        public:
            Enemy();
            Enemy(std::string const &file);
            ~Enemy();
            std::vector<std::size_t> addEntitiesFromCSV(Registry &r, std::string const &file) override;
            std::vector<std::size_t> addEntitiesFromCSV(Registry &r) override;
            std::size_t addEntityFromJSON(Registry &r, std::string const &name) override;
            std::size_t addEntityFromJSON(Registry &r, std::string const &file, std::string const &name) override;
        private:
            Json::Reader _reader;
            Json::Value _value;
            std::ifstream _file;
    };
};