/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** tcpClientGameLogic
*/

#include "tcpClientGameLogic.hpp"
#include "DataStructure.hpp"
#include "ClientTCPSingletons.hpp"
#include "Text/TextSystems.hpp"
#include "Serialization.hpp"

/**
 * @brief 
 * Get the Register object from the TCP Network Server,
 * get an id for the player
 * 
 * @param data 
 * @param r 
 * @param singleton 
 */
void Register(std::pair<std::array<uint16_t, 50>, std::pair<std::size_t, unsigned int>> &data, Registry &r, EngineComponent::Singletons &singleton)
{
    try {
        EngineNetwork::DataStructure::ID id = std::any_cast<EngineNetwork::DataStructure::ID>(EngineNetwork::Serialisation::unpack(data.first, data.second.first));
        singleton.getSingleton<unsigned int>(EngineClient::TCP::SingletonEnum::ID) = id.id;
        std::cout << "Registered as id " << id.id << "\n";
        std::to_string(singleton.getSingleton<unsigned int>(EngineClient::TCP::SingletonEnum::NAME)) = "";
    } catch (std::bad_cast const &error) {
    }
}

/**
 * @brief 
 * Get the Lobbies List object from the TCP Network Server
 * 
 * @param data 
 * @param r 
 * @param singleton 
 */
void getRoomsList(std::pair<std::array<uint16_t, 50>, std::pair<std::size_t, unsigned int>> &data, Registry &r, EngineComponent::Singletons &singleton)
{
    try {
        EngineNetwork::DataStructure::IDContentNumber content = std::any_cast<EngineNetwork::DataStructure::IDContentNumber>(EngineNetwork::Serialisation::unpack(data.first, data.second.first));
        // Add to registry a room ID + room nbr Players
        auto &rooms = r.getComponents<EngineComponent::ListGame>();
        bool isInit = false;
        for (int i = 0; i < rooms.size(); ++i) {
            auto &room = rooms[i];
            if (room)
                if (content.id == room.value().id) {
                    room.value().nbPlayers = content.number;
                    isInit = true;
                    break;
                }
        }
        if (!isInit) {
            auto id = r.spawnEntity();
            r.addComponent<EngineComponent::ListGame>(id, {static_cast<unsigned int>(content.id), content.number});
        }
    } catch (std::bad_cast const &error) {
    }
}

/**
 * @brief 
 * Get the Lobby object from the TCP Network Server
 * 
 * @param data 
 * @param r 
 * @param singleton 
 */
void createdRoom(std::pair<std::array<uint16_t, 50>, std::pair<std::size_t, unsigned int>> &data, Registry &r, EngineComponent::Singletons &singleton)
{
    try {
        EngineNetwork::DataStructure::ID id = std::any_cast<EngineNetwork::DataStructure::ID>(EngineNetwork::Serialisation::unpack(data.first, data.second.first));
        singleton.getSingleton<unsigned int>(EngineClient::TCP::SingletonEnum::ROOM_ID) = id.id;
        if (id.id == 0)
            singleton.getSingleton<std::unordered_map<std::string, System::DataText>>(EngineClient::TCP::SingletonEnum::TEXTS)["message error create room"] = {"Assets/Fonts/Roboto-Bold.ttf", "Failed create room", 1.0f, {200.0f, 200.0f}, 1.0f, PadaEngine::PADA_RED};
        else
            singleton.getSingleton<std::size_t>(EngineClient::TCP::SingletonEnum::LAYER) = 5;
        std::cout << "Room " << id.id << " created\n";
    } catch (std::bad_cast const &error) {
    }
}

/**
 * @brief 
 * Get the Join Room object from the TCP Network Server
 * 
 * @param data 
 * @param r 
 * @param singleton 
 */
