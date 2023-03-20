/*
** EPITECH PROJECT, 2022
** Project R-TYPE
** File description:
** logicgameServer.cpp
*/

#include "EComponents.hpp"
#include "EntityGeneration.hpp"
#include "Serialization.hpp"
#include "Singletons.hpp"
#include "UDPSingletons.hpp"
#include "DataStructure.hpp"

/**
 * @brief 
 * 
 * @param read 
 * @param r 
 * @param singletons 
 */
void clientDisconnect(std::pair<std::array<uint16_t, 50>, std::pair<std::size_t, unsigned int>> &read, Registry &r, EngineComponent::Singletons &singletons)
{
    std::cout << "Client " << read.second.second << " disconnected\n";
    std::vector<unsigned int> &players = singletons.getSingleton<std::vector<unsigned int>>(EngineServer::UDP::SingletonsEnum::CORE_PLAYER);

    // Erasing the client from the list of players
    for (auto player = players.begin(); player != players.end(); ++player) {
        if (*player == read.second.second) {
            players.erase(player);
            std::cout << "Client " << read.second.second << " erased from player list\n";
            break;
        }
    }
}

/**
 * @brief Send all entities to all client
 */
void sendEntities(Registry &r, EngineComponent::Singletons &singletons)
{
    auto const &positions = r.getComponents<EngineComponent::Position>();
    auto const &rectangles = r.getComponents<EngineComponent::SpriteSheet>();
    auto const &textures = r.getComponents<EngineComponent::Drawable>();
    auto const &directions = r.getComponents<EngineComponent::Direction>();
    auto const &factions = r.getComponents<EngineComponent::Faction>();

    for (std::size_t i = 0; i < positions.size() && i < rectangles.size() && i < textures.size() && i < directions.size() && i < factions.size(); ++i) {
        auto entity = EngineNetwork::UDPDataStructure::convertToEntityTransfer(i, r);
        // if couldn't transfer don't send
        if (!entity.second)
            continue;

        try {
            std::pair<std::array<uint16_t, 50>, std::size_t> sendEntity = EngineNetwork::Serialisation::pack<EngineNetwork::UDPDataStructure::EntityTransfer>({EngineNetwork::UDPDataStructure::STATUS_GAME}, entity.first);
            singletons.getSingleton<EngineUtils::Queue<std::pair<EngineNetwork::DataStructure::Message, EngineNetwork::DataStructure::MessageTarget>>>(EngineServer::UDP::SingletonsEnum::SEND_LIST).push({{sendEntity}, {0, false}});
            std::cout << "From room " << singletons.getSingleton<unsigned int>(EngineServer::UDP::SingletonsEnum::GAMEID) << " : ";
            std::cout << "Sending entity " << i << " at pos [" << entity.first.pos_x << ", " << entity.first.pos_y << "] at direction ["
            << entity.first.direction_x << ", " << entity.first.direction_y << "]\n";
            singletons.getSingleton<std::function<void()>>(EngineServer::UDP::SingletonsEnum::SEND_CALLBACK)(); // Callback to send
        } catch (std::bad_cast const &error) {
            continue;
        }
    }
}

/**
 * @brief Send all the entities for a specific client
 * @param clientID client ID
 * @param r 
 * @param singletons 
 */
void sendEntities(unsigned int clientID, Registry &r, EngineComponent::Singletons &singletons)
{
    auto const &positions = r.getComponents<EngineComponent::Position>();
    auto const &rectangles = r.getComponents<EngineComponent::SpriteSheet>();
    auto const &textures = r.getComponents<EngineComponent::Drawable>();
    auto const &directions = r.getComponents<EngineComponent::Direction>();
    auto const &factions = r.getComponents<EngineComponent::Faction>();

    for (std::size_t i = 0; i < positions.size() && i < rectangles.size() && i < textures.size() && i < directions.size() && i < factions.size(); ++i) {
        auto entity = EngineNetwork::UDPDataStructure::convertToEntityTransfer(i, r);
        // if couldn't transfer don't send
        if (!entity.second)
            continue;

        try {
            std::pair<std::array<uint16_t, 50>, std::size_t> sendEntity = EngineNetwork::Serialisation::pack<EngineNetwork::UDPDataStructure::EntityTransfer>({EngineNetwork::UDPDataStructure::STATUS_GAME}, entity.first);
            singletons.getSingleton<EngineUtils::Queue<std::pair<EngineNetwork::DataStructure::Message, EngineNetwork::DataStructure::MessageTarget>>>(EngineServer::UDP::SingletonsEnum::SEND_LIST).push({{sendEntity}, {clientID, true}});
            std::cout << "From room " << singletons.getSingleton<unsigned int>(EngineServer::UDP::SingletonsEnum::GAMEID) << " : ";
            std::cout << "Sending entity " << i << " at pos [" << entity.first.pos_x << ", " << entity.first.pos_y << "] at direction ["
            << entity.first.direction_x << ", " << entity.first.direction_y << "]\n";
            singletons.getSingleton<std::function<void()>>(EngineServer::UDP::SingletonsEnum::SEND_CALLBACK)(); // Callback to send
        } catch (std::bad_cast const &error) {
            continue;
        }
    }
}

