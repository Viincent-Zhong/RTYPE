/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** SendDataSystems
*/

#include "DrawC.hpp"
#include "SendDataSystems.hpp"
#include "Serialization.hpp"
#include "UDPSingletons.hpp"
#include "DataStructure.hpp"

/**
 * @brief Send all entities of the game to the client at a frequence of miniTimer
 */
static void sendServerDatas(Registry &r, EngineComponent::Singletons &singletons) {
    if (!singletons.getSingleton<EngineUtils::Timer>(EngineServer::UDP::SingletonsEnum::MINI_TIMER).TimerDone())
        return;
    auto const &positions = r.getComponents<EngineComponent::Position>();
    auto const &rectangles = r.getComponents<EngineComponent::SpriteSheet>();
    auto const &textures = r.getComponents<EngineComponent::Drawable>();

    for (std::size_t i = 0; i < positions.size() && i < rectangles.size() && i < textures.size(); ++i) {
        auto const &pos = positions[i];
        auto const &rec = rectangles[i];
        auto const &tex = textures[i];

        if (!pos || !rec || !tex)
            continue;
        EngineNetwork::UDPDataStructure::EntityTransfer entity;
        auto textureID = EngineNetwork::UDPDataStructure::textureToID.find(tex.value().texture);
        if (textureID != EngineNetwork::UDPDataStructure::textureToID.end())
            entity.textureID = textureID->second;
        std::pair<std::array<uint16_t, 50>, std::size_t> sendEntity = EngineNetwork::Serialisation::pack<EngineNetwork::UDPDataStructure::EntityTransfer>({EngineNetwork::UDPDataStructure::STATUS_GAME}, entity);
        singletons.getSingleton<EngineUtils::Queue<std::pair<EngineNetwork::DataStructure::Message, EngineNetwork::DataStructure::MessageTarget>>>(EngineServer::UDP::SingletonsEnum::SEND_LIST).push({{sendEntity}, {0, false}});
    }
};

namespace System {
    Network::Network()
    {
        // _networkSystems.push_front(&sendServerDatas);
    }

    /**
     * @brief 
     * Run the Communication between Server and Client System
     * 
     * @param r 
     * @param singletons 
     */
    void Network::run(Registry &r, EngineComponent::Singletons &singletons)
    {
        for (auto it = _networkSystems.begin(); it != _networkSystems.end(); ++it)
            (*it)(r, singletons);
    }
};