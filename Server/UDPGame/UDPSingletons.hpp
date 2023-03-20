/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** UDPSingletons
*/

#pragma once

#include <array>
#include <stdint.h>
#include <vector>
#include "Time.hpp"
#include "EntityCache.hpp"
#include "Queue.hpp"

namespace EngineServer {
    namespace UDP {
        enum SingletonsEnum {
            AVAILABLE_PLAYER,
            CORE_PLAYER,
            PLAYER_TO_DESTROY,
            SEND_LIST,
            DELTA_TIME,
            CACHE_ENTITY,
            WINDOW_SIZE,
            FPS,
            ONE_SEC_TIMER,
            MINI_TIMER,
            WAVER_OVER,
            WAVES,
            SEND_CALLBACK,
            GAMEID
        };
    };
};