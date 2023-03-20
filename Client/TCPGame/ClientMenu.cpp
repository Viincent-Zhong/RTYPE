/*
** EPITECH PROJECT, 2022
** Project R-TYPE
** File description:
** ClientMenu.cpp
*/

#include <array>
#include <chrono>
#include "Lib.hpp"
#include "Interaction/Interaction.hpp"
#include "Sound/Sound.hpp"
#include "tcpClientGameLogic.hpp"
#include "ClientMenu.hpp"
#include "ClientGame.hpp"
#include "ClientTCPSingletons.hpp"
#include "startClient.hpp"
#include "DrawC.hpp"

#include "BackgroundSystems.hpp"
#include "ButtonSystem.hpp"
#include "DrawSystems.hpp"
#include "Text/TextSystems.hpp"

#include "Background.hpp"
#include "Button.hpp"
#include "Fonts.hpp"

#include "ErrorLoader.hpp"
#include "EngineComponents.hpp"

/**
 * @brief 
 * Initialize Sound effect in the main menu
 * 
 * @param file 
 * @param music 
 */
void EngineClient::ClientMenu::initSoundEffect(std::string const &file, bool music)
{
    const auto content = EngineUtils::CSV::readCSV(defaultEntityPath + file);
    for (auto const &it : content) {
        _audio[it.at(0)].reset(new SoundGame);
        if (music)
            _audio.find(it.at(0))->second->initMusic(it.at(1), std::atoi(it.at(2).c_str()));
        else {
            _audio.find(it.at(0))->second->createEffect(it.at(1));
            _audio.find(it.at(0))->second->updateEffectVolume(std::atoi(it.at(2).c_str()));
        }
    }
}

/**
 * @brief 
 * Handle all the audio in the Main Menu either music or sound effect
 * 
 */
void EngineClient::ClientMenu::handleAudio()
{
    // si un effet est lancé
    if (_singletons.getSingleton<std::string>(EngineClient::TCP::EFFECT_NAME) != "")
        if (_audio.find(_singletons.getSingleton<std::string>(EngineClient::TCP::EFFECT_NAME)) != _audio.end())
            _audio.find(_singletons.getSingleton<std::string>(EngineClient::TCP::EFFECT_NAME))->second->playEffect();
    // lance la musique au choix
    // if 
    if (_audio.find("mainMusic") != _audio.end())
        _audio.find("mainMusic")->second->updateMusicStream();
}

/**
 * @brief 
 * Load all Singletons Components in the Main Menu
 * 
 */
void EngineClient::ClientMenu::loadSingletons()
{
    _singletons.getSingleton<std::pair<unsigned int, unsigned int>>(EngineClient::TCP::WINDOW_SIZE) = _lib.get()->getWindowSize();
    _singletons.getSingleton<std::string>(EngineClient::TCP::EFFECT_NAME) = "";
    _singletons.getSingleton<unsigned int>(EngineClient::TCP::FPS) = _lib.get()->getFps();
    _singletons.getSingleton<std::pair<float, float>>(EngineClient::TCP::SingletonEnum::MOUSE_POS) = _inter.get()->getMousePosition();
    _singletons.getSingleton<bool>(EngineClient::TCP::SingletonEnum::MOUSE_LEFT) = false;
    if (_inter.get()->mouseLeftIsRelease())
        _singletons.getSingleton<bool>(EngineClient::TCP::SingletonEnum::MOUSE_LEFT) = true;
    _singletons.getSingleton<EngineUtils::DeltaTime>(EngineClient::TCP::DELTA_TIME).updateDeltaTime();
}

/**
 * @brief 
 * Run the loaded systems in the Main Menu
 * 
 */
void EngineClient::ClientMenu::runSingletons()
{
    _systems.runSystem(_register, _singletons, EngineClient::TCP::SystemEnum::SDRAW);
    _systems.runSystem(_register, _singletons, EngineClient::TCP::SystemEnum::SBACKGROUND);
    _systems.runSystem(_register, _singletons, EngineClient::TCP::SystemEnum::SBUTTON);
    _systems.runSystem(_register, _singletons, EngineClient::TCP::SystemEnum::STEXT);
}

