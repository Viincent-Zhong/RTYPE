/*
** EPITECH PROJECT, 2022
** Project R-TYPE
** File description:
** UDPDataStructure.hpp
*/

#pragma once

#include <cstring>
#include "GameplayC.hpp"
#include "DrawC.hpp"
#include "Registry.hpp"

namespace EngineNetwork {
    namespace UDPDataStructure {
        const std::unordered_map<std::size_t, std::string> idToTexture = {
            {1, "Assets/Images/r-typesheet1.gif"},
            {2, "Assets/Images/r-typesheet2.gif"},
            {3, "Assets/Images/r-typesheet3.gif"},
            {4, "Assets/Images/r-typesheet5.gif"},
            {5, "Assets/Images/r-typesheet8.gif"},
            {6, "Assets/Images/r-typesheet9.gif"},
            {7, "Assets/Images/r-typesheet10.gif"},
            {8, "Assets/Images/r-typesheet11.gif"},
            {9, "Assets/Images/r-typesheet12.gif"},
            {10, "Assets/Images/r-typesheet13.gif"},
            {11, "Assets/Images/r-typesheet14.gif"},
            {12, "Assets/Images/r-typesheet16.gif"},
            {13, "Assets/Images/r-typesheet17.gif"},
            {14, "Assets/Images/r-typesheet18.gif"},
            {15, "Assets/Images/r-typesheet19.gif"},
            {16, "Assets/Images/r-typesheet20.gif"},
            {17, "Assets/Images/r-typesheet21.gif"},
            {18, "Assets/Images/r-typesheet22.gif"},
            {19, "Assets/Images/r-typesheet23.gif"},
            {20, "Assets/Images/r-typesheet24.gif"},
            {21, "Assets/Images/r-typesheet25.gif"},
            {22, "Assets/Images/r-typesheet26.gif"},
            {23, "Assets/Images/r-typesheet27.gif"},
            {24, "Assets/Images/r-typesheet28.gif"},
            {25, "Assets/Images/r-typesheet29.gif"},
            {26, "Assets/Images/r-typesheet30.gif"},
            {27, "Assets/Images/r-typesheet30a.gif"},
            {28, "Assets/Images/r-typesheet31.gif"},
            {29, "Assets/Images/r-typesheet32.gif"},
            {30, "Assets/Images/r-typesheet33.gif"},
            {31, "Assets/Images/r-typesheet34.gif"},
            {32, "Assets/Images/r-typesheet35.gif"},
            {33, "Assets/Images/r-typesheet36.gif"},
            {34, "Assets/Images/r-typesheet37.gif"},
            {35, "Assets/Images/r-typesheet38.gif"},
            {36, "Assets/Images/r-typesheet39.gif"},
            {37, "Assets/Images/r-typesheet40.gif"},
            {38, "Assets/Images/r-typesheet41.gif"},
            {39, "Assets/Images/r-typesheet42.gif"},
            {40, "Assets/Images/r-typesheet43.gif"},
            {41, "Assets/Images/r-typesheet44.gif"},
            {42, "Assets/Images/r-typesheet-boost-missile.png"}
        };

        const std::unordered_map<std::string, std::size_t> textureToID = {
            {"Assets/Images/r-typesheet1.gif", 1},
            {"Assets/Images/r-typesheet2.gif", 2},
            {"Assets/Images/r-typesheet3.gif", 3},
            {"Assets/Images/r-typesheet5.gif", 4},
            {"Assets/Images/r-typesheet8.gif", 5},
            {"Assets/Images/r-typesheet9.gif", 6},
            {"Assets/Images/r-typesheet10.gif", 7},
            {"Assets/Images/r-typesheet11.gif", 8},
            {"Assets/Images/r-typesheet12.gif", 9},
            {"Assets/Images/r-typesheet13.gif", 10},
            {"Assets/Images/r-typesheet14.gif", 11},
            {"Assets/Images/r-typesheet16.gif", 12},
            {"Assets/Images/r-typesheet17.gif", 13},
            {"Assets/Images/r-typesheet18.gif", 14},
            {"Assets/Images/r-typesheet19.gif", 15},
            {"Assets/Images/r-typesheet20.gif", 16},
            {"Assets/Images/r-typesheet21.gif", 17},
            {"Assets/Images/r-typesheet22.gif", 18},
            {"Assets/Images/r-typesheet23.gif", 19},
            {"Assets/Images/r-typesheet24.gif", 20},
            {"Assets/Images/r-typesheet25.gif", 21},
            {"Assets/Images/r-typesheet26.gif", 22},
            {"Assets/Images/r-typesheet27.gif", 23},
            {"Assets/Images/r-typesheet28.gif", 24},
            {"Assets/Images/r-typesheet29.gif", 25},
            {"Assets/Images/r-typesheet30.gif", 26},
            {"Assets/Images/r-typesheet30a.gif", 27},
            {"Assets/Images/r-typesheet31.gif", 28},
            {"Assets/Images/r-typesheet32.gif", 29},
            {"Assets/Images/r-typesheet33.gif", 30},
            {"Assets/Images/r-typesheet34.gif", 31},
            {"Assets/Images/r-typesheet35.gif", 32},
            {"Assets/Images/r-typesheet36.gif", 33},
            {"Assets/Images/r-typesheet37.gif", 34},
            {"Assets/Images/r-typesheet38.gif", 35},
            {"Assets/Images/r-typesheet39.gif", 36},
            {"Assets/Images/r-typesheet40.gif", 37},
            {"Assets/Images/r-typesheet41.gif", 38},
            {"Assets/Images/r-typesheet42.gif", 39},
            {"Assets/Images/r-typesheet43.gif", 40},
            {"Assets/Images/r-typesheet44.gif", 41},
            {"Assets/Images/r-typesheet-boost-missile.png", 42}
        };