/**
 * @brief Send entity to all client
 * 
 * @param i Entity ID
 * @param r 
 * @param singletons 
 */
void sendEntity(unsigned int i, Registry &r, EngineComponent::Singletons &singletons)
{
    auto entity = EngineNetwork::UDPDataStructure::convertToEntityTransfer(i, r);
    // if couldn't transfer don't send
    if (!entity.second)
        return;

    // Send position, spritesheet, texture, direction, faction
    try {
        std::pair<std::array<uint16_t, 50>, std::size_t> sendEntity = EngineNetwork::Serialisation::pack<EngineNetwork::UDPDataStructure::EntityTransfer>({EngineNetwork::UDPDataStructure::STATUS_GAME}, entity.first);
        singletons.getSingleton<EngineUtils::Queue<std::pair<EngineNetwork::DataStructure::Message, EngineNetwork::DataStructure::MessageTarget>>>(EngineServer::UDP::SingletonsEnum::SEND_LIST).push({{sendEntity}, {0, false}});
        singletons.getSingleton<std::function<void()>>(EngineServer::UDP::SingletonsEnum::SEND_CALLBACK)(); // Callback to send
        std::cout << "From room " << singletons.getSingleton<unsigned int>(EngineServer::UDP::SingletonsEnum::GAMEID) << " : ";
        std::cout << "Sending entity " << i << " at pos [" << entity.first.pos_x << ", " << entity.first.pos_y << "] at direction ["
        << entity.first.direction_x << ", " << entity.first.direction_y << "]\n";

    } catch (std::bad_cast const &error) {
        return;
    }
}

/**
 * @brief Send an entity to all client except for a client
 * 
 * @param i EntityID
 * @param r 
 * @param singletons 
 * @param exception ClientID that we don't want to ping
 */
void sendEntity(unsigned int i, Registry &r, EngineComponent::Singletons &singletons, unsigned int exception)
{
    auto entity = EngineNetwork::UDPDataStructure::convertToEntityTransfer(i, r);
    // if couldn't transfer don't send
    if (!entity.second)
        return;

    // Send position, spritesheet, texture, direction, faction
    try {
        std::pair<std::array<uint16_t, 50>, std::size_t> sendEntity = EngineNetwork::Serialisation::pack<EngineNetwork::UDPDataStructure::EntityTransfer>({EngineNetwork::UDPDataStructure::STATUS_GAME}, entity.first);
        singletons.getSingleton<EngineUtils::Queue<std::pair<EngineNetwork::DataStructure::Message, EngineNetwork::DataStructure::MessageTarget>>>(EngineServer::UDP::SingletonsEnum::SEND_LIST).push({{sendEntity}, {exception, false}});
        singletons.getSingleton<std::function<void()>>(EngineServer::UDP::SingletonsEnum::SEND_CALLBACK)(); // Callback to send
        std::cout << "From room " << singletons.getSingleton<unsigned int>(EngineServer::UDP::SingletonsEnum::GAMEID) << " : ";
        std::cout << "Sending entity " << i << " at pos [" << entity.first.pos_x << ", " << entity.first.pos_y << "] at direction ["
        << entity.first.direction_x << ", " << entity.first.direction_y << "] with id " << exception << " as exception\n";

    } catch (std::bad_cast const &error) {
        return;
    }
}

/**
 * @brief Send an entity to the client
 * 
 * @param clientID clientID
 * @param i Entity ID
 * @param r 
 * @param singletons 
 */
void sendEntity(unsigned int clientID, unsigned int i, Registry &r, EngineComponent::Singletons &singletons)
{
    auto entity = EngineNetwork::UDPDataStructure::convertToEntityTransfer(i, r);
    // if couldn't transfer don't send
    if (!entity.second)
        return;

    // Send position, spritesheet, texture, direction, faction
    try {
        std::pair<std::array<uint16_t, 50>, std::size_t> sendEntity = EngineNetwork::Serialisation::pack<EngineNetwork::UDPDataStructure::EntityTransfer>({EngineNetwork::UDPDataStructure::STATUS_GAME}, entity.first);
        singletons.getSingleton<EngineUtils::Queue<std::pair<EngineNetwork::DataStructure::Message, EngineNetwork::DataStructure::MessageTarget>>>(EngineServer::UDP::SingletonsEnum::SEND_LIST).push({{sendEntity}, {clientID, true}});
        singletons.getSingleton<std::function<void()>>(EngineServer::UDP::SingletonsEnum::SEND_CALLBACK)(); // Callback to send
        std::cout << "From room " << singletons.getSingleton<unsigned int>(EngineServer::UDP::SingletonsEnum::GAMEID) << " : ";
        std::cout << "Sending entity " << i << " at pos [" << entity.first.pos_x << ", " << entity.first.pos_y << "] at direction ["
        << entity.first.direction_x << ", " << entity.first.direction_y << "]\n";

    } catch (std::bad_cast const &error) {
        return;
    }
}

