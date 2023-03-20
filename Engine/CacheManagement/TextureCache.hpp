/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** TextureCache
*/

#pragma once

#include <memory>
#include <unordered_map>
#include "IElement.hpp"

namespace Engine {
    class TextureCache {
        public:
            TextureCache() {};
            ~TextureCache() {};
            /**
             * @brief 
             * Put Texture in cache to avoid creating again and draw it
             * 
             * @tparam T 
             * @param texture 
             * @param pos 
             */
            template <typename T>
            void drawTexture(std::string const &texture, PadaEngine::Position const &pos)
            {
                auto textureIndex = _texturesList.find(texture);

                if (textureIndex == _texturesList.end()) {
                    auto newTextureIndex = _texturesList.insert({texture, std::unique_ptr<T>(new T)});
                    newTextureIndex.first->second.get()->createObject(texture);
                    newTextureIndex.first->second.get()->draw(pos);
                } else
                    textureIndex->second.get()->draw(pos);
            }

            /**
             * @brief 
             * Put Texture with a specific rectangle in cache to avoid creating again and draw it
             * 
             * @tparam T 
             * @param texture 
             * @param pos 
             * @param rec 
             */
            template <typename T>
            void drawTextureRec(std::string const &texture, PadaEngine::Position const &pos, PadaEngine::Rectangle const &rec)
                {
                    auto textureIndex = _texturesList.find(texture);

                    if (textureIndex == _texturesList.end()) {
                        auto newTextureIndex = _texturesList.insert({texture, std::unique_ptr<T>(new T)});
                        newTextureIndex.first->second.get()->createObject(texture);
                        newTextureIndex.first->second.get()->drawRec(pos, rec);
                    } else {
                        textureIndex->second.get()->drawRec(pos, rec);
                    }
                };
        private:
            std::unordered_map<std::string, std::unique_ptr<PadaEngine::IElement>> _texturesList;
    };
};