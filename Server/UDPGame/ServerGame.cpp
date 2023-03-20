/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** ServerGame
*/

#include "PhysiqueSystems.hpp"
#include "SendDataSystems.hpp"
#include "EnemySystems.hpp"

#include "Player.hpp"
#include "Missile.hpp"
#include "Auxiliaries.hpp"
#include "Enemy.hpp"
#include "EntityGeneration.hpp"

#include "EngineComponents.hpp"
#include "DrawC.hpp"
#include "logicGameServer.hpp"
#include "UDPDataStructure.hpp"
#include "Singletons.hpp"
#include "UDPSingletons.hpp"
#include "DataStructure.hpp"

#include "ServerGame.hpp"

static void setSingletons(EngineComponent::Singletons &singletons)
{
    EngineUtils::Timer &oneSecTimer = singletons.getSingleton<EngineUtils::Timer>(EngineServer::UDP::SingletonsEnum::ONE_SEC_TIMER);
    EngineUtils::Timer &miniTimer = singletons.getSingleton<EngineUtils::Timer>(EngineServer::UDP::SingletonsEnum::MINI_TIMER);
    EngineUtils::DeltaTime &deltaTime = singletons.getSingleton<EngineUtils::DeltaTime>(EngineServer::UDP::SingletonsEnum::DELTA_TIME);

    if (oneSecTimer.TimerDone())
        oneSecTimer.RestartTimer();
    oneSecTimer.UpdateTimer(deltaTime.getDeltaTime());
    if (miniTimer.TimerDone())
        miniTimer.RestartTimer();
    miniTimer.UpdateTimer(deltaTime.getDeltaTime());
    deltaTime.updateDeltaTime();
}

/**
 * @brief 
 * Run all the Systems
 * 
 * @param r 
 * @param singletons 
 * @param systems 
 */
static void runSystems(Registry &r, EngineComponent::Singletons &singletons, EngineSystem::Systems &systems)
{
    systems.runSystem(r, singletons, EngineServer::ServerGame::SystemEnum::SPHYSIQUE);
    systems.runSystem(r, singletons, EngineServer::ServerGame::SystemEnum::SNETWORK);
    systems.runSystem(r, singletons, EngineServer::ServerGame::SystemEnum::SENEMY);
}

/**
 * @brief 
 * Generate a wave of enemies
 * 
 * @param r 
 * @param singletons 
 */
void generateWave(Registry &r, EngineComponent::Singletons &singletons)
{
    auto &dataWaves = singletons.getSingleton<std::vector<std::vector<std::string>>>(EngineServer::UDP::SingletonsEnum::WAVES);
    std::size_t id;

    for (int i = 0; i != std::atoi(dataWaves.at(0).at(0).c_str()); ++i) {
        id = r.entityCache.addEntityFromJSON(r, EngineServer::Init::IENEMY, dataWaves.at(0).at(1));
        sendEntity(i, r, singletons);
    }
    for (int i = 0; i != std::atoi(dataWaves.at(0).at(2).c_str()); ++i) {
        id = r.entityCache.addEntityFromJSON(r, EngineServer::Init::IENEMY, dataWaves.at(0).at(3));
        sendEntity(i, r, singletons);
    }
    for (int i = 0; i != std::atoi(dataWaves.at(0).at(4).c_str()); ++i) {
        id = r.entityCache.addEntityFromJSON(r, EngineServer::Init::IENEMY, dataWaves.at(0).at(5));
        sendEntity(i, r, singletons);
    }
    for (int i = 0; i != std::atoi(dataWaves.at(0).at(6).c_str()); ++i) {
        id = r.entityCache.addEntityFromJSON(r, EngineServer::Init::IENEMY, dataWaves.at(0).at(7));
        sendEntity(i, r, singletons);
    }
    for (int i = 0; i != std::atoi(dataWaves.at(0).at(8).c_str()); ++i) {
        id = r.entityCache.addEntityFromJSON(r, EngineServer::Init::IENEMY, dataWaves.at(0).at(9));
        sendEntity(i, r, singletons);
    }
}

namespace EngineServer {
    ServerGame::ServerGame()
    {
        _translateList[EngineNetwork::DataStructure::CONNECTION] = clientConnection;
        _translateList[EngineNetwork::UDPDataStructure::MOVE_PLAYER] = clientMove;
	    _translateList[EngineNetwork::UDPDataStructure::PLAYER_FIRE] = clientFire;
	    _translateList[EngineNetwork::DataStructure::DECONNECTION] = clientDisconnect;
	    _translateList[EngineNetwork::UDPDataStructure::STATUS_GAME] = clientSendGameDatas;
    }

