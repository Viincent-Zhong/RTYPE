/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Button
*/

#include <algorithm>
#include <functional>
#include <chrono>
#include <thread>
#include "DrawC.hpp"
#include "GameplayC.hpp"
#include "Element/Element.hpp"
#include "ButtonSystem.hpp"
#include "Utils.hpp"
#include "ClientTCPSingletons.hpp"
#include "Text/TextSystems.hpp"
#include "tcpClientGameLogic.hpp"

namespace System {

    void errorMessage(std::string const &errorType, std::pair<float, float> const &pos, std::string const &message, EngineComponent::Singletons &singletons)
    {
        singletons.getSingleton<std::unordered_map<std::string, System::DataText>>(EngineClient::TCP::TEXTS)[errorType] = {singletons.getSingleton<std::string>(EngineClient::TCP::FONT_NAME), message, 1.0f, pos, 1.0f, PadaEngine::PADA_RED};
    }

    /**
     * @brief 
     * Function for a button that create a new Lobby changing the actual scene
     * 
     * @param r 
     * @param singletons 
     */
    void functionCreateGame(Registry &r, EngineComponent::Singletons &singletons)
    {
        if (singletons.getSingleton<unsigned int>(EngineClient::TCP::SingletonEnum::ID) == 0) {
            errorMessage("not connected", {600.0f, 700.0f}, "You need to be connected to do that (button in the middle)", singletons);
            return;
        }
        singletons.getSingleton<std::size_t>(EngineClient::TCP::SingletonEnum::LAYER) = 2;
        singletons.getSingleton<std::unordered_map<std::string, System::DataText>>(EngineClient::TCP::TEXTS).clear();
    }

    /**
     * @brief 
     * Function for a button that display all the existing lobbies changing the actual scene
     * 
     * @param r 
     * @param singletons 
     */
    void functionGetGames(Registry &r, EngineComponent::Singletons &singletons)
    {
        if (singletons.getSingleton<unsigned int>(EngineClient::TCP::SingletonEnum::ID) == 0) {
            errorMessage("not connected", {600.0f, 700.0f}, "You need to be connected to do that (button in the middle)", singletons);
            return;
        }
        singletons.getSingleton<std::size_t>(EngineClient::TCP::SingletonEnum::LAYER) = 3;
        singletons.getSingleton<std::unordered_map<std::string, System::DataText>>(EngineClient::TCP::TEXTS).clear();
    }

    /**
     * @brief 
     * Function for a button that try to join an existing lobby changing the actual scene
     * 
     * @param r 
     * @param singletons 
     */
    void functionJoinGame(Registry &r, EngineComponent::Singletons &singletons)
    {
        singletons.getSingleton<std::size_t>(EngineClient::TCP::SingletonEnum::LAYER) = 3;
        singletons.getSingleton<std::unordered_map<std::string, System::DataText>>(EngineClient::TCP::TEXTS).clear();
    }

    /**
     * @brief 
     * Function for a button that generate an AI or a Player to the lobby (server side)
     * 
     * @param r 
     * @param singletons 
     */
    void functionCreatePlayer(Registry &r, EngineComponent::Singletons &singletons)
    {
        singletons.getSingleton<std::size_t>(EngineClient::TCP::SingletonEnum::LAYER) = 4;
        singletons.getSingleton<std::unordered_map<std::string, System::DataText>>(EngineClient::TCP::TEXTS).clear();
    }

    /**
     * @brief
     * Function for a button that send the data of a Player to another Player
     * 
     * @param r 
     * @param singletons 
     */
    void functionSendDataPlayer(Registry &r, EngineComponent::Singletons &singletons)
    {
        singletons.getSingleton<std::size_t>(EngineClient::TCP::SingletonEnum::LAYER) = 1;
        singletons.getSingleton<std::unordered_map<std::string, System::DataText>>(EngineClient::TCP::TEXTS).clear();
        auto &name = singletons.getSingleton<std::array<char, 20>>(EngineClient::TCP::SingletonEnum::NAME);
        for (int i = 0; i != singletons.getSingleton<std::string>(EngineClient::TCP::SNAME).size(); ++i) {
            if (i >= 20)
                break;
            name[i] = singletons.getSingleton<std::string>(EngineClient::TCP::SNAME)[i];
        }
        askRegister(singletons, 0);
        std::cout << "Send register request\n";
    }

