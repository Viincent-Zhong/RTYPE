/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** EntityCache
*/

#include "EntityCache.hpp"

namespace EngineEntity {
    EntityCache::EntityCache()
    {
    }

    EntityCache::~EntityCache()
    {
    }

    /**
     * @brief 
     * Create entity based on previous data
     * 
     * @param r 
     * @param entity 
     * @return std::vector<std::size_t> 
     */
    std::vector<std::size_t> EntityCache::addEntitiesFromCSV(Registry &r, int entity)
    {
        auto init = _inits.find(entity);

        if (init != _inits.end()) {
            return init->second.get()->addEntitiesFromCSV(r);
        } else
            return {};
    }

    /**
     * @brief 
     * Set entity from a CSV file
     * 
     * @param r 
     * @param entity 
     * @param file 
     * @return std::vector<std::size_t> 
     */
    std::vector<std::size_t> EntityCache::addEntitiesFromCSV(Registry &r, int entity, std::string const &file)
    {
        auto init = _inits.find(entity);

        if (init != _inits.end()) {
            return init->second.get()->addEntitiesFromCSV(r, file);
        } else
            return {};
    }

    /**
     * @brief 
     * Create entity based on previous data
     * 
     * @param r 
     * @param entity 
     * @param name 
     * @return std::size_t 
     */
    std::size_t EntityCache::addEntityFromJSON(Registry &r, int entity, std::string const &name)
    {
        auto init = _inits.find(entity);

        if (init != _inits.end()) {
            return init->second.get()->addEntityFromJSON(r, name);
        } else
            return {};
    }

    /**
     * @brief 
     * Set entity from a JSON file
     * 
     * @param r 
     * @param entity 
     * @param name 
     * @param file 
     * @return std::size_t 
     */
    std::size_t EntityCache::addEntityFromJSON(Registry &r, int entity, std::string const &name, std::string const &file)
    {
        auto init = _inits.find(entity);

        if (init != _inits.end()) {
            return init->second.get()->addEntityFromJSON(r, file, name);
        } else
            return {};
    }
};
