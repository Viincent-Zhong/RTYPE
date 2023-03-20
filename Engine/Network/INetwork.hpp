/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** INetwork
*/

#pragma once

#include <string>
#include <functional>
#include <array>
#include "Queue.hpp"

namespace EngineNetwork {
    class INetwork {
        public:
            virtual ~INetwork() = default;

            /**
             * @brief start the server in a thread for not blocking the game loop
             * 
             */
            virtual void start() = 0;
            /**
             * @brief Connect to a server with a given host and port
             * 
             * @param host 
             * @param port 
             */
            virtual void startOn(std::string const &host, std::string const &port) = 0;
            /**
             * @brief stop the server and stop thread
             * 
             */
            virtual void stop() = 0;

            /**
             * @brief when a client send message to the server, this function is call.
             *        if the client is not register, the server add it to it list of clients
             * 
             */
            virtual void read() = 0;

            /**
             * @brief send message to all register clients
             * 
             * @param message to send
             */
            virtual void writeToAll(std::pair<std::array<uint16_t, 50>, std::size_t> &message) = 0;

            /**
             * @brief send message to all register clients except for a given list
             * 
             * @param message 
             */
			virtual void writeToAllExceptFor(std::pair<std::array<uint16_t, 50>, std::size_t> &message, std::vector<unsigned int> &exception) = 0;

            /**
             * @brief send message to all register clients except for a given list
             * 
             * @param message 
             */
			virtual void writeToAllExceptFor(std::pair<std::array<uint16_t, 50>, std::size_t> &message, std::vector<unsigned int> &&exception) = 0;

            /**
             * @brief send message to a specific client
             * 
             * @param id of the client in the list
             * @param message to send
             */
            virtual void writeToID(unsigned int id, std::pair<std::array<uint16_t, 50>, std::size_t> &message) = 0;

            /**
             * @brief This function take a callback to a function that will handle readed messages.
             * 
             */
            virtual void loopRead(std::function<void()> &callbackHandleRead) = 0;
            /**
             * @brief This function take a callback to a function that will handle readed messages.
             * 
             */
            virtual void loopRead(std::function<void()> &&callbackHandleRead) = 0;

            /**
             * Return a list of readed messages. It contains the data(std::array), the size of the data(std::size_t), and an id of who sent the message(unsigned int)
             * Return value : 
             * value.first = message
             * value.second.first = size of message
             * value.second.second = id of who sent it
             */
    		virtual EngineUtils::Queue<std::pair<std::array<uint16_t, 50>, std::pair<std::size_t, unsigned int>>> &getReadList() = 0;

            /**
             * @brief remove first element from the server list of action receive from the clients
             * 
             */
    		virtual void delElemListAction() = 0;
    };
};
