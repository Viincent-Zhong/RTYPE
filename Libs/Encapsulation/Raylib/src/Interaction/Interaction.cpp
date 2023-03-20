/*
** EPITECH PROJECT, 2022
** Project R-TYPE
** File description:
** Interaction.cpp
*/

#include "raylib.h"
#include "Interaction.hpp"

/**
 * @brief 
 * Return the key pressed by the player
 * 
 * @return EngineComponent::KEY_VALUE 
 */
EngineComponent::KEY_VALUE Interaction::getPressedKey()
{
    return keyToEngine(GetKeyPressed());
}

/**
 * @brief 
 * Check if a key is downed
 * 
 * @param key 
 * @return true 
 * @return false 
 */
bool Interaction::isKeyDowned(EngineComponent::KEY_VALUE key)
{
    return IsKeyDown(engineToKey(key));
}

/**
 * @brief 
 * Check if a key is pressed
 * 
 * @param key 
 * @return true 
 * @return false 
 */
bool Interaction::isKeyPressed(EngineComponent::KEY_VALUE key)
{
    return IsKeyPressed(engineToKey(key));
}

/**
 * @brief 
 * Check if a key is not pressed
 * 
 * @param key 
 * @return true 
 * @return false 
 */
bool Interaction::keyIsNotPress(EngineComponent::KEY_VALUE key)
{
    return IsKeyUp(engineToKey(key));
}

/**
 * @brief 
 * Check if a key is released
 * 
 * @param key 
 * @return true 
 * @return false 
 */
bool Interaction::isKeyReleased(EngineComponent::KEY_VALUE key)
{
    return IsKeyReleased(engineToKey(key));
}

/**
 * @brief 
 * Check if the mouse Left Click is pressed
 * 
 * @return true 
 * @return false 
 */
bool Interaction::mouseLeftIsPress()
{
    return IsMouseButtonDown(_mouseLeft);
}

/**
 * @brief 
 * Check if the mouse Left Click is released
 * 
 * @return true 
 * @return false 
 */
bool Interaction::mouseLeftIsRelease()
{
    return IsMouseButtonReleased(_mouseLeft);
}

/**
 * @brief 
 * Check if the mouse Right Click is pressed
 * 
 * @return true 
 * @return false 
 */
bool Interaction::mouseRightIsPress()
{
    return IsMouseButtonDown(_mouseRight);
}

/**
 * @brief 
 * Check if the mouse Right Click is released
 * 
 * @return true 
 * @return false 
 */
bool Interaction::mouseRightIsRelease()
{
    return IsMouseButtonReleased(_mouseRight);
}

/**
 * @brief 
 * Get the mouse position
 * 
 * @return std::pair<float, float> 
 */
std::pair<float, float> Interaction::getMousePosition()
{
    const Vector2 mousePos = GetMousePosition();
    const std::pair<float, float> pos = {mousePos.x, mousePos.y};

    return pos;
}

/**
 * @brief 
 * Get a specific Key 
 * 
 * @param key 
 * @return unsigned int 
 */
unsigned int Interaction::engineToKey(EngineComponent::KEY_VALUE key)
{
    switch (key) {
        case EngineComponent::KEY_VALUE::ARROW_LEFT:
            return KEY_LEFT;
        case EngineComponent::KEY_VALUE::ARROW_RIGHT:
            return KEY_RIGHT;
        case EngineComponent::KEY_VALUE::ARROW_UP:
            return KEY_UP;
        case EngineComponent::KEY_VALUE::ARROW_DOWN:
            return KEY_DOWN;
        case EngineComponent::KEY_VALUE::SPACE:
            return KEY_SPACE;
        case EngineComponent::KEY_VALUE::ENTER:
            return KEY_ENTER;
        case EngineComponent::KEY_VALUE::ESCAP:
            return KEY_ESCAPE;
        case EngineComponent::KEY_VALUE::MY_DELETE:
            return KEY_BACKSPACE;
        case EngineComponent::KEY_VALUE::A:
            return KEY_A;
        case EngineComponent::KEY_VALUE::B:
            return KEY_B;
        case EngineComponent::KEY_VALUE::C:
            return KEY_C;
        case EngineComponent::KEY_VALUE::D:
            return KEY_D;
        case EngineComponent::KEY_VALUE::E:
            return KEY_E;
        case EngineComponent::KEY_VALUE::F:
            return KEY_F;
        case EngineComponent::KEY_VALUE::G:
            return KEY_G;
        case EngineComponent::KEY_VALUE::H:
            return KEY_H;
        case EngineComponent::KEY_VALUE::I:
            return KEY_I;
        case EngineComponent::KEY_VALUE::J:
            return KEY_J;
        case EngineComponent::KEY_VALUE::K:
            return KEY_K;
        case EngineComponent::KEY_VALUE::L:
            return KEY_L;
        case EngineComponent::KEY_VALUE::M:
            return KEY_M;
        case EngineComponent::KEY_VALUE::N:
            return KEY_N;
        case EngineComponent::KEY_VALUE::O:
            return KEY_O;
        case EngineComponent::KEY_VALUE::P:
            return KEY_P;
        case EngineComponent::KEY_VALUE::Q:
            return KEY_Q;
        case EngineComponent::KEY_VALUE::R:
            return KEY_R;
        case EngineComponent::KEY_VALUE::S:
            return KEY_S;
        case EngineComponent::KEY_VALUE::T:
            return KEY_T;
        case EngineComponent::KEY_VALUE::U:
            return KEY_U;
        case EngineComponent::KEY_VALUE::V:
            return KEY_V;
        case EngineComponent::KEY_VALUE::W:
            return KEY_W;
        case EngineComponent::KEY_VALUE::X:
            return KEY_X;
        case EngineComponent::KEY_VALUE::Y:
            return KEY_Y;
        case EngineComponent::KEY_VALUE::Z:
            return KEY_Z;
        case EngineComponent::KEY_VALUE::ONE:
            return KEY_ONE;
        case EngineComponent::KEY_VALUE::TWO:
            return KEY_TWO;
        case EngineComponent::KEY_VALUE::THREE:
            return KEY_THREE;
        case EngineComponent::KEY_VALUE::FOUR:
            return KEY_FOUR;
        case EngineComponent::KEY_VALUE::FIVE:
            return KEY_FIVE;
        case EngineComponent::KEY_VALUE::SIX:
            return KEY_SIX;
        case EngineComponent::KEY_VALUE::SEVEN:
            return KEY_SEVEN;
        case EngineComponent::KEY_VALUE::EIGHT:
            return KEY_EIGHT;
        case EngineComponent::KEY_VALUE::NINE:
            return KEY_NINE;
        case EngineComponent::KEY_VALUE::ZERO:
            return KEY_ZERO;
    }
    return 0;
}

