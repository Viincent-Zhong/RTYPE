/*
** EPITECH PROJECT, 2022
** Project R-TYPE
** File description:
** Text.hpp
*/

#ifndef TEXT_HPP_
#define TEXT_HPP_

#include <unordered_map>
#include "IText.hpp"
#include "raylib.h"

class Text : public PadaEngine::IText {
    public:
        Text();
        Text(std::string const &fileName);
        ~Text();
        void loadFont(std::string const &fileName);
        void drawText(std::string const &text, float textSize, std::pair<float, float> textPos, float spacing, PadaEngine::EngineColor color) const;
        void unloadFont();

    private:
        Font _font;
        bool _isFontLoaded;
        const std::unordered_map<PadaEngine::EngineColor, Color> _colors {
            {PadaEngine::PADA_LIGHTGRAY, LIGHTGRAY},
            {PadaEngine::PADA_DARKGRAY, DARKGRAY},
            {PadaEngine::PADA_YELLOW, YELLOW},
            {PadaEngine::PADA_GOLD, GOLD},
            {PadaEngine::PADA_ORANGE, ORANGE},
            {PadaEngine::PADA_PINK, PINK},
            {PadaEngine::PADA_RED, RED},
            {PadaEngine::PADA_MAROON, MAROON},
            {PadaEngine::PADA_GREEN, GREEN},
            {PadaEngine::PADA_LIME, LIME},
            {PadaEngine::PADA_DARKGREEN, DARKGREEN},
            {PadaEngine::PADA_SKYBLUE, SKYBLUE},
            {PadaEngine::PADA_BLUE, BLUE},
            {PadaEngine::PADA_DARKBLUE, DARKBLUE},
            {PadaEngine::PADA_PURPLE, PURPLE},
            {PadaEngine::PADA_VIOLET, VIOLET},
            {PadaEngine::PADA_DARKPURPLE, DARKPURPLE},
            {PadaEngine::PADA_BEIGE, BEIGE},
            {PadaEngine::PADA_BROWN, BROWN},
            {PadaEngine::PADA_DARKBROWN, DARKBROWN},
            {PadaEngine::PADA_WHITE, WHITE},
            {PadaEngine::PADA_BLACK, BLACK},
            {PadaEngine::PADA_BLANK, BLANK},
            {PadaEngine::PADA_MAGENTA, MAGENTA}
        };
};

#endif /* !TEXT_HPP_ */