    /**
     * @brief 
     * Function for a button that return to the Main Menu changing the actual scene
     * 
     * @param r 
     * @param singletons 
     */
    void functionHome(Registry &r, EngineComponent::Singletons &singletons)
    {
        singletons.getSingleton<std::size_t>(EngineClient::TCP::SingletonEnum::LAYER) = 1;
        singletons.getSingleton<std::unordered_map<std::string, System::DataText>>(EngineClient::TCP::TEXTS).clear();
    }

    /**
     * @brief 
     * Function for a button that quit the game
     * 
     * @param r 
     * @param singletons 
     */
    void functionClose(Registry &r, EngineComponent::Singletons &singletons)
    {
        singletons.getSingleton<std::size_t>(EngineClient::TCP::SingletonEnum::LAYER) = 0;
        singletons.getSingleton<std::unordered_map<std::string, System::DataText>>(EngineClient::TCP::TEXTS).clear();
        singletons.getSingleton<bool>(EngineClient::TCP::SingletonEnum::LEAVING) = true;
        std::cout << "Quitte le jeu !" << std::endl;
    }

    /**
     * @brief 
     * Function for a button that refresh the existing lobbies and display them again
     * 
     * @param r 
     * @param singletons 
     */
    void functionRefreshGameList(Registry &r, EngineComponent::Singletons &singletons)
    {
        singletons.getSingleton<std::unordered_map<std::string, System::DataText>>(EngineClient::TCP::TEXTS).clear();
        askRoomsList(singletons, 0);
        std::cout << "Refresh la liste des parties disponible !" << std::endl;
    }

    /**
     * @brief 
     * Function for a button that join a game after searching for a lobby
     * 
     * @param r 
     * @param singletons 
     */
    void functionJoinOneGame(Registry &r, EngineComponent::Singletons &singletons)
    {
        singletons.getSingleton<std::unordered_map<std::string, System::DataText>>(EngineClient::TCP::TEXTS).clear();
        auto &gameID = singletons.getSingleton<std::string>(EngineClient::TCP::GAME_ID);
        askJoiningRoom(singletons, std::stoi(gameID));
        std::cout << "Send request to join room " << gameID << "\n";
    }

    /**
     * @brief 
     * Function for a button that join a lobby that exist and is displayed on the scene
     * 
     * @param r 
     * @param singletons 
     */
    void functionGoToLobby(Registry &r, EngineComponent::Singletons &singletons)
    {
        singletons.getSingleton<std::unordered_map<std::string, System::DataText>>(EngineClient::TCP::TEXTS).clear();
        std::cout << "Send create room request\n";
        askCreatingRoom(singletons, 0);
    }

    void functionExitLobby(Registry &r, EngineComponent::Singletons &singletons)
    {
        singletons.getSingleton<std::unordered_map<std::string, System::DataText>>(EngineClient::TCP::TEXTS).clear();
        std::cout << "Leave lobby\n";
        sendLeavingRoom(singletons, singletons.getSingleton<unsigned int>(EngineClient::TCP::SingletonEnum::ROOM_ID));
        singletons.getSingleton<unsigned int>(EngineClient::TCP::SingletonEnum::ROOM_ID) = 0;
        singletons.getSingleton<std::size_t>(EngineClient::TCP::SingletonEnum::LAYER) = 1;
    }

    /**
     * @brief 
     * Function for a button that start the game in the lobby
     * 
     * @param r 
     * @param singletons 
     */
    void functionPlay(Registry &r, EngineComponent::Singletons &singletons)
    {
        askLaunchingGame(singletons, 0);
    }

    /**
     * @brief 
     * Function for a button that display the informations off the lobby
     * 
     * @param r 
     * @param singletons 
     */
    void functionInfoLobby(Registry &r, EngineComponent::Singletons &singletons)
    {
        singletons.getSingleton<std::size_t>(EngineClient::TCP::SingletonEnum::LAYER) = 5;
        singletons.getSingleton<std::unordered_map<std::string, System::DataText>>(EngineClient::TCP::TEXTS).clear();

        askRoomPlayers(singletons, 0);
    }

