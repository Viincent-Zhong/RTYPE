/*
** EPITECH PROJECT, 2022
** Project R-TYPE
** File description:
** ISound.hpp
*/

#pragma once

#include <string>

namespace PadaEngine {
    class ISoundGame {
        public:
            /**
             * @brief Destroy the ISound Game object
             * 
             */
            virtual ~ISoundGame() = default;

            /**
             * @brief load the file
             * 
             * @param path 
             * @param volume 
             */
            virtual void initMusic(std::string const &path, const float volume) = 0;

            /**
             * @brief stop the music
             * 
             */
            virtual void stopMusic() = 0;

            /**
             * @brief make a pause
             * 
             */
            virtual void pauseMusic() = 0;

            /**
             * @brief restart the music after pause
             * 
             */
            virtual void resumeMusic() = 0;

            /**
             * @brief Set the Music Pitch
             * 
             * @param pitch 
             */
            virtual void setMusicPitch(const float pitch) = 0;

            /**
             * @brief Set the Music Volume
             * 
             * @param volume 
             */
            virtual void setMusicVolume(const float volume) = 0;

            /**
             * @brief play the music in the game loop
             * 
             */
            virtual void updateMusicStream() = 0;

            /**
             * @brief look if the music in now playing
             * 
             * @return true 
             * @return false 
             */
            virtual bool isPlaying() const = 0;

            /**
             * @brief Create a Effect object
             * 
             * @param path 
             */
            virtual void createEffect(std::string const &path) = 0;

            /**
             * @brief play little sound (fire, press button...)
             * 
             */
            virtual void playEffect() const = 0;

            /**
             * @brief update effect volume
             * 
             * @param pitch 
             */
            virtual void updateEffectVolume(int pitch) = 0;
    };
}
