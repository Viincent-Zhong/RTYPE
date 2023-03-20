/*
** EPITECH PROJECT, 2022
** Project R-TYPE
** File description:
** Layers.cpp
*/

#include <iterator>
#include "ClientMenu.hpp"
#include "ClientTCPSingletons.hpp"
#include "Text/TextSystems.hpp"
#include "DrawC.hpp"

#include "tcpClientGameLogic.hpp"

/**
 * @brief 
 * Get the User Input for names and others Text Input Box
 * 
 * @param str 
 * @param interaction 
 * @param sizeMax 
 * @param singletons 
 * @param errorMessagePos 
 */
static void getUserInput(std::string &str, std::unique_ptr<PadaEngine::Iinteraction> &interaction, unsigned int sizeMax, EngineComponent::Singletons &singletons, std::pair<float, float> const &errorMessagePos)
{
    EngineComponent::KEY_VALUE val = interaction.get()->getPressedKey();
    if (val >= EngineComponent::A && val <= EngineComponent::Z || val >= EngineComponent::ZERO && val <= EngineComponent::NINE || val == EngineComponent::POINT || val == EngineComponent::SPACE) {
        if (str.size() > sizeMax)
            singletons.getSingleton<std::unordered_map<std::string, System::DataText>>(EngineClient::TCP::SingletonEnum::TEXTS)["message error name"] = {singletons.getSingleton<std::string>(EngineClient::TCP::FONT_NAME), "Name too long " + std::to_string(sizeMax + 1) + " characters max", 1.0f, errorMessagePos, 1.0f, PadaEngine::PADA_RED};
        else
            str.push_back(val == EngineComponent::SPACE ? 46 : val);
    } else if (val == EngineComponent::MY_DELETE && !str.empty())
        str.pop_back();
    if (str.size() <= sizeMax)
        singletons.getSingleton<std::unordered_map<std::string, System::DataText>>(EngineClient::TCP::SingletonEnum::TEXTS).erase("message error name");
}

/**
 * @brief 
 * Handle the change of scene/page for the client
 * 
 * @param interaction 
 * @param singletons 
 * @param page 
 */
static void changeDisplayPage(std::unique_ptr<PadaEngine::Iinteraction> &interaction, EngineComponent::Singletons &singletons, unsigned int &page)
{
    EngineComponent::KEY_VALUE val = interaction.get()->getPressedKey();
    std::cout << val << std::endl;
    if (val >= EngineComponent::ARROW_LEFT && page != 0) {
        std::cout << "pad\n";
        --page;
    } else if (val == EngineComponent::ARROW_RIGHT) {
        std::cout << "pad pad\n";
        ++page;
    }
}

/**
 * @brief 
 * Sixth layer, Display the Title Screen scene
 * 
 */
void EngineClient::ClientMenu::displayLayerSix()
{

}

/**
 * @brief 
 * Seventh layer, Display the Connection to a Port scene
 * 
 */
void EngineClient::ClientMenu::displayLayerSeven()
{
    bool tmp = _singletons.getSingleton<bool>(EngineClient::TCP::SWITCH_IP_PORT);
    if (tmp)
        getUserInput(_singletons.getSingleton<std::string>(EngineClient::TCP::PORT), _inter, 8, _singletons, {10.0f, 10.0f});
    else
        getUserInput(_singletons.getSingleton<std::string>(EngineClient::TCP::IP_SERVER), _inter, 20, _singletons, {10.0f, 10.0f});
    _singletons.getSingleton<std::unordered_map<std::string, System::DataText>>(EngineClient::TCP::TEXTS)["ip server"] = {_singletons.getSingleton<std::string>(EngineClient::TCP::FONT_NAME), "IP Server: " + _singletons.getSingleton<std::string>(EngineClient::TCP::IP_SERVER), 2.0f, {630.0f, 300.0f}, 1.0f, PadaEngine::PADA_WHITE};
    _singletons.getSingleton<std::unordered_map<std::string, System::DataText>>(EngineClient::TCP::TEXTS)["port server"] = {_singletons.getSingleton<std::string>(EngineClient::TCP::FONT_NAME), "Port : " + _singletons.getSingleton<std::string>(EngineClient::TCP::PORT), 2.0f, {630.0f, 400.0f}, 1.0f, PadaEngine::PADA_WHITE};
}

/**
 * @brief 
 * First layer, display the Main Menu scene
 * 
 */
void EngineClient::ClientMenu::displayLayerOne()
{

}

/**
 * @brief 
 * Second layer, display the Create Game scene
 * 
 */
