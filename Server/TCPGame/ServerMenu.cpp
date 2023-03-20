/*
** EPITECH PROJECT, 2022
** Project R-TYPE
** File description:
** ServerMenu.cpp
*/

#include "asio.hpp"
#include "ServerMenu.hpp"
#include "tcpServerGameLogic.hpp"
#include "ServerTCPSingletons.hpp"
#include "SafeVector.hpp"
#include "Serialization.hpp"
#include "TCPDataStructure.hpp"
#include "startServer.hpp"

EngineServer::ServerMenu::ServerMenu(EngineNetwork::INetwork *server) : _server(server)
{
    // CLIENT_DISCONNECTION
    _list[EngineNetwork::TCPDataStructure::REGISTER] = RegisterPlayer;

    _list[EngineNetwork::TCPDataStructure::GET_ROOMS] = sendRoomList;
    _list[EngineNetwork::TCPDataStructure::GET_PLAYER_IN_ROOM] = sendRoomPlayers;

    _list[EngineNetwork::TCPDataStructure::CREATE_ROOM] = playerCreatingRoom;
    _list[EngineNetwork::TCPDataStructure::JOIN_ROOM] = playerJoiningRoom;

    _list[EngineNetwork::TCPDataStructure::LAUNCH_GAME] = playerLaunchGame;
    _list[EngineNetwork::TCPDataStructure::LEAVE_ROOM] = playerLeaveRoom;
    _list[EngineNetwork::TCPDataStructure::CLIENT_DISCONNECTION] = playerCrash;
}

EngineServer::ServerMenu::~ServerMenu()
{
    stop();
}

/**
 * @brief 
 * Disconnect the TCP Server and all the threads, Server-side
 * 
 */
void EngineServer::ServerMenu::stop()
{
    _server.get()->stop();
    _end = true;

    // Erase games
    for (auto game = _games.begin(); game != _games.end(); ++game) {
        if (game->first.joinable())
            game->first.join();
        _games.erase(game);
        if (_games.size() == 0)
            break;
    }
}

/**
 * @brief 
 * Initialize all the game, Server-side
 * 
 */
void EngineServer::ServerMenu::initGame()
{
    _singletons.setSingleton<unsigned int>(EngineServer::TCP::SingletonEnum::NBR_ROOMS, 0);
    _singletons.setSingleton<EngineUtils::SafeVector<EngineServer::TCP::ServerRoom>>(EngineServer::TCP::SingletonEnum::ROOMS);
    _singletons.setSingleton<EngineUtils::SafeVector<EngineServer::TCP::Player>>(EngineServer::TCP::SingletonEnum::PLAYERS);
    _singletons.setSingleton<unsigned int>(EngineServer::TCP::SingletonEnum::GAME_LEVEL, 1);
    _singletons.setSingleton<EngineUtils::Queue<std::pair<EngineNetwork::DataStructure::Message, EngineNetwork::DataStructure::MessageTargets>>>
    (EngineServer::TCP::SingletonEnum::SEND_LIST);
    _singletons.setSingleton<EngineUtils::Queue<unsigned int>>(EngineServer::TCP::SingletonEnum::LAUNCHING_GAME);
    _singletons.setSingleton<std::function<void()>>(EngineServer::TCP::SingletonEnum::SEND_CALLBACK);
    _singletons.setSingleton<std::function<void()>>(EngineServer::TCP::SingletonEnum::LAUNCHING_CALLBACK);

    _singletons.getSingleton<std::function<void()>>(EngineServer::TCP::SingletonEnum::LAUNCHING_CALLBACK) = [this]() {launchingRooms();};
}

void EngineServer::ServerMenu::gameLoop()
{
}

/**
 * @brief Server should never end
 * @return true 
 * @return false 
 */
bool EngineServer::ServerMenu::endCondition()
{
    return false;
}

/**
 * @brief 
 * Initialize Network, Server-side
 * 
 */
void EngineServer::ServerMenu::initNetwork()
{
    _server.get()->start();
}

/**
 * @brief 
 * Initialize the function for sending messages to ClientS
 * 
 */
void EngineServer::ServerMenu::initNetworkSend()
{
    _singletons.getSingleton<std::function<void()>>(EngineServer::TCP::SingletonEnum::SEND_CALLBACK) = [this]() {handleSendingMessages();};
}

/**
 * @brief 
 * Initialize the loop function for reading messages from Clients
 * 
 */
void EngineServer::ServerMenu::initNetworkRead()
{
    _server.get()->loopRead([this]() {handleReceivedMessages();});
}

/**
 * @brief 
 * Handle the messages that must be received from Clients 
 * 
 */
void EngineServer::ServerMenu::handleReceivedMessages()
{
    auto &listAction = _server.get()->getReadList();

    while (listAction.size() != 0) {
        auto readed = listAction.front();
        unsigned int code = readed.first.at(0);

        auto func = _list.find(code);
        if (func != _list.end()) {
            func->second(readed, _singletons);
        }
        listAction.pop();
    }
}

/**
 * @brief 
 * Handle the messages that must be sent to Clients
 * 
 */