/**
 * @brief 
 * Send all the entities to the Clients
 * 
 * @param read 
 * @param r 
 * @param singletons 
 */
void clientSendGameDatas(std::pair<std::array<uint16_t, 50>, std::pair<std::size_t, unsigned int>> &read, Registry &r, EngineComponent::Singletons &singletons)
{
    sendEntities(read.second.second, r, singletons);
}

/**
 * @brief Client connected, sending him an id and all the entities
 */
void clientConnection(std::pair<std::array<uint16_t, 50>, std::pair<std::size_t, unsigned int>> &read, Registry &r, EngineComponent::Singletons &singletons)
{
    std::cout << "Client " << read.second.second << " connection request\n";
    std::vector<std::size_t> &playerAvailable = singletons.getSingleton<std::vector<std::size_t>>(EngineServer::UDP::SingletonsEnum::AVAILABLE_PLAYER);
    std::vector<unsigned int> &players = singletons.getSingleton<std::vector<unsigned int>>(EngineServer::UDP::SingletonsEnum::CORE_PLAYER);
    std::vector<std::size_t> &playersDestroyable = singletons.getSingleton<std::vector<std::size_t>>(EngineServer::UDP::SingletonsEnum::PLAYER_TO_DESTROY);
    // Get available id
    if (playerAvailable.size() != 0) {
        EngineNetwork::DataStructure::ID sendID;
        sendID.id = playerAvailable.front();
        players.push_back(read.second.second); // Save client id to check if he deconnected or not
        playersDestroyable.push_back(sendID.id); // Save client player to check if the player is destroyed or not
        playerAvailable.erase(playerAvailable.begin());

        try {
            EngineUtils::Queue<std::pair<EngineNetwork::DataStructure::Message, EngineNetwork::DataStructure::MessageTarget>> &sendList = singletons.getSingleton<EngineUtils::Queue<std::pair<EngineNetwork::DataStructure::Message, EngineNetwork::DataStructure::MessageTarget>>>(EngineServer::UDP::SingletonsEnum::SEND_LIST);
            std::pair<std::array<uint16_t, 50>, std::size_t> message = EngineNetwork::Serialisation::pack<EngineNetwork::DataStructure::ID>({EngineNetwork::DataStructure::CONNECTION}, sendID);
            // Send to client the available id
            std::cout << "Sending to client " << read.second.second << " player " << sendID.id << "\n";
            sendList.push({{message}, {read.second.second, true}});
            sendEntities(read.second.second, r, singletons);
        } catch (std::bad_cast const &error) {
            playerAvailable.push_back(sendID.id);
            return;
        }
    }
}

/**
 * @brief Notify all players that a entity got killed
 * 
 * @param r 
 * @param singletons 
 * @param id EntityID
 */
void sendKill(Registry &r, EngineComponent::Singletons &singletons, std::size_t id)
{
    auto &destroyablePlayer = singletons.getSingleton<std::vector<std::size_t>>(EngineServer::UDP::SingletonsEnum::PLAYER_TO_DESTROY);

    try {
        EngineNetwork::DataStructure::ID pID = {id};
        auto message = EngineNetwork::Serialisation::pack<EngineNetwork::DataStructure::ID>({EngineNetwork::UDPDataStructure::DESTROY}, pID);
        singletons.getSingleton<EngineUtils::Queue<std::pair<EngineNetwork::DataStructure::Message, EngineNetwork::DataStructure::MessageTarget>>>(EngineServer::UDP::SingletonsEnum::SEND_LIST).push({{message}, {0, false}});
        singletons.getSingleton<std::function<void()>>(EngineServer::UDP::SingletonsEnum::SEND_CALLBACK)(); // Callback to send

        // Check if the id killed is a player
        for (auto player = destroyablePlayer.begin(); player != destroyablePlayer.end(); ++player) {
            if (*player == id) {// Destroyed a player
                destroyablePlayer.erase(player);
                break;
            }
        }
    } catch (std::bad_cast const &error) {
    }
}

/**
 * @brief Move client player position and all its attached entities
 */
