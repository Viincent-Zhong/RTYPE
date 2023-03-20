/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Queue
*/

#pragma once

#include <queue>
#include <mutex>
#include <utility>

namespace EngineUtils {
    template<typename T>
    class Queue {
        public:
            Queue()
            {
            };

            Queue(const Queue<T> &other)
            {
                std::lock_guard<std::mutex> lock(_mutex);
                _queue = std::move(other._queue);
            }

            Queue& operator=(const Queue<T> &other)
            {
                std::lock_guard<std::mutex> lock(_mutex);
                _queue = std::move(other._queue);
            }

            Queue(Queue<T>&& other) {
                std::lock_guard<std::mutex> lock(_mutex);
                _queue = std::move(other._queue);
            }
            
            ~Queue() {}

            unsigned long size() const {
                std::lock_guard<std::mutex> lock(_mutex);
                return _queue.size();
            }

            void pop() {
                std::lock_guard<std::mutex> lock(_mutex);
                if (_queue.empty()) {
                    return;
                }
                _queue.pop();
            }

            void push(const T &item) {
                std::lock_guard<std::mutex> lock(_mutex);
                _queue.push(item);
            }

            void push(const T &&item) {
                std::lock_guard<std::mutex> lock(_mutex);
                _queue.push(item);
            }

            T front() {
                std::lock_guard<std::mutex> lock(_mutex);
                return _queue.front();
            }
        private:
            std::queue<T> _queue;
            mutable std::mutex _mutex;
            bool empty() const {
                return _queue.empty();
            }
    };
};
