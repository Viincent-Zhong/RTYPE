/*
** EPITECH PROJECT, 2022
** B-CPP-500-PAR-5-1-rtype-pierre-alexandre.delgado-arevalo
** File description:
** Text
*/

#pragma once

#include "IEntity.hpp"

namespace Entity {
    class Text : public EngineEntity::IEntity {
        public:
            Text() {};
            ~Text() {};
            Text(std::string const &file);    
            // Text(std::string const &text, float x, float y);
            std::vector<std::size_t> addEntitiesFromCSV(Registry &r, std::string const &file);
            std::vector<std::size_t> addEntitiesFromCSV(Registry &r);
            std::size_t addEntityFromJSON(Registry &r, std::string const &name);
            std::size_t addEntityFromJSON(Registry &r, std::string const &file, std::string const &name);
        private:
            std::vector<std::vector<std::string>> _content;
    };
};