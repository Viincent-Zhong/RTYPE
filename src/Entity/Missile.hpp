/*
** EPITECH PROJECT, 2022
** B-CPP-500-PAR-5-1-rtype-pierre-alexandre.delgado-arevalo
** File description:
** Missile.hpp
*/

#pragma once

#include <json/json.h>
#include <fstream>
#include "IEntity.hpp"

namespace Entity {
    class Missile : public EngineEntity::IEntity {
        public:
            Missile();
            Missile(std::string const &file);
            ~Missile();
            std::vector<std::size_t> addEntitiesFromCSV(Registry &r, std::string const &file) override
                {return std::vector<std::size_t>();};
            std::vector<std::size_t> addEntitiesFromCSV(Registry &r) override
                {return std::vector<std::size_t>();};
            std::size_t addEntityFromJSON(Registry &r, std::string const &name) override;
            std::size_t addEntityFromJSON(Registry &r, std::string const &file, std::string const &name) override;
        private:
            Json::Reader _reader;
            Json::Value _value;
            std::ifstream _file;
    };
};