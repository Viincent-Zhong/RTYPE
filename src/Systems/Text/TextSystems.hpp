/*
** EPITECH PROJECT, 2022
** B-CPP-500-PAR-5-1-rtype-pierre-alexandre.delgado-arevalo
** File description:
** TextSystem
*/

#pragma once

#include "ISystem.hpp"
#include "Singletons.hpp"

namespace System {
    struct DataText {
        std::string font;
        std::string data;
        float size;
        std::pair<float, float> pos;
        float space;
        PadaEngine::EngineColor color;
    };

    class TextSystem : public EngineSystem::ISystem {
        public:
            TextSystem();
            ~TextSystem() {};
            void run(Registry &r, EngineComponent::Singletons &singletons);
        private:
            std::list<EngineSystem::systemFunc> _textSystems;
    };
}