void joinedRoom(std::pair<std::array<uint16_t, 50>, std::pair<std::size_t, unsigned int>> &data, Registry &r, EngineComponent::Singletons &singleton)
{
    try {
        EngineNetwork::DataStructure::ID id = std::any_cast<EngineNetwork::DataStructure::ID>(EngineNetwork::Serialisation::unpack(data.first, data.second.first));
        singleton.getSingleton<unsigned int>(EngineClient::TCP::SingletonEnum::ROOM_ID) = id.id;
        singleton.getSingleton<std::size_t>(EngineClient::TCP::SingletonEnum::LAYER) = 5;
        std::cout << "Joined room " << id.id << "\n";
    } catch (std::bad_cast const &error) {
    }
}

/**
 * @brief
 * Get the Room Players object from the TCP Network Server
 * 
 * @param data 
 * @param r 
 * @param singleton 
 */
void getRoomPlayers(std::pair<std::array<uint16_t, 50>, std::pair<std::size_t, unsigned int>> &data, Registry &r, EngineComponent::Singletons &singleton)
{
    try {
        EngineNetwork::TCPDataStructure::RoomContent content = std::any_cast<EngineNetwork::TCPDataStructure::RoomContent>(EngineNetwork::Serialisation::unpack(data.first, data.second.first));
        auto &rooms = r.getComponents<EngineComponent::RoomPlayer>();
        bool isInit = false;

        // normalement pas besoin mais garde au cas ou
        // for (int i = 0; i < rooms.size(); ++i) {
            // auto &room = rooms[i];
            // if (room)
                // if (content.roomID == room.value().roomID) {
                    // room.value().playerName = content.player;
                    // room.value().playerID = content.playerID;
                    // room.value().roomID = content.roomID;
                    // isInit = true;
                    // return;
                // }
        // }
        r.addComponent<EngineComponent::RoomPlayer>(rooms.size(), {content.player, content.playerID, content.roomID});
    } catch (std::bad_cast const &error) {
    }
}

/**
 * @brief 
 * Get the Game Started object from the TCP Network Server
 * 
 * @param data 
 * @param r 
 * @param singleton 
 */
void launchedGame(std::pair<std::array<uint16_t, 50>, std::pair<std::size_t, unsigned int>> &data, Registry &r, EngineComponent::Singletons &singleton)
{
    try {
        // Get port of launched game
        EngineNetwork::DataStructure::IDContentNumber id = std::any_cast<EngineNetwork::DataStructure::IDContentNumber>(EngineNetwork::Serialisation::unpack(data.first, data.second.first));
        if (id.number != 0)
            singleton.getSingleton<unsigned int>(EngineClient::TCP::SingletonEnum::GAME_LAUNCHED) = id.number;
        std::cout << "Game launched\n";
    } catch (std::bad_cast const &error) {
    }
}

/**
 * @brief 
 * Ask to be registered on the server
 * 
 * @param singleton 
 * @param id 
 */
void askRegister(EngineComponent::Singletons &singleton, unsigned int id)
{
    auto &sendList = singleton.getSingleton<EngineUtils::Queue<std::pair<EngineNetwork::DataStructure::Message, EngineNetwork::DataStructure::MessageTarget>>>(EngineClient::TCP::SingletonEnum::SEND_LIST);
    auto &name = singleton.getSingleton<std::array<char, 20>>(EngineClient::TCP::NAME);

    EngineNetwork::TCPDataStructure::RoomContent sendName;
    // Copying current name
    sendName.playerID = 0;
    sendName.roomID = 0;
    for (unsigned int i = 0; i < 20; ++i)
        sendName.player[i] = name[i];

    // Sending current name
    auto send = EngineNetwork::Serialisation::pack<EngineNetwork::TCPDataStructure::RoomContent>(
        {EngineNetwork::TCPDataStructure::REGISTER},
        sendName
    );
    sendList.push({
        {send}, {0, false}
    });
    singleton.getSingleton<std::function<void()>>(EngineClient::TCP::SingletonEnum::SEND_CALLBACK)(); // Callback to send
}

