/*
** EPITECH PROJECT, 2022
** Project R-TYPE
** File description:
** Text.cpp
*/

#include "Text.hpp"

Text::Text() : _isFontLoaded(false)
{
}

Text::Text(std::string const &fileName) : _isFontLoaded(true)
{
    _font = LoadFont(fileName.c_str());
}

Text::~Text()
{
    if (_isFontLoaded)
        UnloadFont(_font);
}

/**
 * @brief 
 * Load the Font for a text
 * 
 * @param fileName 
 */
void Text::loadFont(std::string const &fileName)
{
    if (!_isFontLoaded) {
        _isFontLoaded = true;
        _font = LoadFont(fileName.c_str());
    }
}

/**
 * @brief 
 * Unload the Font for a text
 * 
 */
void Text::unloadFont()
{
    if (_isFontLoaded) {
        _isFontLoaded = false;
        UnloadFont(_font);
    }
}

/**
 * @brief 
 * Draw the Text
 * 
 * @param text 
 * @param textSize 
 * @param textPos 
 * @param spacing 
 * @param color 
 */
void Text::drawText(std::string const &text, float textSize, std::pair<float, float> textPos, float spacing, PadaEngine::EngineColor color) const
{
    Vector2 pos;

    pos.x = textPos.first;
    pos.y = textPos.second;
    if (_colors.find(color) != _colors.end())
        DrawTextEx(_font, text.c_str(), pos, _font.baseSize * textSize, spacing, _colors.find(color)->second);
}
