/*
** EPITECH PROJECT, 2022
** B-CPP-500-PAR-5-1-rtype-pierre-alexandre.delgado-arevalo
** File description:
** Missile.cpp
*/

#include "DrawC.hpp"
#include "GameplayC.hpp"
#include "Missile.hpp"
#include "ErrorLoader.hpp"
#include "Element/Element.hpp"
#include "Registry.hpp"

namespace Entity {
    Missile::Missile()
    {}

    Missile::~Missile()
    {}

    Missile::Missile(std::string const &file) : _file(file)
    {
        if (_file.peek() == std::ifstream::traits_type::eof())
            throw ErrorReadFile("Couldn't read the file");
        _reader.parse(_file, _value);
    }

    /**
     * @brief 
     * Create Missile based on previous data
     * 
     * @param r 
     * @param name 
     * @return std::size_t 
     */
    std::size_t Missile::addEntityFromJSON(Registry &r, std::string const &name)
    {
        std::size_t id;

        if (!_value[name])
            throw ErrorJSON("Couldn't find asked name");
        id = r.spawnEntity();

        r.addComponent<EngineComponent::Drawable>(id, {true, _value[name]["Texture"].asString()});
        r.addComponent<EngineComponent::SpriteSheet>(id, {
            true, // isAnimated
            {_value[name]["Rectangle"][0].asFloat(), _value[name]["Rectangle"][1].asFloat(), _value[name]["Rectangle"][2].asFloat(), _value[name]["Rectangle"][3].asFloat()}, // rectangle
            _value[name]["Framespeed"][0].asFloat(), _value[name]["Framespeed"][1].asFloat(), // framespeed
            _value[name]["Rectangle"][0].asFloat(), _value[name]["Rectangle"][1].asFloat(), // startpoint
            _value[name]["Framemax"].asFloat() // framemax
        });
        r.addComponent<EngineComponent::HitDamage>(id, {(std::size_t)_value[name]["Damage"].asInt64()});
        r.addComponent<EngineComponent::Direction>(id, {_value[name]["Direction"][0].asFloat() * 60, _value[name]["Direction"][1].asFloat() * 60});
        r.addComponent<EngineComponent::Position>(id, {{_value[name]["Offset"][0].asFloat(), _value[name]["Offset"][1].asFloat()}, true}); // position

        r.addComponent<EngineComponent::HP>(id, {(std::size_t)_value[name]["Hp"].asInt64()});
        r.addComponent<EngineComponent::Faction>(id, {});
        r.addComponent<EngineComponent::Collision>(id, {false});
        r.addComponent<EngineComponent::Layer>(id, {(std::size_t)_value[name]["Layer"].asInt64()});
        return id;
    }

    /**
     * @brief 
     * Set Missile from a JSON file
     * 
     * @param r 
     * @param file 
     * @param name 
     * @return std::size_t 
     */
    std::size_t Missile::addEntityFromJSON(Registry &r, std::string const &file, std::string const &name)
    {
        std::size_t id;

        _file = std::ifstream(file);
        if (_file.peek() == std::ifstream::traits_type::eof())
            throw ErrorReadFile("Couldn't read the file");
        _reader.parse(_file, _value);

        if (!_value[name])
            throw ErrorJSON("Couldn't find asked name");
        id = r.spawnEntity();

        r.addComponent<EngineComponent::Drawable>(id, {true, _value[name]["Texture"].asString()});
        r.addComponent<EngineComponent::SpriteSheet>(id, {
            true, // isAnimated
            {_value[name]["Rectangle"][0].asFloat(), _value[name]["Rectangle"][1].asFloat(), _value[name]["Rectangle"][2].asFloat(), _value[name]["Rectangle"][3].asFloat()}, // rectangle
            _value[name]["Framespeed"][0].asFloat(), _value[name]["Framespeed"][1].asFloat(), // framespeed
            _value[name]["Rectangle"][0].asFloat(), _value[name]["Rectangle"][1].asFloat(), // startpoint
            _value[name]["Framemax"].asFloat() // framemax
        });
        r.addComponent<EngineComponent::HitDamage>(id, {(std::size_t)_value[name]["Damage"].asInt64()});
        r.addComponent<EngineComponent::Direction>(id, {_value[name]["Direction"][0].asFloat() * 60, _value[name]["Direction"][1].asFloat() * 60});
        r.addComponent<EngineComponent::Position>(id, {{_value[name]["Offset"][0].asFloat(), _value[name]["Offset"][1].asFloat()}, true}); // position
        r.addComponent<EngineComponent::Faction>(id, {});

        r.addComponent<EngineComponent::HP>(id, {1});
        r.addComponent<EngineComponent::Collision>(id, {false});
        r.addComponent<EngineComponent::Layer>(id, {(std::size_t)_value[name]["Layer"].asInt64()});
        return id;
    }
}