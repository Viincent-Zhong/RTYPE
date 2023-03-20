/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Collision
*/

#include "IElement.hpp"

namespace EngineUtils {
    /**
     * @brief 
     * Check a collision between two rect (hitbox) of a "sprite"
     * 
     * @param rec1 
     * @param rec2 
     * @return true 
     * @return false 
     */
    bool collisionBetweenRec(std::pair<PadaEngine::Position, PadaEngine::Rectangle> const &rec1, std::pair<PadaEngine::Position, PadaEngine::Rectangle> const &rec2)
    {
        if ((rec1.first.x < (rec2.first.x + rec2.second.width) && (rec1.first.x + rec1.second.width) > rec2.first.x) &&
        (rec1.first.y < (rec2.first.y + rec2.second.heigth) && (rec1.first.y + rec1.second.heigth) > rec2.first.y))
            return true;
        return false;
    }

    /**
     * @brief 
     * Check a collision between the position in the window of two Sprite and their two rect (hitbox) of a "sprite"
     * 
     * @param pos 
     * @param rec 
     * @return true 
     * @return false 
     */
    bool collisionPosWithRec(PadaEngine::Position const &pos, std::pair<PadaEngine::Position, PadaEngine::Rectangle> const &rec)
    {
        if ((pos.x >= rec.first.x) && (pos.x <= (rec.first.x + rec.second.width)) && (pos.y >= rec.first.y) && (pos.y <= (rec.first.y + rec.second.heigth)))
            return true;
        return false;
    }
};
