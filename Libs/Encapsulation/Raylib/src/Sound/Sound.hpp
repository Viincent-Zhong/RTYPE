/*
** EPITECH PROJECT, 2022
** Project R-TYPE
** File description:
** Sound.hpp
*/

#ifndef SOUND_HPP_
#define SOUND_HPP_

#include "ISound.hpp"
#include "raylib.h"

class SoundGame : public PadaEngine::ISoundGame {
    public:
        SoundGame();
        ~SoundGame();
        void initMusic(std::string const &path, const float volume);
        void stopMusic();
        void pauseMusic();
        void resumeMusic();
        void setMusicPitch(const float pitch);
        void setMusicVolume(const float volume);
        void updateMusicStream();
        bool isPlaying() const;
        void createEffect(std::string const &path);
        void playEffect() const;
        void updateEffectVolume(int pitch);

    private:
        bool _initMusic;
        bool _initEffect;
        bool _isPlaying;
        Music _music;
        Sound _effect;
};

#endif /* !SOUND_HPP_ */