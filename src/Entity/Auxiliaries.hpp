/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Auxiliaries
*/

#pragma once

#include <json/json.h>
#include <fstream>
#include "IEntity.hpp"
#include "Registry.hpp"

namespace Entity {
    class Auxiliaries : public EngineEntity::IEntity {
        public:
            Auxiliaries();
            Auxiliaries(std::string const &file);
            ~Auxiliaries();
            std::vector<std::size_t> addEntitiesFromCSV(Registry &r, std::string const &file) override;
            std::vector<std::size_t> addEntitiesFromCSV(Registry &r);
            std::size_t addEntityFromJSON(Registry &r, std::string const &name) override;
            std::size_t addEntityFromJSON(Registry &r, std::string const &file, std::string const &name) override;
        private:
            Json::Reader _reader;
            Json::Value _value;
            std::ifstream _file;
    };
};