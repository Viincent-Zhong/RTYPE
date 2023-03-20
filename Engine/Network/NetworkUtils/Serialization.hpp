/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Serialisation
*/

#pragma once


#include <iostream>
#include <typeinfo>
#include <typeindex>
#include <unordered_map>
#include <any>
#include <array>
#include <cmath>
#include "ErrorLoader.hpp"
#include "DataStructure.hpp"
#include "TCPDataStructure.hpp"
#include "UDPDataStructure.hpp"

namespace EngineNetwork {

    /**
     * @brief Enum to describe a type
     */
    enum Types {
        NOTHING,
        ENTITY_TRANSFER,
        MOVEMENT_ENTITY,
        CONNECTION_PLAYER,
        ENTITY_SHOOT,
        TRANSFER_ID,
        TRANSFER_ID_CONTENT_NUMBER,
        TRANSFER_ROOM_CONTENT
    };

    /**
     * @brief Map with an enum "Types" as key and its size
     */
    inline std::unordered_map<Types, uint16_t> EnumSize = {
        {Types::ENTITY_TRANSFER, 20},
        {Types::MOVEMENT_ENTITY, 7},
        {Types::ENTITY_SHOOT, 2},
        {Types::TRANSFER_ID, 1},
        {Types::TRANSFER_ID_CONTENT_NUMBER, 2},
        {Types::TRANSFER_ROOM_CONTENT, 22}
    };

    /**
     * @brief Map with a type_index as key and a enum "Types" as value
     */
    inline std::unordered_map<std::type_index, Types> TypeToEnum = {
        {typeid(UDPDataStructure::EntityTransfer), Types::ENTITY_TRANSFER},
        {typeid(UDPDataStructure::PlayerMove), Types::MOVEMENT_ENTITY},
        {typeid(DataStructure::IDStatus), Types::ENTITY_SHOOT},
        {typeid(DataStructure::ID), Types::TRANSFER_ID},
        {typeid(DataStructure::IDContentNumber), Types::TRANSFER_ID_CONTENT_NUMBER},
        {typeid(TCPDataStructure::RoomContent), Types::TRANSFER_ROOM_CONTENT}
    };

    /**
     * @brief Header containing the code describing the action and a type describing the type of what is sent after the header
     * 
     */
    struct MessageHeader {
    	int code;
        Types type;
    };

