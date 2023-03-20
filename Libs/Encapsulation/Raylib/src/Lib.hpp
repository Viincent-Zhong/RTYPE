/*
** EPITECH PROJECT, 2022
** Project R-TYPE
** File description:
** Lib.hpp
*/

#pragma once

#include "IGraphical.hpp"
#include "raylib.h"

class Lib : public PadaEngine::IGraphical {
    public:
        Lib();
        Lib(unsigned int width, unsigned int height, unsigned int fps, std::string const &windowName);
        ~Lib();
        void openWindow();
        void openWindow(unsigned int width, unsigned int height, unsigned int fps, std::string const &windowName, unsigned int flags);
        bool isWindowReady();
        bool isAudioReady();
        void setFps(unsigned int fps);
        unsigned int getFps() const;
        void clearWindow(int color);
        bool hasCloseWindow();
        void setScreenWidth(unsigned int width);
        void setScreenHeight(unsigned int height);
        void startDrawing();
        void endDrawing();
        void start3dDrawing();
        void end3dDrawing();
        void setConfigurationFlags(unsigned int flags);
        void initMusic();
        std::pair<unsigned int, unsigned int> getWindowSize();
        float getDeltaTime();
        void closeWindow();
        void closeAudio();

    private:
        unsigned int _width;
        unsigned int _height;
        unsigned int _fps;
        const unsigned int _maxFps = 200;
        bool _openWindow;
        std::string _windowName;
        bool _initMusic;
};
