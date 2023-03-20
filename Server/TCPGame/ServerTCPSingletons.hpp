/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** ServerTCPSingletons
*/

#pragma once

#include <array>
#include <vector>

namespace EngineServer {
    namespace TCP {
        struct ServerRoom {
            unsigned int roomID;
            unsigned int nbrPlayers;
            std::vector<unsigned int> playersIDs;
            unsigned int port;
        };

        struct Player {
            unsigned int id;
            std::array<char, 20> name;
        };

        enum SingletonEnum {
            NBR_ROOMS,
            ROOMS,
            PLAYERS,
            SEND_LIST,
            SEND_CALLBACK,
            LAUNCHING_GAME,
            LAUNCHING_CALLBACK,
            GAME_LEVEL
        };
    };
};