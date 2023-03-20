/*
** EPITECH PROJECT, 2022
** B-CPP-500-PAR-5-1-rtype-pierre-alexandre.delgado-arevalo
** File description:
** Time.cpp
*/

#include <cstdint>
#include <iostream>
#include "Time.hpp"

EngineUtils::Timer::Timer(float timer)
{
    _lifeTime = timer;
    _maxTime = timer;
}

/**
 * @brief 
 * Start the timer 
 * 
 */
void EngineUtils::Timer::StartTimer()
{
    _lifeTime = _maxTime;
}

/**
 * @brief 
 * Update the timer
 * 
 * @param deltaTime 
 */
void EngineUtils::Timer::UpdateTimer(float deltaTime)
{
    if (_lifeTime > 0)
        _lifeTime -= deltaTime;
}

/**
 * @brief 
 * Check if the timer is done or not
 * 
 * @return true 
 * @return false 
 */
bool EngineUtils::Timer::TimerDone()
{
    return _lifeTime <= 0;
}

/**
 * @brief 
 * Restart the timer
 * 
 */
void EngineUtils::Timer::RestartTimer()
{
    _lifeTime = _maxTime;
}

/**
 * @brief 
 * Set the timer to a certain time
 * 
 * @param time 
 */
void EngineUtils::Timer::SetTimer(float time)
{
    _maxTime = time;
}

/**
 * @brief 
 * Get the DeltaTime
 * 
 * @return float 
 */
float EngineUtils::DeltaTime::getDeltaTime()
{
    return _deltaTime;
}

/**
 * @brief 
 * Update the DeltaTime
 * 
 */
void EngineUtils::DeltaTime::updateDeltaTime()
{
    _now = std::chrono::high_resolution_clock::now();
    _deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(_now - _lastUpdate).count() / 1000000.0f;
    _lastUpdate = _now;
}
