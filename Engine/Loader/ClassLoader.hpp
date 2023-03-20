/*
** EPITECH PROJECT, 2022
** Project R-TYPE
** File description:
** ClassGetter.hpp
*/

#ifndef CLASSLOADER_HPP_
#define CLASSLOADER_HPP_

#include <memory>
#include "IElement.hpp"
#include "IGraphical.hpp"
#include "Iinteraction.hpp"
#include "ISound.hpp"
#include "IText.hpp"
#include "Raylib/src/Element/Element.hpp"
#include "Raylib/src/Lib.hpp"
#include "Raylib/src/Interaction/Interaction.hpp"
#include "Raylib/src/Sound/Sound.hpp"
#include "Raylib/src/Text/Text.hpp"

namespace ClassGetter {
    std::unique_ptr<PadaEngine::IElement> getElementClass();
    std::unique_ptr<PadaEngine::IGraphical> getGraphicalClass();
    std::unique_ptr<PadaEngine::Iinteraction> getInteractionClass();
    std::unique_ptr<PadaEngine::ISoundGame> getSoundClass();
    std::unique_ptr<PadaEngine::IText> getTextClass();
}


#endif /* !CLASSLOADER_HPP_ */