    ServerGame::ServerGame(EngineNetwork::INetwork *server, unsigned int id, std::string const &waves) : _server(server), _gameID(id), _waves(waves)
    {
        _translateList[EngineNetwork::DataStructure::CONNECTION] = clientConnection;
        _translateList[EngineNetwork::UDPDataStructure::MOVE_PLAYER] = clientMove;
	    _translateList[EngineNetwork::UDPDataStructure::PLAYER_FIRE] = clientFire;
	    _translateList[EngineNetwork::DataStructure::DECONNECTION] = clientDisconnect;
	    _translateList[EngineNetwork::UDPDataStructure::STATUS_GAME] = clientSendGameDatas;
    }

    ServerGame::~ServerGame()
    {
        _server.get()->stop();
        _end = true;
    }

    /**
     * @brief End if there is no more players
     * @return true 
     * @return false 
     */
    bool ServerGame::endCondition()
    {
        auto &dataWaves = _singletons.getSingleton<std::vector<std::vector<std::string>>>(EngineServer::UDP::SingletonsEnum::WAVES);
        if ((_singletons.getSingleton<std::vector<unsigned int>>(EngineServer::UDP::SingletonsEnum::CORE_PLAYER).size() == 0 || // THERE IS NO CLIENT
            _singletons.getSingleton<std::vector<std::size_t>>(EngineServer::UDP::SingletonsEnum::PLAYER_TO_DESTROY).size() == 0) && // THERE IS NO CONTROLLABLE PLAYER
            _singletons.getSingleton<std::vector<std::size_t>>(EngineServer::UDP::SingletonsEnum::AVAILABLE_PLAYER).size() != 4 &&
            _init == true) {
            pingGameEnded(_register, _singletons);
            _end = true;
            std::cout << "UDP : Game " << _gameID << " closing\n";
            _server.get()->stop();
            return true;
        }
        if (dataWaves.size() == 0) {
            pingGameEnded(_register, _singletons);
            return true;
        }
        return false;
    }

    /**
     * @brief 
     * Main Loop for the Game, UDP Server Side
     * 
     */
    void ServerGame::gameLoop()
    {
        runSystems(_register, _singletons, _systems);

        auto &dataWaves = _singletons.getSingleton<std::vector<std::vector<std::string>>>(EngineServer::UDP::SingletonsEnum::WAVES);
        if (_singletons.getSingleton<bool>(EngineServer::UDP::SingletonsEnum::WAVER_OVER)) {
            endCondition();
            if (dataWaves.size() > 0) {
                dataWaves.erase(dataWaves.begin());
                if (!dataWaves.empty())
                    generateWave(_register, _singletons);
            }
        }
        setSingletons(_singletons);
    }