/**
 * @brief 
 * Change the key from an understanble key for the Raylib
 * 
 * @param key 
 * @return EngineComponent::KEY_VALUE 
 */
EngineComponent::KEY_VALUE Interaction::keyToEngine(unsigned int key)
{
    switch (key) {
        case KEY_LEFT:
            return EngineComponent::KEY_VALUE::ARROW_LEFT;
        case KEY_RIGHT:
            return EngineComponent::KEY_VALUE::ARROW_RIGHT;
        case KEY_UP:
            return EngineComponent::KEY_VALUE::ARROW_UP;
        case KEY_DOWN:
            return EngineComponent::KEY_VALUE::ARROW_DOWN;
        case KEY_SPACE:
            return EngineComponent::KEY_VALUE::SPACE;
        case KEY_ENTER:
            return EngineComponent::KEY_VALUE::ENTER;
        case KEY_ESCAPE:
            return EngineComponent::KEY_VALUE::ESCAP;
        case KEY_BACKSPACE:
            return EngineComponent::KEY_VALUE::MY_DELETE;
        case KEY_A:
            return EngineComponent::KEY_VALUE::A;
        case KEY_B:
            return EngineComponent::KEY_VALUE::B;
        case KEY_C:
            return EngineComponent::KEY_VALUE::C;
        case KEY_D:
            return EngineComponent::KEY_VALUE::D;
        case KEY_E:
            return EngineComponent::KEY_VALUE::E;
        case KEY_F:
            return EngineComponent::KEY_VALUE::F;
        case KEY_G:
            return EngineComponent::KEY_VALUE::G;
        case KEY_H:
            return EngineComponent::KEY_VALUE::H;
        case KEY_I:
            return EngineComponent::KEY_VALUE::I;
        case KEY_J:
            return EngineComponent::KEY_VALUE::J;
        case KEY_K:
            return EngineComponent::KEY_VALUE::K;
        case KEY_L:
            return EngineComponent::KEY_VALUE::L;
        case KEY_M:
            return EngineComponent::KEY_VALUE::M;
        case KEY_N:
            return EngineComponent::KEY_VALUE::N;
        case KEY_O:
            return EngineComponent::KEY_VALUE::O;
        case KEY_P:
            return EngineComponent::KEY_VALUE::P;
        case KEY_Q:
            return EngineComponent::KEY_VALUE::Q;
        case KEY_R:
            return EngineComponent::KEY_VALUE::R;
        case KEY_S:
            return EngineComponent::KEY_VALUE::S;
        case KEY_T:
            return EngineComponent::KEY_VALUE::T;
        case KEY_U:
            return EngineComponent::KEY_VALUE::U;
        case KEY_V:
            return EngineComponent::KEY_VALUE::V;
        case KEY_W:
            return EngineComponent::KEY_VALUE::W;
        case KEY_X:
            return EngineComponent::KEY_VALUE::X;
        case KEY_Y:
            return EngineComponent::KEY_VALUE::Y;
        case KEY_Z:
            return EngineComponent::KEY_VALUE::Z;
        case KEY_ZERO:
            return EngineComponent::KEY_VALUE::ZERO;
        case KEY_ONE:
            return EngineComponent::KEY_VALUE::ONE;
        case KEY_TWO:
            return EngineComponent::KEY_VALUE::TWO;
        case KEY_THREE:
            return EngineComponent::KEY_VALUE::THREE;
        case KEY_FOUR:
            return EngineComponent::KEY_VALUE::FOUR;
        case KEY_FIVE:
            return EngineComponent::KEY_VALUE::FIVE;
        case KEY_SIX:
            return EngineComponent::KEY_VALUE::SIX;
        case KEY_SEVEN:
            return EngineComponent::KEY_VALUE::SEVEN;
        case KEY_EIGHT:
            return EngineComponent::KEY_VALUE::EIGHT;
        case KEY_NINE:
            return EngineComponent::KEY_VALUE::NINE;
    }
    return EngineComponent::NOTHING;
}