EngineClient::ClientMenu::ClientMenu(EngineNetwork::INetwork *server) : _client(server), _lib(new Lib(1920, 1000, 60, "Pada Engine")), _inter(new Interaction)
{
    if (_lib->isWindowReady()) // Client already have another instance of the game
        throw ErrorGame("Close all the instances of the game first\n");
    _listReceive[EngineNetwork::TCPDataStructure::REGISTER] = Register;
    _listReceive[EngineNetwork::TCPDataStructure::GET_ROOMS] = getRoomsList;
    _listReceive[EngineNetwork::TCPDataStructure::GET_PLAYER_IN_ROOM] = getRoomPlayers;
    _listReceive[EngineNetwork::TCPDataStructure::CREATE_ROOM] = createdRoom;
    _listReceive[EngineNetwork::TCPDataStructure::JOIN_ROOM] = joinedRoom;
    _listReceive[EngineNetwork::TCPDataStructure::LAUNCH_GAME] = launchedGame;
    _listReceive[EngineNetwork::DataStructure::DECONNECTION] = deconnected;
}

EngineClient::ClientMenu::~ClientMenu()
{
    stop();
}

void EngineClient::ClientMenu::loadFont()
{
    auto const &fonts = _register.getComponents<EngineComponent::FontName>();

    for (int i = 0; i != fonts.size(); ++i) {
        auto const &font = fonts[i];
        if (font)
            _singletons.getSingleton<std::string>(EngineClient::TCP::FONT_NAME) = font->name;
    }
}

/**
 * @brief 
 * Initialize all the Objects,Systems prerequisite for the Main Menu
 * 
 */
