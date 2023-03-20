/*
** EPITECH PROJECT, 2022
** B-CPP-500-PAR-5-1-rtype-pierre-alexandre.delgado-arevalo
** File description:
** Time.hpp
*/

#pragma once

#include <chrono>

namespace EngineUtils {
    class Timer {
        public:
            Timer() {};
            Timer(float timer);
            ~Timer() {};
            void StartTimer();
            void UpdateTimer(float deltaTime);
            bool TimerDone();
            void RestartTimer();
            void SetTimer(float time);

        private:
            float _lifeTime;
            float _maxTime;
    };

    class DeltaTime {
        public:
            DeltaTime() {
                _lastUpdate = std::chrono::high_resolution_clock::now();
            };
            ~DeltaTime() {};
            float getDeltaTime();
            void updateDeltaTime();
        
        private:
            float _deltaTime = 0;
            std::chrono::high_resolution_clock::time_point _now;
            std::chrono::high_resolution_clock::time_point _lastUpdate;
    };
}