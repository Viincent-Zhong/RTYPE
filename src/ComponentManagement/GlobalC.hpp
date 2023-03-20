/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** GlobalC
*/

#pragma once

#include "TextureCache.hpp"
#include "EntityCache.hpp"
#include "TextCache.hpp"
#include "Time.hpp"

namespace Component {
    struct DataText {
        std::string font;
        std::string text;
        float textSize;
        std::pair<int, int> textPos;
        float spacing;
        PadaEngine::EngineColor color;
    };

    struct Singletons {
        public:
            std::vector<std::size_t> playersAvailable;
            EngineUtils::Timer oneSecTimer = EngineUtils::Timer(1.0f);
            Engine::TextureCache tCache;
            Engine::TextCache textCache;
            EngineEntity::EntityCache initEntities;
            std::pair<unsigned int, unsigned int> windowSize;
            std::size_t layer;
            unsigned int fps;
            EngineUtils::DeltaTime deltaTime;
            std::size_t id;
            std::pair<float, float> mousePos;
            bool buttonLeftPress;
            std::string launchEffect;
            std::vector<PadaEngine::Position> explosionPos;
            bool waveOver;
            std::vector<std::vector<std::string>> dataWave;
            std::unordered_map<std::string, DataText> texts;
            std::string playerName;
    };
};