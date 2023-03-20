/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** ClientTCPSingletons
*/

#pragma once

namespace EngineClient {
    namespace TCP {
        struct Player {
            unsigned int id = 0;
            char name[20];
        };

        enum SystemEnum {
            SDRAW,
            SBACKGROUND,
            SBUTTON,
            STEXT
        };

        enum SingletonEnum {
            TEXTS,
            ID,
            NAME,
            ROOM_ID,
            GAME_LAUNCHED,
            SEND_LIST,
            SEND_CALLBACK,
            LEAVING,
            LAYER,
            MOUSE_POS,
            MOUSE_LEFT,
            EFFECT_NAME,
            WINDOW_SIZE,
            FPS,
            DELTA_TIME,
            SNAME,
            GAME_LEVEL,
            GAME_ID,
            FONT_NAME,
            PAGE_DATA,
            IP_SERVER,
            TRY_CONNECT,
            PORT,
            END,
            SWITCH_IP_PORT
        };
    };
};