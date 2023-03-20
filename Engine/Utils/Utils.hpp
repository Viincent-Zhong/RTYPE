/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Utils
*/

#pragma once

#include "IElement.hpp"

namespace EngineUtils {
    bool collisionBetweenRec(std::pair<PadaEngine::Position, PadaEngine::Rectangle> const &rec1, std::pair<PadaEngine::Position, PadaEngine::Rectangle> const &rec2);
    bool collisionPosWithRec(PadaEngine::Position const &pos, std::pair<PadaEngine::Position, PadaEngine::Rectangle> const &rec);
};