/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** SafeVector
*/

#pragma once

#include <vector>
#include <mutex>
#include <utility>
#include <algorithm>

namespace EngineUtils {
    template <class T>
    class SafeVector {
        public:
            SafeVector() {}

            SafeVector(const SafeVector<T> &other)
            {
                std::lock_guard<std::mutex> lock(_mutex);
                _vector = std::move(other._vector);
            }

            SafeVector& operator=(const SafeVector<T> &other)
            {
                std::lock_guard<std::mutex> lock(_mutex);
                _vector = std::move(other._vector);
            }

            SafeVector(SafeVector<T>&& other) {
                std::lock_guard<std::mutex> lock(_mutex);
                _vector = std::move(other._vector);
            }

            ~SafeVector() {}

            void insert(T &in, const int index)
            {
                std::lock_guard<std::mutex> lock(_mutex);
                _vector.insert(in, index);
            }

            void insert(T &&in, const int index)
            {
                std::lock_guard<std::mutex> lock(_mutex);
                _vector.insert(in, index);
            }

            void push_back(T &in)
            {
                std::lock_guard<std::mutex> lock(_mutex);
                _vector.push_back(in);
            }

            void push_back(T &&in)
            {
                std::lock_guard<std::mutex> lock(_mutex);
                _vector.push_back(in);
            }

            std::string &at(const unsigned int index)
            {
                std::lock_guard<std::mutex> lock(_mutex);
                return _vector.at(index);
            }

            typename std::vector<T>::iterator begin()
            {
                std::lock_guard<std::mutex> lock(_mutex);
                return _vector.begin();
            }

            typename std::vector<T>::iterator end()
            {
                std::lock_guard<std::mutex> lock(_mutex);
                return _vector.end();
            }

            typename std::vector<T>::iterator erase(typename std::vector<T>::iterator &iterator)
            {
                std::lock_guard<std::mutex> lock(_mutex);
                return _vector.erase(iterator);
            }

            std::size_t size()
            {
                std::lock_guard<std::mutex> lock(_mutex);
                return _vector.size();
            }

        private:
            std::vector<T> _vector;
            mutable std::mutex _mutex;
    };
};
