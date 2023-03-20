/*
** EPITECH PROJECT, 2022
** Project R-TYPE
** File description:
** logicGameClient.cpp
*/

#include "DrawC.hpp"
#include "GameplayC.hpp"
#include "Serialization.hpp"
#include "Singletons.hpp"

#include "DataStructure.hpp"
#include "UDPDataStructure.hpp"
#include "ClientUDPSingletons.hpp"
#include "Registry.hpp"

/**
 * @brief Get the id of a player
 */
void getStatusPlayer(std::pair<std::array<uint16_t, 50>, std::pair<std::size_t, unsigned int>> &data, Registry &r, EngineComponent::Singletons &singleton)
{
    EngineNetwork::DataStructure::ID id;

    try {
        id = std::any_cast<EngineNetwork::DataStructure::ID>(EngineNetwork::Serialisation::unpack(data.first, data.second.first));
    } catch (std::bad_cast const &error) {
        std::cout << "Received bad id\n";
        return;
    }
    std::size_t &sID = singleton.getSingleton<std::size_t>(EngineClient::UDP::SingletonsEnum::ID);
    sID = id.id + 100;
}

/**
 * @brief Get info of an entity sent by the game for us to draw it
 */
void getStatusGame(std::pair<std::array<uint16_t, 50>, std::pair<std::size_t, unsigned int>> &data, Registry &r, EngineComponent::Singletons &singleton)
{
    EngineNetwork::UDPDataStructure::EntityTransfer entity;

    try {
        entity = std::any_cast<EngineNetwork::UDPDataStructure::EntityTransfer>(EngineNetwork::Serialisation::unpack(data.first, data.second.first));
        std::cout << "Receiving entity " << entity.id << " at pos [" << entity.pos_x << ", " << entity.pos_y << "] at direction ["
        << entity.direction_x << ", " << entity.direction_y <<
        "]\n";
    } catch (std::bad_cast const &error) {
        return;
    }
    // Let 10 space for background
    entity.id += 100;

    auto texture = EngineNetwork::UDPDataStructure::idToTexture.find((std::size_t)entity.textureID);
    if (texture != EngineNetwork::UDPDataStructure::idToTexture.end())
        r.addComponent<EngineComponent::Drawable>(entity.id, {true, texture->second});
    r.addComponent<EngineComponent::Position>(entity.id, {PadaEngine::Position{(float)entity.pos_x, (float)entity.pos_y}, true});
    r.addComponent<EngineComponent::SpriteSheet>(entity.id, {
        true,
        PadaEngine::Rectangle{(float)entity.rect_x, (float)entity.rect_y, (float)entity.width, (float)entity.height}, // rec
        entity.frame_speed_x, entity.frame_speed_y, // framespeed
        entity.start_point_x, entity.start_point_y, // startpoint
        entity.framemax // framemax
    });
    r.addComponent<EngineComponent::Direction>(entity.id, {entity.direction_x, entity.direction_y});
    r.addComponent<EngineComponent::Faction>(entity.id, {entity.faction});
    r.addComponent<EngineComponent::Layer>(entity.id, {0});
    r.addComponent<EngineComponent::Collision>(entity.id, {false, 0, 0});
}

/**
 * @brief Get the Destroyed object and kill it
 * 
 * @param data 
 * @param r 
 * @param singleton 
 */
void getDestroyed(std::pair<std::array<uint16_t, 50>, std::pair<std::size_t, unsigned int>> &data, Registry &r, EngineComponent::Singletons &singleton)
{
    EngineNetwork::DataStructure::ID entity;
    auto const &pos = r.getComponents<EngineComponent::Position>();

    try {
        entity = std::any_cast<EngineNetwork::DataStructure::ID>(EngineNetwork::Serialisation::unpack(data.first, data.second.first));
        std::cout << "Destroying entity " << entity.id << "\n";
        entity.id += 100;
        auto const &pad = pos[entity.id];
        // singleton.getSingleton<std::string>(EngineClient::UDP::SingletonsEnum::EFFECT_NAME) = "hit";
        if (pad)
            singleton.getSingleton<std::vector<PadaEngine::Position>>(EngineClient::UDP::SingletonsEnum::POS_EXPLOSION).push_back(pad.value().pos);
        r.killEntity(entity.id);
    } catch (std::bad_cast const &error) {
        return;
    }
}

/**
 * @brief Get deconnection ping from the server (game ended)
 */
void getDeconnected(std::pair<std::array<uint16_t, 50>, std::pair<std::size_t, unsigned int>> &data, Registry &r, EngineComponent::Singletons &singleton)
{
    singleton.getSingleton<bool>(EngineClient::UDP::SingletonsEnum::END) = true; // set end variable to true
}
