/*
** EPITECH PROJECT, 2022
** Project R-TYPE
** File description:
** Audio.cpp
*/

#include "Audio.hpp"
#include "ClassLoader.hpp"


PadaEngine::Audio::Audio()
{
    _sound = ClassGetter::getSoundClass();
}

PadaEngine::Audio::~Audio()
{
}

void PadaEngine::Audio::test()
{
}