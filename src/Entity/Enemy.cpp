/*
** EPITECH PROJECT, 2022
** B-CPP-500-PAR-5-1-rtype-pierre-alexandre.delgado-arevalo
** File description:
** Enemy.cpp
*/

#include <cstdlib>
#include "Enemy.hpp"
#include "DrawC.hpp"
#include "GameplayC.hpp"
#include "ErrorLoader.hpp"
#include "Element/Element.hpp"

namespace Entity {
    Enemy::Enemy()
    {
    }

    Enemy::~Enemy()
    {
    }

    Enemy::Enemy(std::string const &file) : _file(file)
    {
        if (_file.peek() == std::ifstream::traits_type::eof())
            throw ErrorReadFile("Couldn't read the file");
        _reader.parse(_file, _value);
    }

    std::vector<std::size_t> Enemy::addEntitiesFromCSV(Registry &r, std::string const &file)
    {
        return std::vector<std::size_t>();
    }

    std::vector<std::size_t> Enemy::addEntitiesFromCSV(Registry &r)
    {
        return std::vector<std::size_t>();
    }

    /**
     * @brief 
     * Create Enemy based on previous data
     * 
     * @param r 
     * @param name 
     * @return std::size_t 
     */
    std::size_t Enemy::addEntityFromJSON(Registry &r, std::string const &name)
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
        r.addComponent<EngineComponent::HitDamage>(id, {(std::size_t)_value[name]["Damage"].asInt64()}); // damage
        // r.addComponent<EngineComponent::Direction>(id, {_value[name]["Direction"][0].asFloat(), _value[name]["Direction"][1].asFloat()}); // direction
        if (name == "specialEnemyUpsideDown" || name == "specialEnemy") {
            r.addComponent<EngineComponent::Position>(id, {{_value[name]["Offset"][0].asFloat(), _value[name]["Offset"][1].asFloat()}, true}); // position
            r.addComponent<EngineComponent::Direction>(id, {_value[name]["Direction"][0].asFloat(), _value[name]["Direction"][1].asFloat()}); // direction
        } else {
            int pos_enemy = rand() % 850;
            r.addComponent<EngineComponent::Position>(id, {{_value[name]["Offset"][0].asFloat() + rand() % 400, static_cast<float>(pos_enemy)}, true}); // position
            r.addComponent<EngineComponent::Direction>(id, {static_cast<float>(-((rand() % 70) + 30)), _value[name]["Direction"][1].asFloat()}); // direction
        }
        r.addComponent<EngineComponent::Faction>(id, {EngineEntity::Enemy}); // faction (enemy)

        r.addComponent<EngineComponent::HP>(id, {(std::size_t)_value[name]["Hp"].asInt64()}); // hp
        r.addComponent<EngineComponent::Collision>(id, {true}); // Collision : true / false
        r.addComponent<EngineComponent::Layer>(id, {(std::size_t)_value[name]["Layer"].asInt64()});
        return id;
    }

    /**
     * @brief 
     * Set Enemy from a JSON file
     * 
     * @param r 
     * @param file 
     * @param name 
     * @return std::size_t 
     */
    std::size_t Enemy::addEntityFromJSON(Registry &r, std::string const &file, std::string const &name)
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
        r.addComponent<EngineComponent::HitDamage>(id, {(std::size_t)_value[name]["Damage"].asInt64()}); // damage
        r.addComponent<EngineComponent::Direction>(id, {_value[name]["Direction"][0].asFloat(), _value[name]["Direction"][1].asFloat()}); // direction
        r.addComponent<EngineComponent::Position>(id, {{_value[name]["Offset"][0].asFloat(), _value[name]["Offset"][1].asFloat()}, true}); // position
        r.addComponent<EngineComponent::Faction>(id, {EngineEntity::Enemy}); // faction (enemy)

        r.addComponent<EngineComponent::HP>(id, {1}); // hp
        r.addComponent<EngineComponent::Collision>(id, {true}); // collision : true / false
        r.addComponent<EngineComponent::Layer>(id, {(std::size_t)_value[name]["Layer"].asInt64()});
        return id;
    }
}