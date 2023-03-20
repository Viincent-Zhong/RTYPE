/*
** EPITECH PROJECT, 2022
** Project R-TYPE
** File description:
** Interaction.hpp
*/

#pragma once

#include "Iinteraction.hpp"

class Interaction : public PadaEngine::Iinteraction {
    public:
        EngineComponent::KEY_VALUE getPressedKey();
        bool isKeyDowned(EngineComponent::KEY_VALUE key);
        bool isKeyPressed(EngineComponent::KEY_VALUE key);
        bool keyIsNotPress(EngineComponent::KEY_VALUE key);
        bool isKeyReleased(EngineComponent::KEY_VALUE key);
        bool mouseLeftIsPress();
        bool mouseLeftIsRelease();
        bool mouseRightIsPress();
        bool mouseRightIsRelease();
        std::pair<float, float> getMousePosition();
        unsigned int engineToKey(EngineComponent::KEY_VALUE key);
        EngineComponent::KEY_VALUE keyToEngine(unsigned int key);

    private:
        static const unsigned int _mouseLeft = 0;
        static const unsigned int _mouseRight = 1;
};