    namespace Serialisation {
        /**
         * @brief Pack a structure with a header ready to be writed
         * 
         * @tparam Type of the struct that will be sent
         * @param header Header with the action code and an id of the type sent (THIS FUNCTION WILL FILL THE ID FOR YOU)
         * @param data Structure to be sent (in our Engine most likely TransferPlayer or PlayerConnection or UDPDataStructure::PlayerMove or DataStructure::IDStatus)
         */
        template <typename T>
        inline std::pair<std::array<uint16_t, 50>, std::size_t> pack(MessageHeader &header, std::any &&data)
        {
            std::array<uint16_t, 50> message = {0};
            auto type = TypeToEnum.find(typeid(T));

            if (type == TypeToEnum.end())
                throw ErrorSerialisation("Bad type\n");

            auto tSize = EnumSize.find(type->second);
            if (tSize == EnumSize.end())
                throw ErrorSerialisation("Bad type\n");

            // Size of header + type + 1
            std::size_t size = sizeof(uint16_t) * (3 + tSize->second);
            // header.type = type->second;
            message[0] = header.code;
            message[1] = type->second;
            if (type->second == Types::ENTITY_TRANSFER) {
                UDPDataStructure::EntityTransfer t_entity = std::any_cast<UDPDataStructure::EntityTransfer>(data);
                message[2] = (uint16_t)t_entity.id;
                message[3] = (uint16_t)t_entity.textureID;
                message[4] = (uint16_t)t_entity.pos_x;
                message[5] = (uint16_t)t_entity.pos_y;
                message[6] = (uint16_t)t_entity.rect_x;
                message[7] = (uint16_t)t_entity.rect_y;
                message[8] = (uint16_t)t_entity.width;
                message[9] = (uint16_t)t_entity.height;
                message[10] = (uint16_t)t_entity.frame_speed_x;
                message[11] = (uint16_t)t_entity.frame_speed_y;
                message[12] = (uint16_t)t_entity.start_point_x;
                message[13] = (uint16_t)t_entity.start_point_y;
                message[14] = (uint16_t)t_entity.framemax;
                message[15] = (uint16_t)t_entity.faction;

                message[16] = (uint16_t)std::floor(t_entity.direction_x); // round down
                message[17] = (uint16_t)std::floor(t_entity.direction_y); // round down
                message[18] = (uint16_t)((t_entity.direction_x - message[16]) * 10000); // get the decimal part as uint16
                message[19] = (uint16_t)((t_entity.direction_y - message[17]) * 10000); // get the decimal part as uint16
                message[20] = (uint16_t)t_entity.neg_direction_x;
                message[21] = (uint16_t)t_entity.neg_direction_y;
                std::cout << "Neg ["<< message[20] << ", " << message[21] << "] | ";
            }
            if (type->second == Types::MOVEMENT_ENTITY) {
                UDPDataStructure::PlayerMove t_move = std::any_cast<UDPDataStructure::PlayerMove>(data);
                message[2] = (uint16_t)t_move.id;
                message[3] = (uint16_t)std::floor(t_move.moveX); // round down moveX
                message[4] = (uint16_t)((t_move.moveX - message[3]) * 10000); // get the decimal part of moveX
                message[5] = (uint16_t)t_move.negX;
                message[6] = (uint16_t)std::floor(t_move.moveY); // round down moveY
                message[7] = (uint16_t)((t_move.moveY - message[6]) * 10000); // get the decimal part of moveY
                message[8] = (uint16_t)t_move.negY;
            }
            if (type->second == Types::TRANSFER_ID) {
                DataStructure::ID t_id = std::any_cast<DataStructure::ID>(data);
                message[2] = (uint16_t)t_id.id;
            }
            if (type->second == Types::ENTITY_SHOOT) {
                DataStructure::IDStatus t_fire = std::any_cast<DataStructure::IDStatus>(data);
                message[2] = (uint16_t)t_fire.id;
                message[3] = (uint16_t)t_fire.isOk;
            }
            if (type->second == Types::TRANSFER_ID_CONTENT_NUMBER) {
                DataStructure::IDContentNumber id = std::any_cast<DataStructure::IDContentNumber>(data);
                message[2] = (uint16_t)id.id;
                message[3] = (uint16_t)id.number;
            }
            if (type->second == Types::TRANSFER_ROOM_CONTENT) {
                TCPDataStructure::RoomContent room = std::any_cast<TCPDataStructure::RoomContent>(data);
                message[2] = (uint16_t)room.roomID;
                message[3] = (uint16_t)room.playerID;
                for (unsigned int i = 4, x = 0; x < 20; ++i, ++x)
                    message[i] = (uint16_t)room.player[x];
            }
            return {message, size};
        }

