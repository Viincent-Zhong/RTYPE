/*
** EPITECH PROJECT, 2022
** Project R-TYPE
** File description:
** tcpServerGameLogic.cpp
*/

// #include <thread>
#include "tcpServerGameLogic.hpp"
#include "SafeVector.hpp"
#include "ServerTCPSingletons.hpp"
#include "Serialization.hpp"
#include <iostream>

/**
 * @brief 
 * Register the Client as a Player and give them an id
 * 
 * @param message 
 * @param singletons 
 */
void RegisterPlayer(std::pair<std::array<uint16_t, 50>, std::pair<std::size_t, unsigned int>> &message,
EngineComponent::Singletons &singletons)
{
    auto &players = singletons.getSingleton<EngineUtils::SafeVector<EngineServer::TCP::Player>>(EngineServer::TCP::SingletonEnum::PLAYERS);
    auto &sendList = singletons.getSingleton<EngineUtils::Queue<std::pair<EngineNetwork::DataStructure::Message, EngineNetwork::DataStructure::MessageTargets>>>
    (EngineServer::TCP::SingletonEnum::SEND_LIST);

    try {
        EngineNetwork::TCPDataStructure::RoomContent player = std::any_cast<EngineNetwork::TCPDataStructure::RoomContent>
        (EngineNetwork::Serialisation::unpack(message.first, message.second.first));
        // Giving player an ID
        EngineServer::TCP::Player newPlayer;
        newPlayer.id = message.second.second;
        for (unsigned int i = 0; i < 20; ++i)
            newPlayer.name[i] = player.player[i];
        players.push_back(newPlayer);
        std::cout << "Player " << message.second.second << ": register as " << player.player.data() << std::endl;

        //Sending back to player his new ID
        EngineNetwork::DataStructure::ID id = {newPlayer.id};
        auto send = EngineNetwork::Serialisation::pack<EngineNetwork::DataStructure::ID>(
            {EngineNetwork::TCPDataStructure::REGISTER},
            id
        );
        sendList.push({{send}, {{message.second.second}, true}});
        singletons.getSingleton<std::function<void()>>(EngineServer::TCP::SingletonEnum::SEND_CALLBACK)();
    } catch (std::bad_cast const &error) {
        std::cerr << "Player " << message.second.second << ": error when register:" << std::endl;
        std::cerr << error.what() << std::endl;
    }
}

/**
 * @brief 
 * Sending the Lobbies created to the Clients
 * 
 * @param message 
 * @param singletons 
 */
void sendRoomList(std::pair<std::array<uint16_t, 50>, std::pair<std::size_t, unsigned int>> &message,
EngineComponent::Singletons &singletons)
{
    auto &rooms = singletons.getSingleton<EngineUtils::SafeVector<EngineServer::TCP::ServerRoom>>(EngineServer::TCP::SingletonEnum::ROOMS);
    auto &sendList = singletons.getSingleton<EngineUtils::Queue<std::pair<EngineNetwork::DataStructure::Message, EngineNetwork::DataStructure::MessageTargets>>>
    (EngineServer::TCP::SingletonEnum::SEND_LIST);

    // Send all rooms
    for (auto room = rooms.begin(); room != rooms.end(); ++room) {
        // Send a room
        EngineNetwork::DataStructure::IDContentNumber content = {room->roomID, room->nbrPlayers};
        auto send = EngineNetwork::Serialisation::pack<EngineNetwork::DataStructure::IDContentNumber>(
            {EngineNetwork::TCPDataStructure::GET_ROOMS},
            content);
        sendList.push({{send}, {{message.second.second}, true}}); // send back to the client the room
        singletons.getSingleton<std::function<void()>>(EngineServer::TCP::SingletonEnum::SEND_CALLBACK)();
    }
    std::cout << "Player: " << message.second.second << " receive all rooms !" << std::endl;
}

/**
 * @brief 
 * Player is creating a Room
 * 
 * 
 * @param message 
 * @param singletons 
 */
void playerCreatingRoom(std::pair<std::array<uint16_t, 50>, std::pair<std::size_t, unsigned int>> &message,
EngineComponent::Singletons &singletons)
{
    auto &rooms = singletons.getSingleton<EngineUtils::SafeVector<EngineServer::TCP::ServerRoom>>(EngineServer::TCP::SingletonEnum::ROOMS);
    auto &sendList = singletons.getSingleton<EngineUtils::Queue<std::pair<EngineNetwork::DataStructure::Message, EngineNetwork::DataStructure::MessageTargets>>>
    (EngineServer::TCP::SingletonEnum::SEND_LIST);
    auto &nbrRooms = singletons.getSingleton<unsigned int>(EngineServer::TCP::SingletonEnum::NBR_ROOMS);

    // Create room with : RoomID, 1 player, current playerID
    nbrRooms++;
    rooms.push_back({nbrRooms, 1, {message.second.second}});
    std::cout << "Player " << message.second.second << ": create room: " << nbrRooms << std::endl;

    // Send back the new room with its id
    EngineNetwork::DataStructure::ID id = {nbrRooms};
    auto send = EngineNetwork::Serialisation::pack<EngineNetwork::DataStructure::ID>(
        {EngineNetwork::TCPDataStructure::CREATE_ROOM},
        id
    );
    sendList.push({{send}, {{message.second.second}, true}});
    singletons.getSingleton<std::function<void()>>(EngineServer::TCP::SingletonEnum::SEND_CALLBACK)();
}