    /**
     * @brief 
     * Initialize all the objects for the game, UDP Server-side
     * 
     */
    void ServerGame::initGame()
    {
        _systems.setSystem<System::Physique>(SystemEnum::SPHYSIQUE);
        _systems.setSystem<System::Network>(SystemEnum::SNETWORK);
        _systems.setSystem<System::Enemy>(SystemEnum::SENEMY);

        _singletons.setSingleton<std::vector<std::size_t>>(EngineServer::UDP::SingletonsEnum::AVAILABLE_PLAYER);
        _singletons.setSingleton<std::vector<std::size_t>>(EngineServer::UDP::SingletonsEnum::PLAYER_TO_DESTROY);
        _singletons.setSingleton<std::vector<unsigned int>>(EngineServer::UDP::SingletonsEnum::CORE_PLAYER);
        _singletons.setSingleton<EngineUtils::Queue<std::pair<EngineNetwork::DataStructure::Message, EngineNetwork::DataStructure::MessageTarget>>>(EngineServer::UDP::SingletonsEnum::SEND_LIST);
        _singletons.setSingleton<EngineUtils::DeltaTime>(EngineServer::UDP::SingletonsEnum::DELTA_TIME);
        _singletons.setSingleton<std::pair<unsigned int, unsigned int>>(EngineServer::UDP::SingletonsEnum::WINDOW_SIZE, {1920, 2000});
        _singletons.setSingleton<unsigned int>(EngineServer::UDP::SingletonsEnum::FPS, 60);
        _singletons.setSingleton<EngineUtils::Timer>(EngineServer::UDP::SingletonsEnum::ONE_SEC_TIMER, 1);
        _singletons.setSingleton<EngineUtils::Timer>(EngineServer::UDP::SingletonsEnum::MINI_TIMER, 0.1);
        _singletons.setSingleton<bool>(EngineServer::UDP::SingletonsEnum::WAVER_OVER, false);
        _singletons.setSingleton<std::vector<std::vector<std::string>>>(EngineServer::UDP::SingletonsEnum::WAVES);
        _singletons.setSingleton<std::function<void()>>(EngineServer::UDP::SingletonsEnum::SEND_CALLBACK);
        _singletons.setSingleton<unsigned int>(EngineServer::UDP::SingletonsEnum::GAMEID, _gameID);

        EngineComponent::registerEngineComponents(_register);

        _register.entityCache.cacheEntity<Entity::Player>(EngineServer::Init::IPLAYER, EngineServer::defaultEntityPath + "/Player.csv");
        _register.entityCache.cacheEntity<Entity::Missile>(EngineServer::Init::IMISSILE, EngineServer::defaultEntityPath + "/Missile.json");
        _register.entityCache.cacheEntity<Entity::Auxiliaries>(EngineServer::Init::IAUXILIARY, EngineServer::defaultEntityPath + "/Auxiliaries.json");
        _register.entityCache.cacheEntity<Entity::Enemy>(EngineServer::Init::IENEMY, EngineServer::defaultEntityPath + "/Enemy.json");

        // Spawn players
        _singletons.getSingleton<std::vector<std::size_t>>(EngineServer::UDP::AVAILABLE_PLAYER) = _register.entityCache.addEntitiesFromCSV(_register, EngineServer::Init::IPLAYER);
        // Spawn waves
        _singletons.getSingleton<std::vector<std::vector<std::string>>>(EngineServer::UDP::SingletonsEnum::WAVES) = EngineUtils::CSV::readCSV(EngineServer::defaultEntityPath + _waves);
        _init = true;
    }

    /**
     * @brief 
     * Initialize the connection between UDP Server and the player
     * 
     */
    void ServerGame::initNetwork()
    {
        _server.get()->start();
    }

    /**
     * @brief 
     * General function for sending information to the UDP server on the Game
     * 
     */
    void ServerGame::initNetworkSend()
    {
        _singletons.getSingleton<std::function<void()>>(EngineServer::UDP::SingletonsEnum::SEND_CALLBACK) = [this]() {ServerGame::handleSendingMessages();};
        generateWave(_register, _singletons);
    }

    /**
     * @brief  
     * General function for receiving information from the UDP server on the Game
     * 
     */
    void ServerGame::initNetworkRead()
    {
        _server.get()->loopRead([this]() {handleReceivedMessages();});
    }

    /**
     * @brief 
     * Stop all threads when player is disconnected
     * 
     */
    void ServerGame::stop()
    {
        _server.get()->stop();
        _end = true;
    }

    void ServerGame::handleReceivedMessages()
    {
        auto &listAction = _server.get()->getReadList();

        while (listAction.size() != 0 && !_end) {
            auto readed = listAction.front();
            EngineNetwork::UDPDataStructure::codeUDP code = static_cast<EngineNetwork::UDPDataStructure::codeUDP>(readed.first.at(0));

            auto func = _translateList.find(code);
            if (func != _translateList.end()) {
                func->second(readed, _register, _singletons);
            }
            listAction.pop();
        }
    }

    /**
     * @brief 
     * Handle the sent messages to the Clients
     * 
     */
    void ServerGame::handleSendingMessages()
    {
        EngineUtils::Queue<std::pair<EngineNetwork::DataStructure::Message, EngineNetwork::DataStructure::MessageTarget>> &sendList = _singletons.getSingleton<EngineUtils::Queue<std::pair<EngineNetwork::DataStructure::Message, EngineNetwork::DataStructure::MessageTarget>>>(EngineServer::UDP::SingletonsEnum::SEND_LIST);

        while (sendList.size() != 0 && !_end) {
            auto head = sendList.front();
            if (head.second.privateMessage) // Write to a single client
                _server.get()->writeToID(head.second.idTarget, head.first.message);
            else {
                if (head.second.idTarget != 0) // Write to all client except for given clients
                    _server.get()->writeToAllExceptFor(head.first.message, {head.second.idTarget}); 
                else // Write to all client
                    _server.get()->writeToAll(head.first.message);
            }
            sendList.pop();
        }
    }
};
