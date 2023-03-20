/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Auxiliaries
*/

#include "DrawC.hpp"
#include "GameplayC.hpp"
#include "Auxiliaries.hpp"

namespace Entity {
    Auxiliaries::Auxiliaries()
    {
    }

    Auxiliaries::~Auxiliaries()
    {
    }

    Auxiliaries::Auxiliaries(std::string const &file) : _file(file)
    {
        if (_file.peek() == std::ifstream::traits_type::eof())
            throw ErrorReadFile("Couldn't read the file");
        _reader.parse(_file, _value);
    }

    std::vector<std::size_t> Auxiliaries::addEntitiesFromCSV(Registry &r, std::string const &file)
    {
        std::vector<std::size_t> ids;
        return ids;
    }

    std::vector<std::size_t> Auxiliaries::addEntitiesFromCSV(Registry &r)
    {
        std::vector<std::size_t> ids;
        return ids;
    }

    /**
     * @brief 
     * Create auxiliaries based on previous data
     * 
     * @param r 
     * @param name 
     * @return std::size_t 
     */
    std::size_t Auxiliaries::addEntityFromJSON(Registry &r, std::string const &name)
    {
        std::size_t id;

        if (!_value[name])
            throw ErrorJSON("Couldn't find asked name");
        id = r.spawnEntity();

        r.addComponent<EngineComponent::Position>(id, {{_value[name]["Offset"][0].asFloat(), _value[name]["Offset"][1].asFloat()}}); // position
        r.addComponent<EngineComponent::Drawable>(id, {true, _value[name]["Texture"].asString()});
        r.addComponent<EngineComponent::SpriteSheet>(id, {
            true, // isAnimated
            {_value[name]["Rectangle"][0].asFloat(), _value[name]["Rectangle"][1].asFloat(), _value[name]["Rectangle"][2].asFloat(), _value[name]["Rectangle"][3].asFloat()}, // rectangle
            _value[name]["Framespeed"][0].asFloat(), _value[name]["Framespeed"][1].asFloat(), // framespeed
            _value[name]["Rectangle"][0].asFloat(), _value[name]["Rectangle"][1].asFloat(), // startpoint
            _value[name]["Framemax"].asFloat() // framemax
        });
        r.addComponent<EngineComponent::ProjectileStats>(id, {_value[name]["NormalShoot"].asString(), _value[name]["StrongShoot"].asString()}); // type of shoot + timer
    
        // r.addComponent<EngineComponent::AttachedID>(id, {});
        r.addComponent<EngineComponent::Controllable>(id, {true});
        r.addComponent<EngineComponent::Direction>(id, {});
        // r.addComponent<EngineComponent::Faction>(id, {});
        r.addComponent<EngineComponent::Layer>(id, {(std::size_t)_value[name]["Layer"].asInt64()});
        return id;
    }

    /**
     * @brief 
     * Set auxiliaries from a JSON file
     * 
     * @param r 
     * @param file 
     * @param name 
     * @return std::size_t 
     */
    std::size_t Auxiliaries::addEntityFromJSON(Registry &r, std::string const &file, std::string const &name)
    {
        std::size_t id;

        if (_file.peek() == std::ifstream::traits_type::eof())
            throw ErrorReadFile("Couldn't read the file");
        _reader.parse(_file, _value);
        if (!_value[name])
            throw ErrorJSON("Couldn't find asked name");
        id = r.spawnEntity();

        r.addComponent<EngineComponent::Position>(id, {{_value[name]["Offset"][0].asFloat(), _value[name]["Offset"][1].asFloat()}}); // position
        r.addComponent<EngineComponent::Drawable>(id, {true, _value[name]["Texture"].asString()});
        r.addComponent<EngineComponent::SpriteSheet>(id, {
            true, // isAnimated
            {_value[name]["Rectangle"][0].asFloat(), _value[name]["Rectangle"][1].asFloat(), _value[name]["Rectangle"][2].asFloat(), _value[name]["Rectangle"][3].asFloat()}, // rectangle
            _value[name]["Framespeed"][0].asFloat(), _value[name]["Framespeed"][1].asFloat(), // framespeed
            _value[name]["Rectangle"][0].asFloat(), _value[name]["Rectangle"][1].asFloat(), // startpoint
            _value[name]["Framemax"].asFloat() // framemax
        });
        r.addComponent<EngineComponent::ProjectileStats>(id, {_value[name]["NormalShoot"].asString(), _value[name]["StrongShoot"].asString()}); // type of shoot + timer

        // r.addComponent<EngineComponent::AttachedID>(id, {});
        r.addComponent<EngineComponent::Controllable>(id, {true});
        r.addComponent<EngineComponent::Direction>(id, {});
        r.addComponent<EngineComponent::Faction>(id, {});
        r.addComponent<EngineComponent::Layer>(id, {(std::size_t)_value[name]["Layer"].asInt64()});
        return id;
    }
};