        /**
         * @brief Pack a structure with a header ready to be writed
         * 
         * @tparam Type of the struct that will be sent
         * @param header Header with the action code and an id of the type sent (THIS FUNCTION WILL FILL THE ID FOR YOU)
         * @param data Structure to be sent (in our Engine most likely TransferPlayer or PlayerConnection or UDPDataStructure::PlayerMove or DataStructure::IDStatus)
         */
        template <typename T>
        inline std::pair<std::array<uint16_t, 50>, std::size_t> pack(MessageHeader &&header, std::any &&data)
        {
            std::array<uint16_t, 50> message = {0};
            auto type = TypeToEnum.find(typeid(T));

            if (type == TypeToEnum.end())
                throw ErrorSerialisation("Bad type\n");

            auto tSize = EnumSize.find(type->second);
            if (tSize == EnumSize.end())
                throw ErrorSerialisation("Bad type\n");

            // Size of header + type + 1
            std::size_t size = sizeof(uint16_t) * (3 + tSize->second);

            // header.type = type->second;
            message[0] = header.code;
            message[1] = type->second;
            if (type->second == Types::ENTITY_TRANSFER) {
                UDPDataStructure::EntityTransfer t_entity = std::any_cast<UDPDataStructure::EntityTransfer>(data);
                message[2] = (uint16_t)t_entity.id;
                message[3] = (uint16_t)t_entity.textureID;
                message[4] = (uint16_t)t_entity.pos_x;
                message[5] = (uint16_t)t_entity.pos_y;
                message[6] = (uint16_t)t_entity.rect_x;
                message[7] = (uint16_t)t_entity.rect_y;
                message[8] = (uint16_t)t_entity.width;
                message[9] = (uint16_t)t_entity.height;
                message[10] = (uint16_t)t_entity.frame_speed_x;
                message[11] = (uint16_t)t_entity.frame_speed_y;
                message[12] = (uint16_t)t_entity.start_point_x;
                message[13] = (uint16_t)t_entity.start_point_y;
                message[14] = (uint16_t)t_entity.framemax;
                message[15] = (uint16_t)t_entity.faction;

                message[16] = (uint16_t)std::floor(t_entity.direction_x); // round down
                message[17] = (uint16_t)std::floor(t_entity.direction_y); // round down
                message[18] = (uint16_t)((t_entity.direction_x - message[16]) * 10000); // get the decimal part as uint16
                message[19] = (uint16_t)((t_entity.direction_y - message[17]) * 10000); // get the decimal part as uint16
                message[20] = (uint16_t)t_entity.neg_direction_x;
                message[21] = (uint16_t)t_entity.neg_direction_y;
            }
            if (type->second == Types::MOVEMENT_ENTITY) {
                UDPDataStructure::PlayerMove t_move = std::any_cast<UDPDataStructure::PlayerMove>(data);
                message[2] = (uint16_t)t_move.id;
                message[3] = (uint16_t)std::floor(t_move.moveX); // round down moveX
                message[4] = (uint16_t)((t_move.moveX - message[3]) * 10000); // get the decimal part of moveX
                message[5] = (uint16_t)t_move.negX;
                message[6] = (uint16_t)std::floor(t_move.moveY); // round down moveY
                message[7] = (uint16_t)((t_move.moveY - message[6]) * 10000); // get the decimal part of moveY
                message[8] = (uint16_t)t_move.negY;
            }
            if (type->second == Types::TRANSFER_ID) {
                DataStructure::ID t_id = std::any_cast<DataStructure::ID>(data);
                message[2] = (uint16_t)t_id.id;
            }
            if (type->second == Types::ENTITY_SHOOT) {
                DataStructure::IDStatus t_fire = std::any_cast<DataStructure::IDStatus>(data);
                message[2] = (uint16_t)t_fire.id;
                message[3] = (uint16_t)t_fire.isOk;
            }
            if (type->second == Types::TRANSFER_ID_CONTENT_NUMBER) {
                DataStructure::IDContentNumber id = std::any_cast<DataStructure::IDContentNumber>(data);
                message[2] = (uint16_t)id.id;
                message[3] = (uint16_t)id.number;
            }
            if (type->second == Types::TRANSFER_ROOM_CONTENT) {
                TCPDataStructure::RoomContent room = std::any_cast<TCPDataStructure::RoomContent>(data);
                message[2] = (uint16_t)room.roomID;
                message[3] = (uint16_t)room.playerID;
                for (unsigned int i = 4, x = 0; x < 20; ++i, ++x)
                    message[i] = (uint16_t)room.player[x];
            }
            return {message, size};
        }

        /**
         * @brief Pack only an header ready to be writed
         * 
         * @param header Header with the action code
         */
        inline std::pair<std::array<uint16_t, 50>, std::size_t> pack(MessageHeader &header)
        {
            std::array<uint16_t, 50> message = {0};
            message[0] = header.code;
            return {message, 2};
        }

