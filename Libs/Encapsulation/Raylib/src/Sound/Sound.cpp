/*
** EPITECH PROJECT, 2022
** Project R-TYPE
** File description:
** Sound.cpp
*/

#include "Sound.hpp"

SoundGame::SoundGame() : _initEffect(false), _initMusic(false), _isPlaying(false)
{
}

SoundGame::~SoundGame()
{
    if (_initMusic)
        UnloadMusicStream(_music);
    if (_initEffect)
        UnloadSound(_effect);
}

/**
 * @brief 
 * Initialize the Music
 * 
 * @param path 
 * @param volume 
 */
void SoundGame::initMusic(std::string const &path, const float volume)
{
    _music = LoadMusicStream(path.c_str());
    _music.looping = false;
    _initMusic = true;
    // SetMusicVolume(_music, volume);
    PlayMusicStream(_music);
    _isPlaying = true;
}

/**
 * @brief 
 * Stop the music
 * 
 */
void SoundGame::stopMusic()
{
    StopMusicStream(_music);
}

/**
 * @brief 
 * Pause the music
 * 
 */
void SoundGame::pauseMusic()
{
    PauseMusicStream(_music);
}

/**
 * @brief 
 * Resume the music that is stopped
 * 
 */
void SoundGame::resumeMusic()
{
    ResumeMusicStream(_music);
}

/**
 * @brief 
 * Set a certain Pitch to a music
 * 
 * @param pitch 
 */
void SoundGame::setMusicPitch(const float pitch)
{
    SetMusicPitch(_music, pitch);
}

/**
 * @brief 
 * Set a certain Volume to a music
 * 
 * @param volume 
 */
void SoundGame::setMusicVolume(const float volume)
{
    SetMusicVolume(_music, volume);
}

/**
 * @brief 
 * Update the Music Stream
 * 
 */
void SoundGame::updateMusicStream()
{
    if (!IsMusicStreamPlaying(_music)) {
        PlayMusicStream(_music);
        _isPlaying = true;
    }
    UpdateMusicStream(_music);
}

/**
 * @brief 
 * Check if the Music is playing
 * 
 * @return true 
 * @return false 
 */
bool SoundGame::isPlaying() const
{
    return _isPlaying;
}

/**
 * @brief 
 * Create a Sound Effect
 * 
 * @param path 
 */
void SoundGame::createEffect(std::string const &path)
{
    _initEffect = true;
    _effect = LoadSound(path.c_str());
}

/**
 * @brief 
 * Play the Sound Effect
 * 
 */
void SoundGame::playEffect() const
{
    PlaySound(_effect);
}

/**
 * @brief 
 * Set the Volume of a Sound Effect
 * 
 * @param pitch 
 */
void SoundGame::updateEffectVolume(int pitch)
{
    SetSoundVolume(_effect, pitch);
}
