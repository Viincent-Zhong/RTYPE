/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** TextCache
*/

#pragma once

#include <memory>
#include <unordered_map>
#include "IText.hpp"

namespace Engine {
    class TextCache {
        public:
            TextCache() {};
            ~TextCache() {};

            /**
             * @brief 
             * Put Text in cache to avoid creating again and draw it
             * @tparam T 
             * @param font 
             * @param text 
             * @param textSize 
             * @param textPos 
             * @param spacing 
             * @param color 
             */
            template <typename T>
            void drawText(std::string const &font, std::string const &text, float textSize, std::pair<float, float> textPos, float spacing, PadaEngine::EngineColor color)
            {
                auto fontIndex = _textList.find(font);

                if (fontIndex == _textList.end()) {
                    auto newFontIndex = _textList.insert({font, std::unique_ptr<T>(new T)});
                    newFontIndex.first->second.get()->loadFont(font);
                    newFontIndex.first->second.get()->drawText(text, textSize, textPos, spacing, color);
                } else
                    fontIndex->second.get()->drawText(text, textSize, textPos, spacing, color);
            }

        private:
            std::unordered_map<std::string, std::unique_ptr<PadaEngine::IText>> _textList;
    };
};