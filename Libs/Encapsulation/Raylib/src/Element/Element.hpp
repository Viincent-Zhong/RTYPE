/*
** EPITECH PROJECT, 2022
** Project R-TYPE
** File description:
** Element.hpp
*/

#ifndef ELEMENT_HPP_
#define ELEMENT_HPP_

#include "IElement.hpp"
#include "raylib.h"

class Element : public PadaEngine::IElement {
    public:
        Element();
        Element(std::string const &file);
        ~Element();
        void createObject(std::string const &file) override;
        void draw(PadaEngine::Position const &pos) const override;
        void drawRec(PadaEngine::Position const &pos, PadaEngine::Rectangle const &rec) const override;

    private:
        bool _created;
        Texture2D _texture;
};

#endif /* !ELEMENT_HPP_ */