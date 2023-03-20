/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** DataStructure
*/

#pragma once

#include <cstddef>
#include <vector>
#include <array>
#include <stdint.h>

namespace EngineNetwork {
    namespace DataStructure {

        enum networkCode {
            CONNECTION = 1,
            DECONNECTION = 2
        };

        /**
         * @brief Contains the ID of who we want to ping, and a bool of if we want it to be a private ping or a ping all
         */
        struct MessageTarget {
            unsigned int idTarget;
            bool privateMessage;
        };

        /**
         * @brief Contains the IDs of who we want to ping, and a bool of if we want it to be a private ping or a ping all
         */
        struct MessageTargets {
            std::vector<unsigned int> idTargets;
            bool privateMessage;
        };

        /** @brief Contains a message
         */
        struct Message {
            std::pair<std::array<uint16_t, 50>, std::size_t> message;
        };

        /**
         * @brief Represent an ID
         */
        struct ID {
            std::size_t id;
        };

        /**
         * @brief Represent a status (OK or NOT OK)
         */
        struct Status {
            bool isOk;
        };

        /**
         * @brief Represent the status of an ID (is ID ok or not)
         */
        struct IDStatus {
            std::size_t id;
            bool isOk;
        };

        /**
         * @brief Represent the content number of an ID (unsigned int)
         */
        struct IDContentNumber {
            std::size_t id;
            unsigned int number;
        };
    };
};