void EngineClient::ClientMenu::displayLayerTwo()
{
    getUserInput(_singletons.getSingleton<std::string>(EngineClient::TCP::GAME_LEVEL), _inter, 0, _singletons, {10.0f, 10.0f});
    _singletons.getSingleton<std::unordered_map<std::string, System::DataText>>(EngineClient::TCP::TEXTS)["game level"] = {_singletons.getSingleton<std::string>(EngineClient::TCP::FONT_NAME), "LEVEL(1-3): " + _singletons.getSingleton<std::string>(EngineClient::TCP::GAME_LEVEL), 2.0f, {830.0f, 400.0f}, 1.0f, PadaEngine::PADA_DARKGREEN};
    auto c = _singletons.getSingleton<std::string>(EngineClient::TCP::GAME_LEVEL);
    if (c.empty() || c.at(0) < '1' || c.at(0) > '3')
        _singletons.getSingleton<std::unordered_map<std::string, System::DataText>>(EngineClient::TCP::TEXTS)["error game level"] = {_singletons.getSingleton<std::string>(EngineClient::TCP::FONT_NAME), "LEVEL must be between 1 and 3", 0.5f, {860.0f, 480.0f}, 1.0f, PadaEngine::PADA_RED};       
    else
        _singletons.getSingleton<std::unordered_map<std::string, System::DataText>>(EngineClient::TCP::TEXTS).erase("error game level");
}

/**
 * @brief 
 * Third layer, display all the existing Lobbies scene
 * 
 */
void EngineClient::ClientMenu::displayLayerThree()
{
    getUserInput(_singletons.getSingleton<std::string>(EngineClient::TCP::GAME_ID), _inter, 1000, _singletons, {10.0f, 10.0f});
    _singletons.getSingleton<std::unordered_map<std::string, System::DataText>>(EngineClient::TCP::TEXTS)["game id"] = {_singletons.getSingleton<std::string>(EngineClient::TCP::FONT_NAME), "NAME: " + _singletons.getSingleton<std::string>(EngineClient::TCP::GAME_ID), 2.0f, {800.0f, 300.0f}, 1.0f, PadaEngine::PADA_RED};
    auto const &rooms = _register.getComponents<EngineComponent::ListGame>();
    std::pair<float, float> pos = {800.0f, 350.0f};

    for (int i = 0; i < rooms.size(); ++i) {
        changeDisplayPage(_inter, _singletons, _singletons.getSingleton<unsigned int>(EngineClient::TCP::PAGE_DATA));
        auto const &room = rooms[i];
        if (room) {
            const std::string data = "Game id: " + std::to_string(room.value().id) + " players: " + std::to_string(room.value().nbPlayers) + "/4";
            _singletons.getSingleton<std::unordered_map<std::string, System::DataText>>(EngineClient::TCP::TEXTS)[std::to_string(i)] = {_singletons.getSingleton<std::string>(EngineClient::TCP::FONT_NAME), data, 2.0f, pos, 1.0f, PadaEngine::PADA_RED};
            pos.second += 50.0f;
        }
    }
}

/**
 * @brief 
 * Fourth layer, display the User Register scene
 * 
 */
void EngineClient::ClientMenu::displayLayerFour()
{
    getUserInput(_singletons.getSingleton<std::string>(EngineClient::TCP::SNAME), _inter, 19, _singletons, {10.0f, 10.0f});
    _singletons.getSingleton<std::unordered_map<std::string, System::DataText>>(EngineClient::TCP::TEXTS)["name"] = {_singletons.getSingleton<std::string>(EngineClient::TCP::FONT_NAME), "NAME: " + _singletons.getSingleton<std::string>(EngineClient::TCP::SNAME), 2.0f, {800.0f, 500.0f}, 1.0f, PadaEngine::PADA_RED};
}

/**
 * @brief 
 * Fifth layer, display the Lobby scene
 * 
 */
void EngineClient::ClientMenu::displayLayerFive()
{
    auto const &players = _register.getComponents<EngineComponent::RoomPlayer>();
    std::vector<std::pair<float, float>> pad = {{650.0f, 400.0f}, {650.0f, 450.0f}, {650.0f, 500.0f}, {650.0f, 550.0f}};
    unsigned int roomID = 0;

    for (int i = 0; i < players.size(); ++i) {
        auto const &player = players[i];
        if (player && player->playerID == _singletons.getSingleton<unsigned int>(EngineClient::TCP::SingletonEnum::ID)) {
            roomID = player->roomID;
        }
    }
    for (int i = 0, j = 0; i < players.size(); ++i) {
        auto const &player = players[i];
        if (player && player->roomID == roomID &&
        _singletons.getSingleton<std::unordered_map<std::string, System::DataText>>(EngineClient::TCP::TEXTS).find(std::to_string(player.value().playerID)) == _singletons.getSingleton<std::unordered_map<std::string, System::DataText>>(EngineClient::TCP::TEXTS).end()) {
            std::string str(std::begin(player.value().playerName), std::end(player.value().playerName));
            const std::string data = "Player id: " + std::to_string(player.value().playerID) + " Player name: " + str + "/4" + std::to_string(player->roomID);
            _singletons.getSingleton<std::unordered_map<std::string, System::DataText>>(EngineClient::TCP::TEXTS)[std::to_string(player.value().playerID)] = {_singletons.getSingleton<std::string>(EngineClient::TCP::FONT_NAME), data, 2.0, pad.at(j), 1.0, PadaEngine::PADA_RED};
            ++j;
        }
    }
}