/**
 * @brief 
 * Ask the TCP Server on Room List scene if you can enter a lobby
 * 
 * @param singleton 
 * @param id 
 */
void askRoomsList(EngineComponent::Singletons &singleton, unsigned int id)
{
    auto &sendList = singleton.getSingleton<EngineUtils::Queue<std::pair<EngineNetwork::DataStructure::Message, EngineNetwork::DataStructure::MessageTarget>>>(EngineClient::TCP::SingletonEnum::SEND_LIST);

    auto send = EngineNetwork::Serialisation::pack({EngineNetwork::TCPDataStructure::GET_ROOMS});
    sendList.push({
        {send}, {0, false}
    });
    singleton.getSingleton<std::function<void()>>(EngineClient::TCP::SingletonEnum::SEND_CALLBACK)(); // Callback to send
}

/**
 * @brief 
 * Ask the TCP Server on Creating Room scene if you can enter a lobby
 * 
 * @param singleton 
 * @param id 
 */
void askCreatingRoom(EngineComponent::Singletons &singleton, unsigned int id)
{
    auto &sendList = singleton.getSingleton<EngineUtils::Queue<std::pair<EngineNetwork::DataStructure::Message, EngineNetwork::DataStructure::MessageTarget>>>(EngineClient::TCP::SingletonEnum::SEND_LIST);

    auto send = EngineNetwork::Serialisation::pack({EngineNetwork::TCPDataStructure::CREATE_ROOM});
    sendList.push({
        {send}, {0, false}
    });
    singleton.getSingleton<std::function<void()>>(EngineClient::TCP::SingletonEnum::SEND_CALLBACK)(); // Callback to send
}

/**
 * @brief 
 * Ask the TCP Server on Joining Room scene if you can enter a lobby
 * 
 * @param singleton 
 * @param id 
 */
void askJoiningRoom(EngineComponent::Singletons &singleton, unsigned int id)
{
    auto &sendList = singleton.getSingleton<EngineUtils::Queue<std::pair<EngineNetwork::DataStructure::Message, EngineNetwork::DataStructure::MessageTarget>>>(EngineClient::TCP::SingletonEnum::SEND_LIST);

    // Ask to join a room
    EngineNetwork::DataStructure::ID roomID = {(std::size_t)id};
    auto send = EngineNetwork::Serialisation::pack<EngineNetwork::DataStructure::ID>(
        {EngineNetwork::TCPDataStructure::JOIN_ROOM},
        {roomID}
    );
    sendList.push({
        {send}, {0, false}
    });
    singleton.getSingleton<std::function<void()>>(EngineClient::TCP::SingletonEnum::SEND_CALLBACK)(); // Callback to send
}

/**
 * @brief 
 * Ask the TCP Server on Lobby Room scene for their informations
 * 
 * @param singleton 
 * @param id 
 */
void askRoomPlayers(EngineComponent::Singletons &singleton, unsigned int id)
{
    auto &sendList = singleton.getSingleton<EngineUtils::Queue<std::pair<EngineNetwork::DataStructure::Message, EngineNetwork::DataStructure::MessageTarget>>>(EngineClient::TCP::SingletonEnum::SEND_LIST);

    // Asking players of current room ID
    EngineNetwork::DataStructure::ID roomID = {(std::size_t)singleton.getSingleton<unsigned int>(EngineClient::TCP::SingletonEnum::ROOM_ID)};
    auto send = EngineNetwork::Serialisation::pack<EngineNetwork::DataStructure::ID>(
        {EngineNetwork::TCPDataStructure::GET_PLAYER_IN_ROOM},
        {roomID}
    );
    sendList.push({
        {send}, {0, false}
    });
    std::cout << "Send request to get players of the room " << roomID.id << "\n";
    singleton.getSingleton<std::function<void()>>(EngineClient::TCP::SingletonEnum::SEND_CALLBACK)(); // Callback to send
}

