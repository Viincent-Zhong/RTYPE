/*
** EPITECH PROJECT, 2022
** Project R-TYPE
** File description:
** IElement.hpp
*/

#pragma once

#include <string>

namespace PadaEngine {
    /** @brief
        Rectangle top-left corner position x
        Rectangle top-left corner position y
        Rectangle width
        Rectangle height
     */
    struct Rectangle {
        float x;
        float y;
        float width;
        float heigth;
    };

    struct Position {
        float x;
        float y;
    };

    class IElement {
        public:
            /**
             * @brief Destroy the Element object
             * 
             */
            virtual ~IElement() = default;

            /**
             * @brief Create theElement object
             * 
             * @param file 
             */
            virtual void createObject(std::string const &file) = 0;

            /**
             * @brief draw the sprite of the element
             * 
             */
            virtual void draw(PadaEngine::Position const &pos) const = 0;

            /**
             * @brief draw a rectangle of the texture (used for spritesheet)
             * 
             *  rec is a vector of 4 float : Rectangle top-left corner position x
                                             Rectangle top-left corner position y
                                             Rectangle width
                                             Rectangle height
             */
            virtual void drawRec(PadaEngine::Position const &pos, PadaEngine::Rectangle const &rec) const = 0;
    };
}