        /**
         * @brief Pack only an header ready to be writed
         * 
         * @param header Header with the action code
         */
        inline std::pair<std::array<uint16_t, 50>, std::size_t> pack(MessageHeader &&header)
        {
            std::array<uint16_t, 50> message = {0};
            message[0] = header.code;
            return {message, 2};
        }

        /**
         * @brief To use the return value you need to std::any_cast<YourType>
         * @param data Data to unpack into a std::any
         * @param byteReaded Size of data
         */
        inline std::any unpack(uint16_t *data, std::size_t byteReaded)
        {
            if (!data || byteReaded < 2)
                throw ErrorSerialisation("Unknown header\n");
            Types type = (Types)data[1];
            if (type == Types::ENTITY_TRANSFER && byteReaded >= 20) {
                UDPDataStructure::EntityTransfer entity;
                entity.id = (std::size_t)data[2];
                entity.textureID = (std::size_t)data[3];
                entity.pos_x = (float)data[4];
                entity.pos_y = (float)data[5];
                entity.rect_x = (float)data[6];
                entity.rect_y = (float)data[7];
                entity.width = (float)data[8];
                entity.height = (float)data[9];
                entity.frame_speed_x = (float)data[10];
                entity.frame_speed_y = (float)data[11];
                entity.start_point_x = (float)data[12];
                entity.start_point_y = (float)data[13];
                entity.framemax = (float)data[14];
                entity.faction = (unsigned int)data[15];

                entity.direction_x = (float)(data[16] + (float)(((float)(data[18])) / 10000)); // data + decimal part
                entity.direction_y = (float)(data[17] + (float)(((float)(data[19])) / 10000)); // data + decimal part
                entity.direction_x_decimal_part = (float)data[18];
                entity.direction_y_decimal_part = (float)data[19];
                entity.neg_direction_x = (bool)data[20];
                entity.neg_direction_y = (bool)data[21];
                if (entity.neg_direction_x == true) // if neg make the number neg
                    entity.direction_x *= -1;
                if (entity.neg_direction_y == true) // if neg make the number neg
                    entity.direction_y *= -1;
                return entity;
            }
            if (type == Types::MOVEMENT_ENTITY && byteReaded >= 7) {
                UDPDataStructure::PlayerMove move;
                move.id = (std::size_t)data[2];
                move.negX = (bool)data[5];
                move.negY = (bool)data[8];
                move.moveX_decimal_part = (float)data[4];
                move.moveY_decimal_part = (float)data[7];
                move.moveX = (float)(data[3] + (float)(((float)(move.moveX_decimal_part)) / 10000)); // moveX + decimal part
                move.moveY = (float)(data[6] + (float)(((float)(move.moveY_decimal_part)) / 10000)); // moveX + decimal part
                if (move.negX)
                    move.moveX *= -1;
                if (move.negY)
                    move.moveY *= -1;
                return move;
            }
            if (type == Types::TRANSFER_ID && byteReaded >= 3) {
                DataStructure::ID id;
                id.id = (std::size_t)data[2];
                return id;
            }
            if (type == Types::ENTITY_SHOOT && byteReaded >= 4) {
                DataStructure::IDStatus t_fire;
                t_fire.id = (std::size_t)data[2];
                t_fire.isOk = (bool)data[3];
                return t_fire;
            }
            if (type == Types::TRANSFER_ID_CONTENT_NUMBER && byteReaded >= 4) {
                DataStructure::IDContentNumber id_number;
                id_number.id = (std::size_t)data[2];
                id_number.number = (unsigned int)data[3];
                return id_number;
            }
            if (type == Types::TRANSFER_ROOM_CONTENT && byteReaded >= 22) {
                TCPDataStructure::RoomContent room;
                room.roomID = (unsigned int)data[2];
                room.playerID = (unsigned int)data[3];
                for (unsigned int i = 4, x = 0; x < 20; ++i, ++x)
                    room.player[x] = (char)data[i];
                return room;
            }
            throw ErrorSerialisation("Unknown type\n");
        }

