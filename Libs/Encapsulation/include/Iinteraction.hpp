/*
** EPITECH PROJECT, 2022
** Project R-TYPE
** File description:
** Iinteraction.hpp
*/

#ifndef IINTERACTION_HPP_
#define IINTERACTION_HPP_

#include <utility>
#include "GameplayC.hpp"

namespace PadaEngine {
    class Iinteraction {
        public:
            /**
             * @brief Destroy the Iinteraction object
             * 
             */
            virtual ~Iinteraction() = default;
            /**
             * @brief get the id of the key pressed
             * 
             * @return key id (in raylib.h at enum KeyBoardKey)
             */
            virtual EngineComponent::KEY_VALUE getPressedKey() = 0;

            virtual bool isKeyDowned(EngineComponent::KEY_VALUE key) = 0;

            /**
             * @brief return true if the given key is press
             * 
             * @param key id (in raylib.h at enum KeyBoardKey)
             * @return true 
             * @return false 
             */
            virtual bool isKeyPressed(EngineComponent::KEY_VALUE key) = 0;

            /**
             * @brief return true if the given key is press
             * 
             * @param key id (in raylib.h at enum KeyBoardKey)
             * @return true 
             * @return false 
             */
            virtual bool keyIsNotPress(EngineComponent::KEY_VALUE key) = 0;

            /**
             * @brief return true if the given key is release
             * 
             * @param key id (in raylib.h at enum KeyBoardKey)
             * @return true 
             * @return false 
             */
            virtual bool isKeyReleased(EngineComponent::KEY_VALUE key) = 0;

            /**
             * @brief return true if the left button of the mouse is press
             * 
             * @return true 
             * @return false 
             */
            virtual bool mouseLeftIsPress() = 0;

            /**
             * @brief return true if the left button of the mouse is release
             * 
             * @return true 
             * @return false 
             */
            virtual bool mouseLeftIsRelease() = 0;

            /**
             * @brief return true if the right button of the mouse is press
             * 
             * @return true 
             * @return false 
             */
            virtual bool mouseRightIsPress() = 0;

            /**
             * @brief return true if the right button of the mouse is release
             * 
             * @return true 
             * @return false 
             */
            virtual bool mouseRightIsRelease() = 0;

            /**
             * @brief Get a pair of int with the position x y of the mouse
             * 
             * @return std::pair<int, int> 
             */
            virtual std::pair<float, float> getMousePosition() = 0;
            /** @brief Translate an engine key to your key
             */
            virtual unsigned int engineToKey(EngineComponent::KEY_VALUE key) = 0;
            /**
             * @brief Traslate your key to an engine key
             */
            virtual EngineComponent::KEY_VALUE keyToEngine(unsigned int key) = 0;
    };
}

#endif /* !IINTERACTION_HPP_ */