void EngineServer::ServerMenu::handleSendingMessages()
{
    auto &sendList = _singletons.getSingleton<EngineUtils::Queue<std::pair<EngineNetwork::DataStructure::Message, EngineNetwork::DataStructure::MessageTargets>>>
    (EngineServer::TCP::SingletonEnum::SEND_LIST);

    while (sendList.size() != 0) {
        auto head = sendList.front();
        if (head.second.privateMessage) {
            for (auto client : head.second.idTargets)
                _server.get()->writeToID(client, head.first.message);
        } else
            _server.get()->writeToAll(head.first.message);
        sendList.pop();
    }
}

/**
 * @brief 
 * Check if the port is already in use
 * 
 * @param port 
 * @return true 
 * @return false 
 */
static bool portInUse(uint16_t port)
{
    asio::io_context svc;
    asio::ip::tcp::acceptor a(svc);

    asio::error_code ec;
    a.open(asio::ip::tcp::v4(), ec);
    a.bind({ asio::ip::tcp::v4(), port }, ec);

    return ec == asio::error::address_in_use;
}

/**
 * @brief 
 * Handle all the existing Lobbies
 * 
 */
void EngineServer::ServerMenu::launchingRooms()
{
    const std::vector<std::string> listLevels = {"", "/Waves1.csv", "/Waves2.csv", "/Waves3.csv"};
    auto &launchRequets = _singletons.getSingleton<EngineUtils::Queue<unsigned int>>(EngineServer::TCP::SingletonEnum::LAUNCHING_GAME);
    auto &rooms = _singletons.getSingleton<EngineUtils::SafeVector<EngineServer::TCP::ServerRoom>>(EngineServer::TCP::SingletonEnum::ROOMS);

    while (launchRequets.size() != 0) {
        // Room ID
        auto roomID = launchRequets.front();
        uint16_t i = _startPort;
        bool freePort = false;
        for (; i < _maxPort; ++i)
            if (!portInUse(i)) { // Found a port
                freePort = true;
                break;
            }

        if (freePort == false) { // If didn't find a port don't do anything
            std::cout << "Couldn't find a free port\n";
            launchRequets.pop();
            return;
        }
        // Set room port
        std::cout << "Set port " << i << "\n";
        for (auto room = rooms.begin(); room != rooms.end(); ++room)
            if (room->roomID == roomID) {
                room->port = i;
                break;
            }

        // Create a callback to ping players of the room when game starting
        std::function<void(unsigned int)> pingClientToStart = [this](unsigned int roomID) {
            pingStartRoom(roomID);
        };

        // Create a callback to erase the created game
        std::function<void(unsigned int)> eraseThreadedGame = [this](unsigned int roomID) {
            threadGameEnded(roomID);
        };

        std::cout << _singletons.getSingleton<unsigned int>(EngineServer::TCP::SingletonEnum::GAME_LEVEL) << std::endl;
        // Start new game
        _games.push_back({
            std::thread(startUDPServer,
            i, // port
            roomID, // roomID
            pingClientToStart, // Callback to ping clients of the room when game start
            eraseThreadedGame, // Callback for the server to know when the game ended
            listLevels.at(_singletons.getSingleton<unsigned int>(EngineServer::TCP::SingletonEnum::GAME_LEVEL))
        ),
        roomID
        });

        launchRequets.pop();
        _startPort++;
    }
}

/**
 * @brief 
 * Ping the Client in the Start Room-
 * 
 * @param roomID 
 */
void EngineServer::ServerMenu::pingStartRoom(unsigned int roomID)
{
    auto &rooms = _singletons.getSingleton<EngineUtils::SafeVector<EngineServer::TCP::ServerRoom>>(EngineServer::TCP::SingletonEnum::ROOMS);
    auto &sendList = _singletons.getSingleton<EngineUtils::Queue<std::pair<EngineNetwork::DataStructure::Message, EngineNetwork::DataStructure::MessageTargets>>>
    (EngineServer::TCP::SingletonEnum::SEND_LIST);


    for (auto room = rooms.begin(); room != rooms.end(); ++room) {
        // Found room
        if (room->roomID == roomID) {
            // Send room port
            EngineNetwork::DataStructure::IDContentNumber roomPort = {room->roomID, room->port};
            auto message = EngineNetwork::Serialisation::pack<EngineNetwork::DataStructure::IDContentNumber>(
                {EngineNetwork::TCPDataStructure::LAUNCH_GAME},
                roomPort
            );
            // Ping all players of the room that the game started
            for (auto player : room->playersIDs) {
                sendList.push({{message}, {{player, true}}});
                std::cout << "Sending entities to player " << player << "\n";
            }
            _singletons.getSingleton<std::function<void()>>(EngineServer::TCP::SingletonEnum::SEND_CALLBACK)();
        }
    }
}

/**
 * @brief 
 * Erase a lobby when the game inside that lobby ended
 * 
 * @param roomID 
 */
void EngineServer::ServerMenu::threadGameEnded(unsigned int roomID)
{
    // Search through all the games the game with the corresponding roomID
    for (auto game = _games.begin(); game != _games.end(); ++game) {
        if (game->second == roomID) {// Found correct game
            game->first.detach(); 
            _games.erase(game); // Erase game
            break;
        }
    }
}