        /**
         * @brief To use the return value you need to std::any_cast<YourType>
         * @param data Data to unpack into a std::any
         * @param byteReaded Size of data
         */
        inline std::any unpack(std::array<uint16_t, 50> &data, std::size_t byteReaded)
        {
            if (byteReaded < 2)
                throw ErrorSerialisation("Unknown header\n");
            Types type = (Types)data.at(1);
            if (type == Types::ENTITY_TRANSFER && byteReaded >= 20) {
                UDPDataStructure::EntityTransfer entity;
                entity.id = (std::size_t)data[2];
                entity.textureID = (std::size_t)data[3];
                entity.pos_x = (float)data[4];
                entity.pos_y = (float)data[5];
                entity.rect_x = (float)data[6];
                entity.rect_y = (float)data[7];
                entity.width = (float)data[8];
                entity.height = (float)data[9];
                entity.frame_speed_x = (float)data[10];
                entity.frame_speed_y = (float)data[11];
                entity.start_point_x = (float)data[12];
                entity.start_point_y = (float)data[13];
                entity.framemax = (float)data[14];
                entity.faction = (unsigned int)data[15];

                entity.direction_x = (float)(data[16] + (float)(((float)(data[18])) / 10000)); // data + decimal part
                entity.direction_y = (float)(data[17] + (float)(((float)(data[19])) / 10000)); // data + decimal part
                entity.direction_x_decimal_part = (float)data[18];
                entity.direction_y_decimal_part = (float)data[19];
                entity.neg_direction_x = (bool)data[20];
                entity.neg_direction_y = (bool)data[21];
                if (entity.neg_direction_x == true) // if neg make the number neg
                    entity.direction_x *= -1;
                if (entity.neg_direction_y == true) // if neg make the number neg
                    entity.direction_y *= -1;
                return entity;
            }
            if (type == Types::MOVEMENT_ENTITY && byteReaded >= 7) {
                UDPDataStructure::PlayerMove move;
                move.id = (std::size_t)data[2];
                move.negX = (bool)data[5];
                move.negY = (bool)data[8];
                move.moveX_decimal_part = (float)data[4];
                move.moveY_decimal_part = (float)data[7];
                move.moveX = (float)(data[3] + (float)(((float)(move.moveX_decimal_part)) / 10000)); // moveX + decimal part
                move.moveY = (float)(data[6] + (float)(((float)(move.moveY_decimal_part)) / 10000)); // moveX + decimal part
                if (move.negX)
                    move.moveX *= -1;
                if (move.negY)
                    move.moveY *= -1;
                return move;
            }
            if (type == Types::TRANSFER_ID && byteReaded >= 3) {
                DataStructure::ID id;
                id.id = (std::size_t)data.at(2);
                return id;
            }
            if (type == Types::ENTITY_SHOOT && byteReaded >= 4) {
                DataStructure::IDStatus t_fire;
                t_fire.id = (std::size_t)data.at(2);
                t_fire.isOk = (bool)data.at(3);
                return t_fire;
            }
            if (type == Types::TRANSFER_ID_CONTENT_NUMBER && byteReaded >= 4) {
                DataStructure::IDContentNumber id_number;
                id_number.id = (std::size_t)data[2];
                id_number.number = (unsigned int)data[3];
                return id_number;
            }
            if (type == Types::TRANSFER_ROOM_CONTENT && byteReaded >= 22) {
                TCPDataStructure::RoomContent room;
                room.roomID = (unsigned int)data[2];
                room.playerID = (unsigned int)data[3];
                for (unsigned int i = 4, x = 0; x < 20; ++i, ++x)
                    room.player[x] = (char)data[i];
                return room;
            }
            throw ErrorSerialisation("Unknown type\n");
        }
    };
};
