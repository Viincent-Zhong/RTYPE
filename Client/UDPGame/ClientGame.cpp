/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** ClientGame
*/

#include "ClientGame.hpp"
#include "Lib.hpp"
#include "Interaction/Interaction.hpp"
#include "Sound/Sound.hpp"
#include "Element/Element.hpp"
#include "GameplayC.hpp"
#include "ClientUDPSingletons.hpp"

#include "DrawSystems.hpp"
#include "BackgroundSystems.hpp"
#include "PhysiqueSystems.hpp"
#include "VisualEffectSystems.hpp"
#include "RenderingSystems.hpp"
#include "Text/TextSystems.hpp"

#include "Background.hpp"
#include "VisualEffect.hpp"
#include "Fonts.hpp"

#include "Serialization.hpp"
#include "logicGameClient.hpp"
#include "EngineComponents.hpp"
#include "UDPDataStructure.hpp"

EngineClient::ClientGame::ClientGame() : _lib(new Lib(1920, 1000, 60, "Pada Engine")), _inter(new Interaction), _timeout(30)
{
    _listReceive[EngineNetwork::UDPDataStructure::STATUS_GAME] = getStatusGame;
    _listReceive[EngineNetwork::DataStructure::CONNECTION] = getStatusPlayer;
    _listReceive[EngineNetwork::UDPDataStructure::DESTROY] = getDestroyed;
    _listReceive[EngineNetwork::DataStructure::DECONNECTION] = getDeconnected;
}

EngineClient::ClientGame::ClientGame(EngineNetwork::INetwork *server) : _lib(new Lib(1920, 1000, 60, "Pada Engine")), _inter(new Interaction), _client(server), _timeout(30)
{
    _listReceive[EngineNetwork::UDPDataStructure::STATUS_GAME] = getStatusGame;
    _listReceive[EngineNetwork::DataStructure::CONNECTION] = getStatusPlayer;
    _listReceive[EngineNetwork::UDPDataStructure::DESTROY] = getDestroyed;
    _listReceive[EngineNetwork::DataStructure::DECONNECTION] = getDeconnected;
}

EngineClient::ClientGame::~ClientGame()
{
    _end = true;
    _client.get()->stop();
}

void EngineClient::ClientGame::loadFont()
{
    auto const &fonts = _register.getComponents<EngineComponent::FontName>();

    for (int i = 0; i != fonts.size(); ++i) {
        auto const &font = fonts[i];
        if (font)
            _singletons.getSingleton<std::string>(EngineClient::UDP::FONT_NAME) = font->name;
    }
}

/**
 * @brief 
 * Initialize the game with players, background, systems and waves
 * 
 */
void EngineClient::ClientGame::initGame()
{
    if (!_lib->isAudioReady())
        _lib->initMusic();
    if (!_lib->isWindowReady())
        _lib->openWindow();
    EngineComponent::registerEngineComponents(_register);

    _register.entityCache.cacheEntity<Entity::Background>(InitEnum::BACKGROUND, defaultEntityPath + "/Background.csv");
    _register.entityCache.cacheEntity<Entity::VisualEffect>(InitEnum::VISUAL_EFFECT, defaultEntityPath + "/VisualEffect.csv");
    _register.entityCache.cacheEntity<Entity::Fonts>(InitEnum::FONT, defaultEntityPath + "/Font.csv");

    _systems.setSystem<System::Draw>(SystemEnum::SDRAW);
    _systems.setSystem<System::Background>(SystemEnum::SBACKGROUND);
    _systems.setSystem<System::Physique>(SystemEnum::SPHYSIQUE);
    _systems.setSystem<System::VisualEffect>(SystemEnum::SVISUAL_EFFECT);
    _systems.setSystem<System::Rendering>(SystemEnum::SRENDERING);
    _systems.setSystem<System::TextSystem>(SystemEnum::STEXT);

    _singletons.setSingleton<std::size_t>(EngineClient::UDP::SingletonsEnum::ID, 0);
    _singletons.setSingleton<EngineUtils::DeltaTime>(EngineClient::UDP::SingletonsEnum::DELTA_TIME);
    _singletons.setSingleton<std::pair<float, float>>(EngineClient::UDP::SingletonsEnum::LAST_MOVE, {-1.0f, -1.0f});
    _singletons.setSingleton<EngineUtils::Timer>(EngineClient::UDP::SingletonsEnum::BULLET_TIMER, 2.0f);
    _singletons.setSingleton<std::vector<PadaEngine::Position>>(EngineClient::UDP::SingletonsEnum::POS_EXPLOSION);
    _singletons.setSingleton<EngineUtils::Timer>(EngineClient::UDP::SingletonsEnum::ONE_SEC_TIMER, 1.0f);
    _singletons.setSingleton<std::string>(EngineClient::UDP::SingletonsEnum::EFFECT_NAME, "fire_one");
    _singletons.setSingleton<bool>(EngineClient::UDP::SingletonsEnum::END, false);
    _singletons.setSingleton<std::unordered_map<std::string, System::DataText>>(EngineClient::UDP::SingletonsEnum::TEXT);
    _singletons.setSingleton<std::string>(EngineClient::UDP::SingletonsEnum::FONT_NAME, "");

    _register.entityCache.addEntitiesFromCSV(_register, InitEnum::BACKGROUND);
    _register.entityCache.addEntitiesFromCSV(_register, InitEnum::VISUAL_EFFECT);
    _register.entityCache.addEntitiesFromCSV(_register, InitEnum::TEXT);
    _register.entityCache.addEntitiesFromCSV(_register, InitEnum::FONT);
    initSoundEffect("/GameEffect.csv", false);
    initSoundEffect("/GameMusic.csv", true);
    loadFont();
}

