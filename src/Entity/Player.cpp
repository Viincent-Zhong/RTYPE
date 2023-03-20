/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Player
*/

#include <sstream>
#include <cstdlib>
#include "Player.hpp"
#include "DrawC.hpp"
#include "GameplayC.hpp"

namespace Entity {
    Player::Player()
    {
    }

    Player::~Player()
    {
    }

    Player::Player(std::string const &file)
    {
        _content = EngineUtils::CSV::readCSV(file);
    }

    /**
     * @brief 
     * Set Player from a JSON file
     * 
     * @param r 
     * @param file 
     * @return std::vector<std::size_t> 
     */
    std::vector<std::size_t> Player::addEntitiesFromCSV(Registry &r, std::string const &file)
    {
        std::vector<std::size_t> ids;

        if (_content.size() == 0)
            _content = EngineUtils::CSV::readCSV(file);
        for (auto it : _content) {
            std::size_t id = r.spawnEntity();
            ids.push_back(id);
            r.addComponent<EngineComponent::Position>(id, {{(float)std::atoi(it.at(0).c_str()), (float)std::atoi(it.at(1).c_str())}}); // 0 1 | posX posY
            r.addComponent<EngineComponent::Drawable>(id, {std::atoi(it.at(3).c_str()) == 0 ? false : true, it.at(2)}); // 3 2 | isDrawable Texture
            r.addComponent<EngineComponent::SpriteSheet>(id, {true,
            {(float)std::atoi(it.at(4).c_str()), (float)std::atoi(it.at(5).c_str()), (float)std::atoi(it.at(6).c_str()), (float)std::atoi(it.at(7).c_str())}, // 4 5 6 7 | recX recY recWidth recHeigth
            (float)std::atoi(it.at(8).c_str()), (float)std::atoi(it.at(9).c_str()), // 8 9 | framespeedX framespeedY
            (float)std::atoi(it.at(4).c_str()), (float)std::atoi(it.at(5).c_str()), // 4 5 | starpointX starpointY
            (float)std::atoi(it.at(10).c_str())}); // 10 | frameMax
            r.addComponent<EngineComponent::HP>(id, {(std::size_t)std::atoi(it.at(11).c_str())}); // 11 | HP
            r.addComponent<EngineComponent::ProjectileStats>(id, {it.at(12), it.at(13)}); // 12 13 14 | normal strong timer
            r.addComponent<EngineComponent::WalkAnimation>(id, {{
                {(float)std::atoi(it.at(4).c_str()), (float)std::atoi(it.at(5).c_str())}, // origin 4 5 | X Y
                {(float)std::atoi(it.at(14).c_str()), (float)std::atoi(it.at(15).c_str())}, // left 15 16 | X Y
                {(float)std::atoi(it.at(16).c_str()), (float)std::atoi(it.at(17).c_str())}, // right 17 18 | X Y
                {(float)std::atoi(it.at(18).c_str()), (float)std::atoi(it.at(19).c_str())}, // up 19 20 | X Y
                {(float)std::atoi(it.at(20).c_str()), (float)std::atoi(it.at(21).c_str())} // down 21 22 | X Y
            }});

            r.addComponent<EngineComponent::Controllable>(id, {true});
            r.addComponent<EngineComponent::Direction>(id, {0, 0});
            r.addComponent<EngineComponent::Faction>(id, {EngineEntity::Ally});
            r.addComponent<EngineComponent::Collision>(id, {false});
            r.addComponent<EngineComponent::Controllable>(id, {true});
            r.addComponent<EngineComponent::Direction>(id, {0, 0});
            r.addComponent<EngineComponent::HitDamage>(id, {1});

        }
        return ids;
    }

    /**
     * @brief 
     * Create Player based on previous data
     * 
     * @param r 
     * @return std::vector<std::size_t> 
     */
    std::vector<std::size_t> Player::addEntitiesFromCSV(Registry &r)
    {
        std::vector<std::size_t> ids;

        for (auto it : _content) {
            std::size_t id = r.spawnEntity();
            ids.push_back(id);
            r.addComponent<EngineComponent::Position>(id, {{(float)std::atoi(it.at(0).c_str()), (float)std::atoi(it.at(1).c_str())}}); // 0 1 | posX posY
            r.addComponent<EngineComponent::Drawable>(id, {std::atoi(it.at(3).c_str()) == 0 ? false : true, it.at(2)}); // 3 2 | isDrawable Texture
            r.addComponent<EngineComponent::SpriteSheet>(id, {true,
            {(float)std::atoi(it.at(4).c_str()), (float)std::atoi(it.at(5).c_str()), (float)std::atoi(it.at(6).c_str()), (float)std::atoi(it.at(7).c_str())}, // 4 5 6 7 | recX recY recWidth recHeigth
            (float)std::atoi(it.at(8).c_str()), (float)std::atoi(it.at(9).c_str()), // 8 9 | framespeedX framespeedY
            (float)std::atoi(it.at(4).c_str()), (float)std::atoi(it.at(5).c_str()), // 4 5 | starpointX starpointY
            (float)std::atoi(it.at(10).c_str())}); // 10 | frameMax
            r.addComponent<EngineComponent::HP>(id, {(std::size_t)std::atoi(it.at(11).c_str())}); // 11 | HP
            r.addComponent<EngineComponent::ProjectileStats>(id, {it.at(12), it.at(13)}); // 12 13 14 | normal strong timer
            r.addComponent<EngineComponent::WalkAnimation>(id, {{
                {(float)std::atoi(it.at(4).c_str()), (float)std::atoi(it.at(5).c_str())}, // origin 4 5 | X Y
                {(float)std::atoi(it.at(14).c_str()), (float)std::atoi(it.at(15).c_str())}, // left 15 16 | X Y
                {(float)std::atoi(it.at(16).c_str()), (float)std::atoi(it.at(17).c_str())}, // right 17 18 | X Y
                {(float)std::atoi(it.at(18).c_str()), (float)std::atoi(it.at(19).c_str())}, // up 19 20 | X Y
                {(float)std::atoi(it.at(20).c_str()), (float)std::atoi(it.at(21).c_str())} // down 21 22 | X Y
            }});

            r.addComponent<EngineComponent::Faction>(id, {EngineEntity::Ally});
            r.addComponent<EngineComponent::Collision>(id, {false});
            r.addComponent<EngineComponent::Controllable>(id, {true});
            r.addComponent<EngineComponent::Direction>(id, {0, 0});
            r.addComponent<EngineComponent::HitDamage>(id, {1});
        }
        return ids;
    }

    std::size_t Player::addEntityFromJSON(Registry &r, std::string const &name)
    {
        return std::size_t();
    }
    std::size_t Player::addEntityFromJSON(Registry &r, std::string const &file, std::string const &name)
    {
        return std::size_t();
    }
};