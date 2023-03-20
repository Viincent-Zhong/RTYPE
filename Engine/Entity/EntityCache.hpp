/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Entity
*/

#pragma once

#include <unordered_map>
#include <memory>
#include "IEntity.hpp"

namespace EngineEntity {
    class EntityCache {
        public:
            EntityCache();
            ~EntityCache();
            std::vector<std::size_t> addEntitiesFromCSV(Registry &r, int entityIndex);
            std::vector<std::size_t> addEntitiesFromCSV(Registry &r, int entityIndex, std::string const &file);
            std::size_t addEntityFromJSON(Registry &r, int entityIndex, std::string const &name);
            std::size_t addEntityFromJSON(Registry &r, int entityIndex, std::string const &name, std::string const &file);
            template<class T, typename ... Params>
            void cacheEntity(int entityIndex, Params &&...params)
            {
                _inits.insert({entityIndex, std::unique_ptr<EngineEntity::IEntity>(new T(params...))});
            }

        private:
            std::unordered_map<int, std::unique_ptr<EngineEntity::IEntity>> _inits;
    };
};