/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Drawable
*/

#pragma once

#include <utility>
#include <vector>
#include <array>
#include "IElement.hpp"

namespace EngineComponent {
    struct Position {
        PadaEngine::Position pos;
        bool isOutOfBoundable;
    };

    struct Drawable {
        bool isDrawable;
        std::string texture;
    };

    struct SpriteSheet {
        bool isAnimated;
        PadaEngine::Rectangle rec;
        float xFrameSpeed;
        float yFrameSpeed;
        float xStartPoint;
        float yStartPoint;
        float frameMax;
    };

    struct Layer {
        std::size_t layer;
    };

    struct Mouseover {
        bool hasMouseOver;
    };

    struct WalkAnimation {
        std::vector<PadaEngine::Position> directionsAnimation; // 0 origin 1 left 2 right 3 up 4 down
    };
    struct Slide {
        bool isSlidable;
    };
    struct FunctionName {
        std::string name;
    };
    struct SoundEffect {
        std::string sound;
        int volume;
    };
    struct EffectName {
        std::string name;
    };
    // struct ContentText {
    //     std::string content;
    // }
    struct ListGame {
        unsigned int id;
        unsigned int nbPlayers;
    };

    struct RoomPlayer {
        std::array<char, 20> playerName;
        unsigned int playerID;
        unsigned int roomID;
    };

    struct FontName {
        std::string name;
    };
    
}
