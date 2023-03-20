/*
** EPITECH PROJECT, 2022
** Project R-TYPE
** File description:
** IText.hpp
*/

#pragma once

#include <utility>
#include <string>

namespace PadaEngine {
    enum EngineColor {
        PADA_LIGHTGRAY,
        PADA_DARKGRAY,
        PADA_YELLOW,
        PADA_GOLD,  
        PADA_ORANGE,
        PADA_PINK,
        PADA_RED,
        PADA_MAROON,
        PADA_GREEN,
        PADA_LIME,
        PADA_DARKGREEN,
        PADA_SKYBLUE,
        PADA_BLUE,
        PADA_DARKBLUE,
        PADA_PURPLE,
        PADA_VIOLET,
        PADA_DARKPURPLE,
        PADA_BEIGE,
        PADA_BROWN,
        PADA_DARKBROWN,
        PADA_WHITE,
        PADA_BLACK,
        PADA_BLANK,
        PADA_MAGENTA
    };

    class IText {
        public:
            /**
             * @brief Destroy the IText object
             * 
             */
            virtual ~IText() = default;

            /**
             * @brief load the given font
             * 
             * @param fileName 
             */
            virtual void loadFont(std::string const &fileName) = 0;

            /**
             * @brief draw text with parameters
             * 
             * @param text
             * @param textSize 
             * @param textPos 
             * @param spacing space between letters
             * @param color 
             */
            virtual void drawText(std::string const &text, float textSize, std::pair<float, float> textPos, float spacing, EngineColor color) const = 0;

            /**
             * @brief unload font
             * 
             */
            virtual void unloadFont() = 0;
    };
}