void EngineClient::ClientMenu::initGame()
{
    EngineComponent::registerEngineComponents(_register);

    _lib->initMusic();
    _lib->openWindow();
    _register.entityCache.cacheEntity<Entity::Background>(InitEnum::BACKGROUND, defaultEntityPath + "/Background.csv");
    _register.entityCache.cacheEntity<Entity::Button>(InitEnum::BUTTON, defaultEntityPath + "/Button.csv");
    _register.entityCache.cacheEntity<Entity::Fonts>(InitEnum::FONT, defaultEntityPath + "/Font.csv");

    _systems.setSystem<System::Draw>(EngineClient::TCP::SystemEnum::SDRAW);
    _systems.setSystem<System::Background>(EngineClient::TCP::SystemEnum::SBACKGROUND);
    _systems.setSystem<System::Button>(EngineClient::TCP::SystemEnum::SBUTTON);
    _systems.setSystem<System::TextSystem>(EngineClient::TCP::SystemEnum::STEXT);

    _singletons.setSingleton<unsigned int>(EngineClient::TCP::SingletonEnum::ID, 0);
    _singletons.setSingleton<std::array<char, 20>>(EngineClient::TCP::SingletonEnum::NAME, {0});
    _singletons.setSingleton<unsigned int>(EngineClient::TCP::SingletonEnum::ROOM_ID, 0);
    _singletons.setSingleton<unsigned int>(EngineClient::TCP::SingletonEnum::GAME_LAUNCHED, 0);
    _singletons.setSingleton<EngineUtils::Queue<std::pair<EngineNetwork::DataStructure::Message, EngineNetwork::DataStructure::MessageTarget>>>(EngineClient::TCP::SingletonEnum::SEND_LIST);
    _singletons.setSingleton<bool>(EngineClient::TCP::SingletonEnum::LEAVING, false);
    _singletons.setSingleton<std::size_t>(EngineClient::TCP::SingletonEnum::LAYER, 7);
    _singletons.setSingleton<std::pair<float, float>>(EngineClient::TCP::SingletonEnum::MOUSE_POS);
    _singletons.setSingleton<bool>(EngineClient::TCP::SingletonEnum::MOUSE_LEFT, false);
    _singletons.setSingleton<std::string>(EngineClient::TCP::SingletonEnum::EFFECT_NAME, "");
    _singletons.setSingleton<std::pair<unsigned int, unsigned int>>(EngineClient::TCP::SingletonEnum::WINDOW_SIZE, {0, 0});
    _singletons.setSingleton<unsigned int>(EngineClient::TCP::SingletonEnum::FPS, 60);
    _singletons.setSingleton<EngineUtils::DeltaTime>(EngineClient::TCP::SingletonEnum::DELTA_TIME);
    _singletons.setSingleton<std::unordered_map<std::string, System::DataText>>(EngineClient::TCP::SingletonEnum::TEXTS);
    _singletons.setSingleton<std::string>(EngineClient::TCP::SingletonEnum::SNAME, "");
    _singletons.setSingleton<std::string>(EngineClient::TCP::SingletonEnum::GAME_LEVEL, "1");
    _singletons.setSingleton<std::string>(EngineClient::TCP::SingletonEnum::GAME_ID, "1");
    _singletons.setSingleton<std::string>(EngineClient::TCP::SingletonEnum::FONT_NAME, "");
    _singletons.setSingleton<std::function<void()>>(EngineClient::TCP::SingletonEnum::SEND_CALLBACK);
    _singletons.setSingleton<std::string>(EngineClient::TCP::IP_SERVER);
    _singletons.setSingleton<std::string>(EngineClient::TCP::PORT, "1234");
    _singletons.setSingleton<bool>(EngineClient::TCP::SingletonEnum::TRY_CONNECT, false);
    _singletons.setSingleton<bool>(EngineClient::TCP::SingletonEnum::END, false);
    _singletons.setSingleton<bool>(EngineClient::TCP::SingletonEnum::SWITCH_IP_PORT, false);

    _singletons.setSingleton<unsigned int>(EngineClient::TCP::PAGE_DATA, 0);

    _register.entityCache.addEntitiesFromCSV(_register, InitEnum::BACKGROUND);
    _register.entityCache.addEntitiesFromCSV(_register, InitEnum::BUTTON);
    _register.entityCache.addEntitiesFromCSV(_register, InitEnum::TEXT);
    _register.entityCache.addEntitiesFromCSV(_register, InitEnum::FONT);
    initSoundEffect("/MenuEffect.csv", false);
    initSoundEffect("/MenuMusic.csv", true);
    loadFont();
}

/**
 * @brief 
 * The Main Menu loop for all the TCP Network side
 * 
 */
void EngineClient::ClientMenu::gameLoop()
{
    unsigned int &gameLaunched = _singletons.getSingleton<unsigned int>(EngineClient::TCP::SingletonEnum::GAME_LAUNCHED);
    bool &try_connect = _singletons.getSingleton<bool>(EngineClient::TCP::SingletonEnum::TRY_CONNECT);

    if (gameLaunched != 0) {
        startUDPClient(_host, std::to_string((int)gameLaunched));
        if (!_lib->isWindowReady()) { // If the game closed its window close the menu too
            _end = true;
            return;
        }
        gameLaunched = 0;
    }

    if (try_connect == true)
        initNetwork();
    loadSingletons();
    _lib->startDrawing();
    _lib->clearWindow(0);
    switch (_singletons.getSingleton<std::size_t>(EngineClient::TCP::LAYER))
    {
        case 7:
            displayLayerSeven();
            break;
        case 6:
            displayLayerSix();
            break;
        case 1:
            displayLayerOne();
            break;
        case 2:
            displayLayerTwo();
            break;
        case 3:
            displayLayerThree();
            break;
        case 4:
            displayLayerFour();
            break;
        case 5:
            displayLayerFive();
            break;
    
        default:
            displayLayerOne();
            break;
    }
    runSingletons();
    handleAudio();
    _lib->endDrawing();
}

/**
 * @brief 
 * Disconnect the player from the server if he disconnect or close the window
 * 
 * @return true 
 * @return false 
 */
