/*
** EPITECH PROJECT, 2022
** B-CPP-500-PAR-5-1-rtype-pierre-alexandre.delgado-arevalo
** File description:
** Text
*/

#include "TextSystems.hpp"
#include "GameplayC.hpp"
#include "DrawC.hpp"
#include "Text/Text.hpp"

namespace System {

    /**
     * @brief 
     * Draw a Text on cache
     * 
     * @param r 
     * @param singletons 
     */
    void drawText(Registry &r, EngineComponent::Singletons &singletons)
    {
        for (auto const &text : singletons.getSingleton<std::unordered_map<std::string, System::DataText>>(0))
            r.textCache.drawText<Text>(text.second.font, text.second.data, text.second.size, text.second.pos, text.second.space, text.second.color);
    }

    TextSystem::TextSystem()
    {
        _textSystems.push_front(&drawText);
    }

    /**
     * @brief 
     * Run the Text System 
     * 
     * @param r 
     * @param singletons 
     */
    void TextSystem::run(Registry &r, EngineComponent::Singletons &singletons)
    {
        for (auto it = _textSystems.begin(); it != _textSystems.end(); ++it)
            (*it)(r, singletons);
    }
}