/**
 * @brief 
 * Run all the systems for the game
 * 
 */
void EngineClient::ClientGame::runSystems()
{
    _systems.runSystem(_register, _singletons, SystemEnum::SDRAW);
    _systems.runSystem(_register, _singletons, SystemEnum::SBACKGROUND);
    _systems.runSystem(_register, _singletons, SystemEnum::SPHYSIQUE);
    _systems.runSystem(_register, _singletons, SystemEnum::SVISUAL_EFFECT);
    _systems.runSystem(_register, _singletons, SystemEnum::SRENDERING);
    _systems.runSystem(_register, _singletons, SystemEnum::STEXT);
    handleAudio();
}

/**
 * @brief 
 * Load all the singletons
 * 
 */
void EngineClient::ClientGame::loadSingletons()
{
    auto &deltaTime = _singletons.getSingleton<EngineUtils::DeltaTime>(EngineClient::UDP::SingletonsEnum::DELTA_TIME);
    std::size_t &id = _singletons.getSingleton<std::size_t>(EngineClient::UDP::SingletonsEnum::ID);
    EngineUtils::Timer &oneSecTimer = _singletons.getSingleton<EngineUtils::Timer>(EngineClient::UDP::SingletonsEnum::ONE_SEC_TIMER);

    _singletons.getSingleton<std::string>(EngineClient::UDP::EFFECT_NAME) = "";
    if (id != 0)
        inputControl();
    if (oneSecTimer.TimerDone())
        oneSecTimer.RestartTimer();
    oneSecTimer.UpdateTimer(deltaTime.getDeltaTime());

    // Update timeout
    _timeout.UpdateTimer(deltaTime.getDeltaTime());
    // _singletons.getSingleton<std::string>(EngineClient::UDP::EFFECT_NAME) = "";
    deltaTime.updateDeltaTime();
}

/**
 * @brief 
 * Main Loop for the Game for the UDP Server
 * 
 */
void EngineClient::ClientGame::gameLoop()
{
    _lib->startDrawing();
    _lib->clearWindow(0);
    std::string nb1 = "1";
    std::string nb2 = "1";
    std::string data = "WAVE: " + nb1 + "/" + nb2;
    _singletons.getSingleton<std::unordered_map<std::string, System::DataText>>(EngineClient::UDP::SingletonsEnum::TEXT)["wave id"] = {_singletons.getSingleton<std::string>(EngineClient::UDP::SingletonsEnum::FONT_NAME), data, 2.0f, {800.0f, 10.0f}, 1.0f, PadaEngine::PADA_RED};;
    runSystems();
    _lib->endDrawing();
    loadSingletons();
}

/**
 * @brief 
 * Disconnect the player from the server and the game if he disconnect or close the window
 * 
 * @return true 
 * @return false 
 */