bool EngineClient::ClientMenu::endCondition()
{
    if (_singletons.getSingleton<bool>(EngineClient::TCP::SingletonEnum::END) == true) {
        std::cout << "Server not responding\n";
        stop();
        return true;
    }
    if (_end == true) {
        sendDeconnecting(_singletons, 0);
        std::this_thread::sleep_for(std::chrono::seconds(2)); // Wait 2 sec before stopping game so the client send its deconnection to the server before
        stop();
        return true;
    }
    if (_singletons.getSingleton<bool>(EngineClient::TCP::SingletonEnum::LEAVING)) {
        return true;
    }
    if (_inter.get()->isKeyReleased(EngineComponent::KEY_VALUE::ESCAP)) {
        sendDeconnecting(_singletons, 0);
        std::this_thread::sleep_for(std::chrono::seconds(2)); // Wait 2 sec before stopping game so the client send its deconnection to the server before
        stop();
        return true;
    }
    return false;
}

/**
 * @brief 
 * Initialize the TCP Network for the client
 * 
 */
void EngineClient::ClientMenu::initNetwork()
{
    auto const &host = _singletons.getSingleton<std::string>(EngineClient::TCP::IP_SERVER);
    if (host.size() == 0)
        return;
    try {
        auto const &port = _singletons.getSingleton<std::string>(EngineClient::TCP::PORT);
        _client.get()->startOn(host, port);
        _client.get()->loopRead([this]() {handleReadedMessages();});
        _singletons.getSingleton<std::size_t>(EngineClient::TCP::SingletonEnum::LAYER) = 1;
        _singletons.getSingleton<std::unordered_map<std::string, System::DataText>>(EngineClient::TCP::TEXTS).clear();
    } catch (ErrorConnection const &error) {
    }
    _singletons.getSingleton<bool>(EngineClient::TCP::SingletonEnum::TRY_CONNECT) = false;
}

/**
 * @brief 
 * General function for sending information to the server on Main Menu and Lobby
 * 
 */
void EngineClient::ClientMenu::initNetworkSend()
{
    _singletons.getSingleton<std::function<void()>>(EngineClient::TCP::SingletonEnum::SEND_CALLBACK) = [this]() {handleSendingMessages();};
}

/**
 * @brief 
 * General function for receiving information from the server on Main Menu and Lobby
 * 
 */
void EngineClient::ClientMenu::initNetworkRead()
{
}

/**
 * @brief 
 * Stop all threads when player is disconnected
 * 
 */
void EngineClient::ClientMenu::stop()
{
    _end = true;
    _client.get()->stop();
    if (_lib->isAudioReady())
        _lib->closeAudio();
    if (_lib->isWindowReady())
        _lib->closeWindow();
}

/**
 * @brief 
 * Handle all the received message from the server 
 * 
 */
void EngineClient::ClientMenu::handleReadedMessages()
{
    auto &listAction = _client.get()->getReadList();

    while (listAction.size() != 0 && !_end) {
        auto readed = listAction.front();
        EngineNetwork::TCPDataStructure::codeTCP code = static_cast<EngineNetwork::TCPDataStructure::codeTCP>(readed.first.at(0));

        auto func = _listReceive.find(code);
        if (func != _listReceive.end())
            func->second(readed, _register, _singletons);
        listAction.pop();
    }
}

/**
 * @brief 
 * Handle all the sent message to the server
 * 
 */
void EngineClient::ClientMenu::handleSendingMessages()
{
    auto &sendList = _singletons.getSingleton<EngineUtils::Queue<std::pair<EngineNetwork::DataStructure::Message, EngineNetwork::DataStructure::MessageTarget>>>(EngineClient::TCP::SingletonEnum::SEND_LIST);

    while (sendList.size() != 0 && !_end) {
        auto head = sendList.front();
        if (head.second.privateMessage)
            _client.get()->writeToID(head.second.idTarget, head.first.message);
        else
            _client.get()->writeToAll(head.first.message);
        sendList.pop();
    }
}