        enum codeUDP {
            PLAYER_FIRE = 3,
            MOVE_PLAYER = 4,
            RECEIVE_ID_CONNECTION = 5,
            STATUS_GAME = 6,
            DESTROY = 7,
            LINK = 8
        };

        struct EntityTransfer {
            std::size_t id;
            // Texture component
            std::size_t textureID;
            // Position component
            float pos_x;
            float pos_y;
            // Rectangle component
            float rect_x;
            float rect_y;
            float width;
            float height;
            //Frame Speed
            float frame_speed_x;
            float frame_speed_y;
            // Rectangle start point 
            float start_point_x;
            float start_point_y;
            float framemax;
            // Direction component
            float direction_x;
            float direction_y;
            float direction_x_decimal_part; // rounded to 4 after comma
            float direction_y_decimal_part; // rounded to 4 after comma
            bool neg_direction_x;
            bool neg_direction_y;
            // Faction component
            unsigned int faction;
        };

        /**
         * @brief Return an entityTransfer and a bool of if it was correctly assigned or not
         */
        static std::pair<EntityTransfer, bool> convertToEntityTransfer(std::size_t id, Registry &r)
        {
            EntityTransfer transfer;
            transfer.id = 0;
            transfer.textureID = 0;
            transfer.pos_x = 0;
            transfer.pos_y = 0;
            transfer.rect_x = 0;
            transfer.rect_y = 0;
            transfer.width = 0;
            transfer.height = 0;
            transfer.frame_speed_x = 0;
            transfer.frame_speed_y = 0;
            transfer.start_point_x = 0;
            transfer.start_point_y = 0;
            transfer.framemax = 0;
            transfer.direction_x = 0;
            transfer.direction_y = 0;
            transfer.direction_x_decimal_part = 0;
            transfer.direction_y_decimal_part = 0;
            transfer.neg_direction_x = false;
            transfer.neg_direction_y = false;
            transfer.faction = 0;
            auto const &positions = r.getComponents<EngineComponent::Position>();
            auto const &rectangles = r.getComponents<EngineComponent::SpriteSheet>();
            auto const &textures = r.getComponents<EngineComponent::Drawable>();
            auto const &directions = r.getComponents<EngineComponent::Direction>();
            auto const &factions = r.getComponents<EngineComponent::Faction>();

            if (id >= positions.size() && id >= rectangles.size() && id >= textures.size() && id >= directions.size() && id >= factions.size())
                return {transfer, false};
            auto const &position = positions[id];
            auto const &sprite = rectangles[id];
            auto const &texture = textures[id];
            auto const &direction = directions[id];
            auto const &faction = factions[id];
            if (!position || !sprite || !texture || !direction || !faction)
                return {transfer, false};
            transfer.id = id;
            auto textureID = EngineNetwork::UDPDataStructure::textureToID.find(texture.value().texture);
            if (textureID != EngineNetwork::UDPDataStructure::textureToID.end())
                transfer.textureID = textureID->second;
            transfer.pos_x = position.value().pos.x;
            transfer.pos_y = position.value().pos.y;
            transfer.rect_x = sprite.value().rec.x;
            transfer.rect_y = sprite.value().rec.y;
            transfer.width = sprite.value().rec.width;
            transfer.height = sprite.value().rec.heigth;
            transfer.frame_speed_x = sprite.value().xFrameSpeed;
            transfer.frame_speed_y = sprite.value().yFrameSpeed;
            transfer.start_point_x = sprite.value().xStartPoint;
            transfer.start_point_y = sprite.value().yStartPoint;
            transfer.framemax = sprite.value().frameMax;
            transfer.faction = faction.value().faction;
            transfer.direction_x = direction.value().xDirection;
            transfer.direction_y = direction.value().yDirection;
            // negative number x
            if (transfer.direction_x < 0.f) {
                transfer.neg_direction_x = true;
                transfer.direction_x *= -1;
            }
            // negative number y
            if (transfer.direction_y < 0.f) {
                transfer.neg_direction_y = true;
                transfer.direction_y *= -1;
            }
            return {transfer, true};
        }

        struct PlayerMove {
            std::size_t id;
            float moveX;
            float moveX_decimal_part;
            bool negX;
            float moveY;
            float moveY_decimal_part;
            bool negY;
        };

        static PlayerMove convertToPlayerMove(unsigned int id, float move_x, float move_y)
        {
            PlayerMove move;
            move.id = id;
            move.moveX = move_x;
            move.moveY = move_y;
            move.negX = false;
            move.negY = false;
            if (move_x < 0) {
                move.moveX *= -1;
                move.negX = true;
            }
            if (move_y < 0) {
                move.moveY *= -1;
                move.negY = true;
            }
            return move;
        }
    };
};
