/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** SoundEffect
*/

#pragma once

#include "IEntity.hpp"

namespace Entity {
    class SoundEffect : public EngineEntity::IEntity {
        public:
            SoundEffect();
            ~SoundEffect();
            SoundEffect(std::string const &file);
            std::vector<std::size_t> addEntitiesFromCSV(Registry &r) override;
            std::vector<std::size_t> addEntitiesFromCSV(Registry &r, std::string const &file) override;
            std::size_t addEntityFromJSON(Registry &r, std::string const &name) override;
            std::size_t addEntityFromJSON(Registry &r, std::string const &file, std::string const &name) override;
        private:
            std::vector<std::vector<std::string>> _content;
    };
};