bool EngineClient::ClientGame::endCondition()
{
    if (_singletons.getSingleton<bool>(EngineClient::UDP::SingletonsEnum::END)) {
        stop();
        return true;
    }
    if (_end) {
        stop();
        return true;
    }
    if (_inter.get()->isKeyReleased(EngineComponent::KEY_VALUE::ESCAP)) { // If press escape
        // Notify server of our deconnection
        auto message = EngineNetwork::Serialisation::pack({EngineNetwork::DataStructure::DECONNECTION});
        _client.get()->writeToAll(message);
        std::cout << "Pinged server of my deconnection\n";
        std::this_thread::sleep_for(std::chrono::seconds(2)); // Wait 2 sec before stopping game so the client send its deconnection to the server before
        stop();
        return true;
    }
    if (_timeout.TimerDone()) { // If timeout (30 seconds of no activity from server)
        auto message = EngineNetwork::Serialisation::pack({EngineNetwork::DataStructure::DECONNECTION});
        _client.get()->writeToAll(message);
        std::cout << "Pinged server of my deconnection\n";
        std::this_thread::sleep_for(std::chrono::seconds(2)); // Wait 2 sec before stopping game so the client send its deconnection to the server before
        stop();
        return true;
    }
    if (_lib->hasCloseWindow()) {
        auto message = EngineNetwork::Serialisation::pack({EngineNetwork::DataStructure::DECONNECTION});
        _client.get()->writeToAll(message);
        std::cout << "Pinged server of my deconnection\n";
        std::this_thread::sleep_for(std::chrono::seconds(2)); // Wait 2 sec before stopping game so the client send its deconnection to the server before
        stop();
        return true;
    }
    return false;
}

/**
 * @brief 
 * Initialize the connection between UDP Server and the player
 * 
 */
void EngineClient::ClientGame::initNetwork()
{
    _client.get()->start();
}

/**
 * @brief 
 * General function for sending information to the server on the Game
 * 
 */
void EngineClient::ClientGame::initNetworkSend()
{
    // First connection
    try {
        std::cout << "Send connection request to server\n";
        std::pair<std::array<uint16_t, 50>, std::size_t> message = EngineNetwork::Serialisation::pack({EngineNetwork::DataStructure::CONNECTION});
        _client.get()->writeToAll(message);
    } catch (std::bad_cast const &error) {
    }
}

/**
 * @brief 
 * General function for receiving information from the server on the Game
 * 
 */
void EngineClient::ClientGame::initNetworkRead()
{
    _client.get()->loopRead([this]() {handleReadedMessages();});
}

/**
 * @brief 
 * Stop all threads when player is disconnected
 * 
 */
void EngineClient::ClientGame::stop()
{
    _end = true;
    _client.get()->stop();
}

/**
 * @brief 
 * Handle all the received message from the server 
 * 
 */
void EngineClient::ClientGame::handleReadedMessages()
{
    auto &listAction = _client.get()->getReadList();

    while (listAction.size() != 0 && !_end) {
        // Reset timeout to 30 sec if received an activity from server
        _timeout.RestartTimer();
        auto readed = listAction.front();
        EngineNetwork::UDPDataStructure::codeUDP code = static_cast<EngineNetwork::UDPDataStructure::codeUDP>(readed.first.at(0));

        auto func = _listReceive.find(code);
        if (func != _listReceive.end())
            func->second(readed, _register, _singletons);
        listAction.pop();
    }
}

/**
 * @brief 
 * Initialize a sound effect with a CSV file
 * 
 * @param file 
 * @param music 
 */
void EngineClient::ClientGame::initSoundEffect(std::string const &file, bool music)
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
 * Handle the music in the UDP Server
 * 
 */
void EngineClient::ClientGame::handleAudio()
{
    // si un effet est lancé
    if (_singletons.getSingleton<std::string>(EngineClient::UDP::SingletonsEnum::EFFECT_NAME) != "") {
        if (_audio.find(_singletons.getSingleton<std::string>(EngineClient::UDP::SingletonsEnum::EFFECT_NAME)) != _audio.end())
            _audio.find(_singletons.getSingleton<std::string>(EngineClient::UDP::SingletonsEnum::EFFECT_NAME))->second->playEffect();
    }
    // lance la musique au choix
    if (_audio.find("mainMusic") != _audio.end()) {
        _audio.find("mainMusic")->second->updateMusicStream();
    }
}