/**
 * @brief 
 * Ask the TCP Server on Lobby Room scene if you can start the game
 * 
 * @param singleton 
 * @param id 
 */
void askLaunchingGame(EngineComponent::Singletons &singleton, unsigned int id)
{
    auto &sendList = singleton.getSingleton<EngineUtils::Queue<std::pair<EngineNetwork::DataStructure::Message, EngineNetwork::DataStructure::MessageTarget>>>(EngineClient::TCP::SingletonEnum::SEND_LIST);
    unsigned int level = std::stoi(singleton.getSingleton<std::string>(EngineClient::TCP::GAME_LEVEL));

    // Asking to launch the game from current room ID
    EngineNetwork::DataStructure::IDContentNumber roomID = {(std::size_t)singleton.getSingleton<unsigned int>(EngineClient::TCP::SingletonEnum::ROOM_ID), level};
    auto send = EngineNetwork::Serialisation::pack<EngineNetwork::DataStructure::IDContentNumber>(
        {EngineNetwork::TCPDataStructure::LAUNCH_GAME},
        {roomID}
    );
    sendList.push({
        {send}, {0, false}
    });
        std::cout << "Send request to launch game from room " << roomID.id << " with level " << level << "\n";
    singleton.getSingleton<std::function<void()>>(EngineClient::TCP::SingletonEnum::SEND_CALLBACK)(); // Callback to send
}

/**
 * @brief 
 * Send a message to the TCP Server that a player is leavign the lobby
 * 
 * @param singleton 
 * @param id 
 */
void sendLeavingRoom(EngineComponent::Singletons &singleton, unsigned int id)
{
    auto &sendList = singleton.getSingleton<EngineUtils::Queue<std::pair<EngineNetwork::DataStructure::Message, EngineNetwork::DataStructure::MessageTarget>>>(EngineClient::TCP::SingletonEnum::SEND_LIST);
    auto &roomID = singleton.getSingleton<unsigned int>(EngineClient::TCP::SingletonEnum::ROOM_ID);

    // Leaving current room ID
    EngineNetwork::DataStructure::ID sRoomID = {(std::size_t)roomID};
    auto send = EngineNetwork::Serialisation::pack<EngineNetwork::DataStructure::ID>(
        {EngineNetwork::TCPDataStructure::LEAVE_ROOM},
        {sRoomID}
    );
    sendList.push({
        {send}, {0, false}
    });
    singleton.getSingleton<std::function<void()>>(EngineClient::TCP::SingletonEnum::SEND_CALLBACK)(); // Callback to send

    roomID = 0;
}

/**
 * @brief 
 * Send a message to the TCP Server that a player is leavign the lobby and in disconnected from the server
 * 
 * @param singleton 
 * @param id 
 */
void sendDeconnecting(EngineComponent::Singletons &singleton, unsigned int id)
{
    auto &sendList = singleton.getSingleton<EngineUtils::Queue<std::pair<EngineNetwork::DataStructure::Message, EngineNetwork::DataStructure::MessageTarget>>>(EngineClient::TCP::SingletonEnum::SEND_LIST);

    // End the game
    auto send = EngineNetwork::Serialisation::pack({EngineNetwork::TCPDataStructure::CLIENT_DISCONNECTION});
    sendList.push({
        {send}, {0, false}
    });
    singleton.getSingleton<std::function<void()>>(EngineClient::TCP::SingletonEnum::SEND_CALLBACK)(); // Callback to send
    singleton.getSingleton<bool>(EngineClient::TCP::SingletonEnum::LEAVING) = true;
}

/**
 * @brief Got deconnected from the server
 * 
 * @param data 
 * @param r 
 * @param singleton 
 */
void deconnected(std::pair<std::array<uint16_t, 50>, std::pair<std::size_t, unsigned int>> &data, Registry &r, EngineComponent::Singletons &singleton)
{
    singleton.getSingleton<bool>(EngineClient::TCP::SingletonEnum::END) = true;
}