/**
 * @brief 
 * Player is trying to join a Room 
 * 
 * @param message 
 * @param singletons 
 */
void playerJoiningRoom(std::pair<std::array<uint16_t, 50>, std::pair<std::size_t, unsigned int>> &message,
EngineComponent::Singletons &singletons)
{
    auto &rooms = singletons.getSingleton<EngineUtils::SafeVector<EngineServer::TCP::ServerRoom>>(EngineServer::TCP::SingletonEnum::ROOMS);
    auto &sendList = singletons.getSingleton<EngineUtils::Queue<std::pair<EngineNetwork::DataStructure::Message, EngineNetwork::DataStructure::MessageTargets>>>
    (EngineServer::TCP::SingletonEnum::SEND_LIST);
    EngineNetwork::DataStructure::ID roomID;

    try {
        roomID = std::any_cast<EngineNetwork::DataStructure::ID>(EngineNetwork::Serialisation::unpack(message.first, message.second.first));
    } catch (std::bad_cast const &error) {
        std::cout << "Received bad id\n";
        return;
    }
    if (roomID.id == 0) { // room ID cannot be 0
        std::cout << "Received bad id\n";
        return;
    }
    // Finding if the room has available space
    for (auto room = rooms.begin(); room != rooms.end(); ++room) {
        if (room->roomID == roomID.id && room->nbrPlayers < 4) {
            for (auto player : room->playersIDs) { // if already in the room don't add
                if (player == message.second.second) { // player is already in the room
                    std::cout << "Player " << message.second.second << " is already in the room "<< room->roomID << "\n";
                    return;
                }
            }
            // Room is available, add to the room new player ID
            room->playersIDs.push_back(message.second.second);
            ++room->nbrPlayers;

            // Send back the roomID
            EngineNetwork::DataStructure::ID id = {room->roomID};
            auto send = EngineNetwork::Serialisation::pack<EngineNetwork::DataStructure::ID>(
            {EngineNetwork::TCPDataStructure::JOIN_ROOM},
            id);
            sendList.push({{send}, {{message.second.second}, true}});
            singletons.getSingleton<std::function<void()>>(EngineServer::TCP::SingletonEnum::SEND_CALLBACK)();
            std::cout << "Player " << message.second.second << ": joined room " << room->roomID << std::endl;
            return;
        }
    }
}

/**
 * @brief 
 * Find the informations of the Players in a specific room
 * 
 * @param message 
 * @param singletons 
 */
void sendRoomPlayers(std::pair<std::array<uint16_t, 50>, std::pair<std::size_t, unsigned int>> &message,
EngineComponent::Singletons &singletons)
{
    auto &rooms = singletons.getSingleton<EngineUtils::SafeVector<EngineServer::TCP::ServerRoom>>(EngineServer::TCP::SingletonEnum::ROOMS);
    auto &sendList = singletons.getSingleton<EngineUtils::Queue<std::pair<EngineNetwork::DataStructure::Message, EngineNetwork::DataStructure::MessageTargets>>>
    (EngineServer::TCP::SingletonEnum::SEND_LIST);
    auto &players = singletons.getSingleton<EngineUtils::SafeVector<EngineServer::TCP::Player>>(EngineServer::TCP::SingletonEnum::PLAYERS);

    try {
        auto roomID = std::any_cast<EngineNetwork::DataStructure::ID>(EngineNetwork::Serialisation::unpack(message.first, message.second.first));
        for (auto room = rooms.begin(); room != rooms.end(); ++room) {
        // Finding the room
            if (room->roomID == roomID.id) {
                // Send all players
                for (auto playerID : room->playersIDs) {
                    // Finding player name
                    for (auto cmp = players.begin(); cmp != players.end(); ++cmp) {
                        // Send to client : roomID, playerID, playerName
                        EngineNetwork::TCPDataStructure::RoomContent playerInfo = {room->roomID, playerID};
                        std::cout << "Player " << message.second.second << ": " << cmp->name.data() << " is in room " << room->roomID << std::endl;
                        for (int i = 0; i < 20; ++i)
                            playerInfo.player[i] = cmp->name[i];
                        if (cmp->id == playerID) {
                            auto send = EngineNetwork::Serialisation::pack<EngineNetwork::TCPDataStructure::RoomContent>(
                                {EngineNetwork::TCPDataStructure::GET_PLAYER_IN_ROOM},
                                playerInfo
                            );
                            sendList.push({{send}, {{message.second.second}, true}});
                            singletons.getSingleton<std::function<void()>>(EngineServer::TCP::SingletonEnum::SEND_CALLBACK)();
                        }
                    }
                }
                return;
            }
        }
        std::cerr << "Player " << message.second.second << ": failed to get data players in room " << roomID.id << " because room not found" << std::endl;
    } catch (std::bad_cast const &error) {
        std::cerr << "Player " << message.second.second << ": error when getting all players in room" << std::endl;
        std::cerr << error.what() << std::endl;
    }

}

