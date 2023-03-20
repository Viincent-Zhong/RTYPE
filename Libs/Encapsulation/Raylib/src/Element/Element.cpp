/*
** EPITECH PROJECT, 2022
** Project R-TYPE
** File description:
** Element.cpp
*/

#include "Element.hpp"

Element::Element() : _created(false)
{
}

Element::Element(std::string const &file)
: _created(true)
{
    _texture = LoadTexture(file.c_str());
}

Element::~Element()
{
    if (_created)
        UnloadTexture(_texture);
}

/**
 * @brief 
 * Create an object from a file
 * 
 * @param file 
 */
void Element::createObject(std::string const &file)
{
    _texture = LoadTexture(file.c_str());
    _created = true;
}

/**
 * @brief 
 * Draw an object with a certain position
 * 
 * @param pos 
 */
void Element::draw(PadaEngine::Position const &pos) const
{
    DrawTexture(_texture, pos.x, pos.y, WHITE);
}

/**
 * @brief 
 * Draw the rect (hitbox) of an object
 * 
 * @param pos 
 * @param rec 
 */
void Element::drawRec(PadaEngine::Position const &pos, PadaEngine::Rectangle const &rec) const
{
    Vector2 tmpPos = {pos.x, pos.y};
    Rectangle tmpRec = {rec.x, rec.y, rec.width, rec.heigth};
    DrawTextureRec(_texture, tmpRec, tmpPos, WHITE);
}