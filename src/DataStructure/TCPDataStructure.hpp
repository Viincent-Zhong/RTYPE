/*
** EPITECH PROJECT, 2022
** Project R-TYPE
** File description:
** TCPDataStructure.hpp
*/

#pragma once

#include <string>
#include <vector>
#include <array>
#include <functional>
#include "Queue.hpp"

namespace EngineNetwork {
    namespace TCPDataStructure {
        /**
         * @brief all possible actions between server/client and the responses
         * 
         */
        enum codeTCP {
            REGISTER = 3, // Client connect and send his name
            GET_ROOMS, // List all rooms
            GET_PLAYER_IN_ROOM, // List players of a room
            CREATE_ROOM, // Create a room
            JOIN_ROOM, // Join a room
            SOMEONE_JOINED_ROOM,
            CLIENT_DISCONNECTION, // Client crash or disconnected
            LAUNCH_GAME, // Room launch game
            LEAVE_ROOM, // Client leave the room
            ROOM_FULL,
            ERROR_JOIN_ROOM,
            ROOM_NOT_FOUND
        };

        /**
         * @brief data game for server
         * 
         */
        struct Party {
            std::vector<unsigned int> playerId;
            unsigned int id;

            // Host on which the client connected to
            unsigned int port;
        };

        struct Room {
            unsigned int id;
            unsigned int nbPlayers;
        };

        struct RoomContent {
            unsigned int roomID;
            unsigned int playerID;
            std::array<char, 20> player;
        };

        /**
         * @brief list of data game and client on server
         * 
         */
        struct DataTCPServer {
            EngineUtils::Queue<unsigned int> _leavedClients;
            EngineUtils::Queue<std::pair<std::array<uint16_t, 50>, std::pair<std::size_t, unsigned int>>> _readList;
            std::function<void()> _callbackHandleRead;
            std::function<void()> _callbackHandleClientLeaved;
        };
    };
}