/**
 * @brief
 * Player is leaving the room
 */
void playerLeaveRoom(std::pair<std::array<uint16_t, 50>, std::pair<std::size_t, unsigned int>> &message,
EngineComponent::Singletons &singletons)
{
    auto &rooms = singletons.getSingleton<EngineUtils::SafeVector<EngineServer::TCP::ServerRoom>>(EngineServer::TCP::SingletonEnum::ROOMS);

    unsigned int id = message.second.second;
    // Search through all the rooms the player
    for (auto room = rooms.begin(); room != rooms.end(); ++room) {
        // Search through all the players in the room
        for (auto player = room->playersIDs.begin(); player != room->playersIDs.end(); ++player) {
            // Found player
            if (*player == id) {
                // Erase this player from the room
                room->playersIDs.erase(player);
                if (room->nbrPlayers > 0)
                    --room->nbrPlayers;
                std::cout << "Player " << message.second.second << " leaves the room" << room->roomID << std::endl;
                // If he was the last player remove the room
                if (room->playersIDs.size() == 0) {
                    std::cout << "There was 0 player, erased room " << room->roomID << "\n";
                    rooms.erase(room);
                }
                break;
            }
        }
        if (rooms.size() == 0)
            break;
    }
}

/**
 * @brief 
 * Player has crashed and his erased from the Lobby
 * 
 * @param message 
 * @param singletons 
 */
void playerCrash(std::pair<std::array<uint16_t, 50>, std::pair<std::size_t, unsigned int>> &message,
EngineComponent::Singletons &singletons)
{
    auto &sendList = singletons.getSingleton<EngineUtils::Queue<std::pair<EngineNetwork::DataStructure::Message, EngineNetwork::DataStructure::MessageTargets>>>
    (EngineServer::TCP::SingletonEnum::SEND_LIST);
    auto &players = singletons.getSingleton<EngineUtils::SafeVector<EngineServer::TCP::Player>>(EngineServer::TCP::SingletonEnum::PLAYERS);

    std::cout << "Player " << message.second.second << ": crash" << std::endl;
    // Make player leave his room
    playerLeaveRoom(message, singletons);

    unsigned int id = message.second.second;
    // Erase player from the list of players
    for (auto player = players.begin(); player != players.end(); ++player) {
        if (player->id == id) {
            std::cout << "Erased player " << message.second.second << " from lists\n"; 
            players.erase(player);
            break;
        }
    }
}

/**
 * @brief 
 * Players are trying to laucnh the game 
 * 
 * @param message 
 * @param singletons 
 */
void playerLaunchGame(std::pair<std::array<uint16_t, 50>, std::pair<std::size_t, unsigned int>> &message,
EngineComponent::Singletons &singletons)
{
    auto &rooms = singletons.getSingleton<EngineUtils::SafeVector<EngineServer::TCP::ServerRoom>>(EngineServer::TCP::SingletonEnum::ROOMS);

    // id of who launched the game
    unsigned int id = message.second.second;
    EngineNetwork::DataStructure::IDContentNumber roomID;
    try {
        // Get launched room
        roomID = std::any_cast<EngineNetwork::DataStructure::IDContentNumber>(EngineNetwork::Serialisation::unpack(message.first, message.second.first));
    } catch (std::bad_cast const &error) {
        std::cerr << "Player " << message.second.second << ": error when trying to launch a room" << std::endl;
        return;
    }
    for (auto room = rooms.begin(); room != rooms.end(); ++room) {
        // Look for the launched room and look if the one who asked the launch is the host of the game
        if (room->roomID == roomID.id && room->playersIDs.size() > 0 && room->playersIDs.front() == id) {
            // Add a request to launch a room
            singletons.getSingleton<EngineUtils::Queue<unsigned int>>(EngineServer::TCP::SingletonEnum::LAUNCHING_GAME).push(roomID.id);
            singletons.getSingleton<unsigned int>(EngineServer::TCP::SingletonEnum::GAME_LEVEL) = roomID.number;
            singletons.getSingleton<std::function<void()>>(EngineServer::TCP::SingletonEnum::LAUNCHING_CALLBACK)();
            std::cout << "Player " << message.second.second << ": launch game in room: " << roomID.id << std::endl;
            break;
        }
    }
}
