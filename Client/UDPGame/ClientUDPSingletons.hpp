/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** ClientUDPSingletons
*/

#pragma once

namespace EngineClient {
    namespace UDP {
        /**
         * @brief An animation of a player is supposed to have a line of its movement where
         * static = frame 0, left = 1, right = 2, down = 3, and up = 4
         */
        enum MovementAnimation {
            STATIC = 0,
            LEFT = 1,
            RIGHT = 2,
            DOWN = 3,
            UP = 4
        };

        enum SingletonsEnum {
            TEXT,
            ID,
            DRAW_ENTITY,
            CACHE_ENTITY,
            DELTA_TIME,
            LAST_MOVE,
            BULLET_TIMER,
            POS_EXPLOSION,
            ONE_SEC_TIMER,
            EFFECT_NAME,
            END,
            FONT_NAME
        };
    };
};