void clientMove(std::pair<std::array<uint16_t, 50>, std::pair<std::size_t, unsigned int>> &read, Registry &r, EngineComponent::Singletons &singletons)
{
    EngineNetwork::UDPDataStructure::PlayerMove data;

    try {
        data = std::any_cast<EngineNetwork::UDPDataStructure::PlayerMove>(EngineNetwork::Serialisation::unpack(read.first, read.second.first));
        std::cout << "From room " << singletons.getSingleton<unsigned int>(EngineServer::UDP::SingletonsEnum::GAMEID) << " : ";
        std::cout << "Client " << read.second.second << " sent move request on entity " << data.id << "\n";
    } catch (std::bad_cast const &error) {
        return;
    }
    auto &velocities = r.getComponents<EngineComponent::Direction>();
    auto const &attachedIDs = r.getComponents<EngineComponent::AttachedID>();
    auto &controllables = r.getComponents<EngineComponent::Controllable>();

    if (data.id < velocities.size() && data.id < controllables.size()) {
        auto &velocity = velocities[data.id];
        auto &control = controllables[data.id];
        if (velocity && control && control->controllable) {
            velocity->xDirection = data.moveX;
            velocity->yDirection = data.moveY;
            std::cout << "From room " << singletons.getSingleton<unsigned int>(EngineServer::UDP::SingletonsEnum::GAMEID) << " : ";
            std::cout << "Entity " << data.id << " new direction is [" << data.moveX << ", " << data.moveY << "]\n";
            sendEntity(data.id, r, singletons); // Send to other client that a player has moved

        }
    }

    // Move all attached entities
    for (std::size_t i = 0; i < velocities.size() && i < controllables.size() && i < attachedIDs.size(); ++i) {
        if (i == data.id)
            continue;
        auto &velocity = velocities[i];
        auto &control = controllables[i];
        auto const &aID = attachedIDs[i];

        if (velocity && control && control->controllable && aID && aID->parentID == data.id) {
            velocity->xDirection = data.moveX;
            velocity->yDirection = data.moveY;
            sendEntity(data.id, r, singletons); // Send to other client that a player has moved
        }
    }
}

/**
 * @brief Notify all players that the game ended
 */
void pingGameEnded(Registry &r, EngineComponent::Singletons &singletons)
{
    try {
        std::pair<std::array<uint16_t, 50>, std::size_t> sendEntity = EngineNetwork::Serialisation::pack({EngineNetwork::DataStructure::DECONNECTION});
        singletons.getSingleton<EngineUtils::Queue<std::pair<EngineNetwork::DataStructure::Message, EngineNetwork::DataStructure::MessageTarget>>>(EngineServer::UDP::SingletonsEnum::SEND_LIST).push({{sendEntity}, {0, false}});
        singletons.getSingleton<std::function<void()>>(EngineServer::UDP::SingletonsEnum::SEND_CALLBACK)(); // Callback to send
        std::cout << "Pinging everyone of game ending\n";
    } catch (std::bad_cast const &error) {
        return;
    }
}

/**
 * @brief 
 * Client has sent a request to fire a missile
 * 
 * @param read 
 * @param r 
 * @param singletons 
 */
void clientFire(std::pair<std::array<uint16_t, 50>, std::pair<std::size_t, unsigned int>> &read, Registry &r, EngineComponent::Singletons &singletons)
{
    EngineNetwork::DataStructure::IDStatus data;
    try {
        data = std::any_cast<EngineNetwork::DataStructure::IDStatus>(EngineNetwork::Serialisation::unpack(read.first, read.second.first));
        std::cout << "From room " << singletons.getSingleton<unsigned int>(EngineServer::UDP::SingletonsEnum::GAMEID) << " : ";
        std::cout << "Receive missile request from player " << data.id << " with " << (data.isOk == true ? "strong" : "normal")<< " status\n";
    } catch (std::bad_cast const &error) {
        return;
    }

    auto &missiles = r.getComponents<EngineComponent::ProjectileStats>();
    auto &controllables = r.getComponents<EngineComponent::Controllable>();
    auto const &attachedIDs = r.getComponents<EngineComponent::AttachedID>();

    EngineUtils::DeltaTime &deltaTime = singletons.getSingleton<EngineUtils::DeltaTime>(EngineServer::UDP::SingletonsEnum::DELTA_TIME);

    // Player fire
    if (data.id < missiles.size() && data.id < controllables.size()) {
        auto &missile = missiles[data.id];
        auto &control = controllables[data.id];
        if (missile && control && control->controllable) {
            System::spawnMissile(r, singletons, data.id, data.isOk);
        }
    }

    // All attached entities fire too
    for (std::size_t i = 0; i < missiles.size() && i < controllables.size() && i < attachedIDs.size(); ++i) {
        if (i == data.id)
            continue;
        auto &missile = missiles[i];
        auto &control = controllables[i];
        auto const &aID = attachedIDs[i];

        if (missile && control && control->controllable && aID && aID->parentID == data.id) {
            System::spawnMissile(r, singletons, i, data.isOk);
        }
    }
}