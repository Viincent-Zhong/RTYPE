/*
** EPITECH PROJECT, 2022
** Project R-TYPE
** File description:
** ClassLoader.cpp
*/

#include "ClassLoader.hpp"

/**
 * @brief 
 * Get a new Element
 * 
 * @return std::unique_ptr<PadaEngine::IElement> 
 */
std::unique_ptr<PadaEngine::IElement> ClassGetter::getElementClass()
{
    return std::unique_ptr<PadaEngine::IElement>(new Element);
}

/**
 * @brief 
 * Get a new Grapchical 
 * 
 * @return std::unique_ptr<PadaEngine::IGraphical> 
 */
std::unique_ptr<PadaEngine::IGraphical> ClassGetter::getGraphicalClass()
{
    return std::unique_ptr<PadaEngine::IGraphical>(new Lib);
}

/**
 * @brief 
 * Get a new Interaction
 * 
 * @return std::unique_ptr<PadaEngine::Iinteraction> 
 */
std::unique_ptr<PadaEngine::Iinteraction> ClassGetter::getInteractionClass()
{
    return std::unique_ptr<PadaEngine::Iinteraction>(new Interaction);
}

/**
 * @brief 
 * Get a new Sound (sound, music)
 * 
 * @return std::unique_ptr<PadaEngine::ISoundGame> 
 */
std::unique_ptr<PadaEngine::ISoundGame> ClassGetter::getSoundClass()
{
    return std::unique_ptr<PadaEngine::ISoundGame>(new SoundGame);
}

/**
 * @brief 
 * Get new Text
 * 
 * @return std::unique_ptr<PadaEngine::IText> 
 */
std::unique_ptr<PadaEngine::IText> ClassGetter::getTextClass()
{
    return std::unique_ptr<PadaEngine::IText>(new Text);
}
