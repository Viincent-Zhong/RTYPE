/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Singletons
*/

#pragma once

#include <any>
#include <unordered_map>
#include <mutex>
#include "ErrorLoader.hpp"

namespace EngineComponent {
    /**
     * @brief Class that represent a list of singletons all keyed by an unsigned int id
     */
    class Singletons {
        public:
            /**
             * @brief Set a singleton into the list with a key
             */
            template <class T>
            void setSingleton(unsigned int id, T &data)
            {
                std::lock_guard<std::mutex> lock(_mutex);
                _singletons[id] = std::move(data);
            }

            /**
             * @brief Set a singleton into the list with a key
             */
            template <class T>
            void setSingleton(unsigned int id, T &&data)
            {
                std::lock_guard<std::mutex> lock(_mutex);
                _singletons[id] = std::move(data);
            }

            /**
             * @brief Set a singleton into the list with a key
             */
            template <class T, typename ... Params>
            void setSingleton(unsigned int id, Params ...params)
            {
                std::lock_guard<std::mutex> lock(_mutex);
                // T value;

                _singletons[id] = std::move(T(params...));
            }
            /**
             * @brief Get a singleton from a key
             */
            template <class T>
            T &getSingleton(unsigned int id)
            {
                std::lock_guard<std::mutex> lock(_mutex);
                auto value = _singletons.find(id);
                if (value == _singletons.end())
                    throw ErrorSingletons("Couldn't find singletons\n");
                return std::any_cast<T&>(value->second);
            }

        private:
            /**
             * @brief Value with id as key and any data
             */
            std::unordered_map<unsigned int, std::any> _singletons;
            mutable std::mutex _mutex;
    };
};
