/*
** EPITECH PROJECT, 2022
** Project R-TYPE
** File description:
** Raylib.cpp
*/

#include "raylib.h"
#include "Lib.hpp"

Lib::Lib() : _windowName("Pada Engine"), _initMusic(false)
{
    SetExitKey(KEY_NULL); // Disable exit key
    setScreenWidth(1920);
    setScreenHeight(1080);
    setFps(60);
}

Lib::Lib(unsigned int width, unsigned int height, unsigned int fps, std::string const &windowName) : _windowName(windowName), _initMusic(false)
{
    SetExitKey(KEY_NULL); // Disable exit key
    setScreenWidth(width);
    setScreenHeight(height);
    setFps(fps);
}

Lib::~Lib()
{
}

void Lib::closeWindow()
{
    CloseWindow();
}

void Lib::closeAudio()
{
    CloseAudioDevice();
}

/**
 * @brief 
 * Open the Window
 * 
 */
void Lib::openWindow()
{
    InitWindow(_width, _height, _windowName.c_str());
    SetTargetFPS(_fps);
    _openWindow = true;
}

/**
 * @brief 
 * Open the window with a certain height, width, fps
 * 
 * @param width 
 * @param height 
 * @param fps 
 * @param windowName 
 * @param flags 
 */
void Lib::openWindow(unsigned int width, unsigned int height, unsigned int fps, std::string const &windowName, unsigned int flags)
{
    setScreenWidth(width);
    setScreenHeight(height);
    _windowName = windowName;
    setConfigurationFlags(flags);
    InitWindow(_width, _height, _windowName.c_str());
    setFps(fps);
    _openWindow = true;
}

bool Lib::isWindowReady()
{
    return IsWindowReady();
}

bool Lib::isAudioReady()
{
    return IsAudioDeviceReady();
}

/**
 * @brief 
 * Set the FPS of a Window
 * 
 * @param fps 
 */
void Lib::setFps(unsigned int fps)
{
    _fps = fps;
    if (_fps > _maxFps)
        _fps = _maxFps;
    SetTargetFPS(fps);
}

/**
 * @brief 
 * Get the FPS of a Window
 * 
 * @return unsigned int 
 */
unsigned int Lib::getFps() const
{
    return _fps;
}

/**
 * @brief 
 * Clear all the sprite in the Window
 * 
 * @param color 
 */
void Lib::clearWindow(int color)
{
    ClearBackground(WHITE);
}

/**
 * @brief 
 * Check if the window is closed
 * 
 * @return true 
 * @return false 
 */
bool Lib::hasCloseWindow()
{
    return WindowShouldClose();
}

/**
 * @brief 
 * Set the Screen Width of the Window
 * 
 * @param width 
 */
void Lib::setScreenWidth(unsigned int width)
{
    _width = width;
    if (_width > 1920)
        _width = 1920;
}

/**
 * @brief 
 * Set the Screen Height of the Window
 * 
 * @param height 
 */
void Lib::setScreenHeight(unsigned int height)
{
    _height = height;
    if (_height > 1080)
        _height = 1080;
}

/**
 * @brief 
 * Start Drawing 
 * 
 */
void Lib::startDrawing()
{
    BeginDrawing();
}

/**
 * @brief 
 * End Drawing
 * 
 */
void Lib::endDrawing()
{
    EndDrawing();
}

/**
 * @brief 
 * Set the Configuration Flags
 * 
 * @param flags 
 */
void Lib::setConfigurationFlags(unsigned int flags)
{
    SetConfigFlags(flags);
}

/**
 * @brief 
 * Initialize the Music
 * 
 */
void Lib::initMusic()
{
    InitAudioDevice();
    if (!_initMusic) {
        _initMusic = true;
    }
}

/**
 * @brief 
 * Get the window Size
 * 
 * @return std::pair<unsigned int, unsigned int> 
 */
std::pair<unsigned int, unsigned int> Lib::getWindowSize()
{
    return {_width, _height};
}

/**
 * @brief 
 * Get the DeltaTime
 * 
 * @return float 
 */
float Lib::getDeltaTime()
{
    return GetFrameTime();
}