    /**
     * @brief 
     * Function for a button that try to connect to a Server
     * 
     * @param r 
     * @param singletons 
     */
    void functionConnectionIP(Registry &r, EngineComponent::Singletons &singletons)
    {
        // Trying to connect with current ip
        singletons.getSingleton<bool>(EngineClient::TCP::TRY_CONNECT) = true;
    }

    /**
     * @brief 
     * Function for a button that switch the get user input for Port ot IP
     * 
     * @param r 
     * @param singletons 
     */
    void functionSwitchBetweenPortIP(Registry &r, EngineComponent::Singletons &singletons)
    {
        // Trying to connect with current ip
        singletons.getSingleton<bool>(EngineClient::TCP::SWITCH_IP_PORT) = !singletons.getSingleton<bool>(EngineClient::TCP::SWITCH_IP_PORT);
        std::cout << "Switch Bool to : " << singletons.getSingleton<bool>(EngineClient::TCP::SWITCH_IP_PORT) << std::endl;
    }

    std::unordered_map<std::string, std::function<void(Registry &r, EngineComponent::Singletons &singletons)>> _actionButton = {
        {"createGame", functionCreateGame},
        {"getGames", functionGetGames},
        {"joinGame", functionJoinGame},
        {"createPlayer", functionCreatePlayer},
        {"exit", functionClose},
        {"home", functionHome},
        {"lobby", functionGoToLobby},
        {"play", functionPlay},
        {"sendDataPlayer", functionSendDataPlayer},
        {"refresh", functionRefreshGameList},
        {"joinOneGame", functionJoinOneGame},
        {"infoLobby", functionInfoLobby},
        {"TryConnectionIP", functionConnectionIP},
        {"exitLobby", functionExitLobby},
        {"SwitchPortIP", functionSwitchBetweenPortIP}
    };

    /**
     * @brief 
     * General handling for ButtonSystems 
     * 
     * @param r 
     * @param singletons 
     */
    void buttonSystem(Registry &r, EngineComponent::Singletons &singletons)
    {
        auto const &positions = r.getComponents<EngineComponent::Position>();
        auto &recs = r.getComponents<EngineComponent::SpriteSheet>();
        auto const &buttonable = r.getComponents<EngineComponent::Interactible>();
        auto &names = r.getComponents<EngineComponent::FunctionName>();
        auto const &effectNames = r.getComponents<EngineComponent::EffectName>();
        auto const &layers = r.getComponents<EngineComponent::Layer>();

        for (size_t i = 0; i < positions.size() && i < recs.size() && i < buttonable.size() && i < effectNames.size() && i < layers.size(); ++i) {
            auto const &pos = positions[i];
            auto &rec = recs[i];
            auto const &button = buttonable[i];
            auto &name = names[i];
            auto const &effectName = effectNames[i];
            auto const &layer = layers[i];
            if (pos && rec && button && name && effectName && layer && (layer.value().layer == 0 || layer.value().layer == singletons.getSingleton<std::size_t>(EngineClient::TCP::SingletonEnum::LAYER))) {
                // Get mouse position
                std::pair<float, float> &mousePos = singletons.getSingleton<std::pair<float, float>>(EngineClient::TCP::SingletonEnum::MOUSE_POS);
                PadaEngine::Position mPos = {mousePos.first, mousePos.second};
                // Check if mouse position is on the button
                if (EngineUtils::collisionPosWithRec(mPos, {pos.value().pos, rec.value().rec}) && singletons.getSingleton<bool>(EngineClient::TCP::SingletonEnum::MOUSE_LEFT)) {
                    // singletons.launchEffect = effectName.value().name;
                    singletons.getSingleton<std::string>(EngineClient::TCP::SingletonEnum::EFFECT_NAME) = effectName.value().name;
                    if (_actionButton.find(name.value().name) != _actionButton.end())
                        _actionButton.find(name.value().name)->second(r, singletons);
                } else {
                    // singletons.isButtonPress = false;
                }
            }
        }
    }

    Button::Button()
    {
        _buttonSystems.push_front(&buttonSystem);
    }

    /**
     * @brief 
     * Run the Button system
     * 
     * @param r 
     * @param singletons 
     */
    void Button::run(Registry &r, EngineComponent::Singletons &singletons)
    {
        for (auto it = _buttonSystems.begin(); it != _buttonSystems.end(); ++it)
            (*it)(r, singletons);
    }
};