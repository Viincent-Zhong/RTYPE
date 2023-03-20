/*
** EPITECH PROJECT, 2022
** Project R-TYPE
** File description:
** IGraphical.hpp
*/

#pragma once

#include <vector>
#include <string>

namespace PadaEngine {
    class IGraphical {
        public:
            /**
             * @brief Destroy the IGraphical object
             * close the window if we open it
             * 
             */
            virtual ~IGraphical() = default;

            /**
             * @brief open the window without changing the params
             * 
             */
            virtual void openWindow() = 0;

            /**
             * @brief check if window has been initialized
             */
            virtual bool isWindowReady() = 0;
            /**
             * @brief open the window with new params
             * 
             * @param width of the window (0 - screen width)
             * @param height of the window (0 - screen height)
             * @param fps of the game (0 - _maxFps)
             * @param windowName 
             */
            virtual void openWindow(unsigned int width, unsigned int height, unsigned int fps, std::string const &windowName, unsigned int flags) = 0;

            /**
             * @brief Set the _fps member
             * 
             * @param fps (0 - _maxFps)
             */
            virtual void setFps(unsigned int fps) = 0;

            /**
             * @brief Get the _fps member
             * 
             * @return unsigned int 
             */
            virtual unsigned int getFps() const = 0;

            /**
             * @brief clear the window with the given color
             * 
             * @param color 
             */
            virtual void clearWindow(int color) = 0;

            /**
             * @brief close the window why pressing escape or press the close button
             * 
             * @return true 
             * @return false 
             */
            virtual bool hasCloseWindow() = 0;

            /**
             * @brief Set the _width member (0 - screen width)
             * if width > screen width, _width = screen width
             * 
             * @param width 
             */
            virtual void setScreenWidth(unsigned int width) = 0;

            /**
             * @brief Set the _height member (0 - screen height)
             * if width > screen height, _height = screen height
             * 
             * @param height 
             */
            virtual void setScreenHeight(unsigned int height) = 0;

            /**
             * @brief function need to be call evrytime we want to print something on the screen (text, image, shape, 3d...)
             * 
             */
            virtual void startDrawing() = 0;

            /**
             * @brief stop drawing
             * 
             */
            virtual void endDrawing() = 0;

            /**
             * @brief Set the Configuration Flags for the window (see FLAGS in raylib.h)
             * 
             * @param flags type
             */
            virtual void setConfigurationFlags(unsigned int flags) = 0;

            /**
             * @brief enable the music to be play
             * 
             */
            virtual void initMusic() = 0;

            /**
             * @brief stop the music
             * 
             */
            virtual void closeAudio() = 0;

            /**
             * @brief get the size of the user screen
             * 
             * @return a pair with width and height
             */
            virtual std::pair<unsigned int, unsigned int> getWindowSize() = 0;

            /**
             * @brief Get the delta time of engine
             * 
             * @return float
             */
            virtual float getDeltaTime() = 0;

            /**
             * @brief check if the audio is initialized
             */
            virtual bool isAudioReady() = 0;
            /**
             * @brief close the window
             */
            virtual void closeWindow() = 0;
    };
}
