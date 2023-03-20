/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** InputHandling
*/

#include "InputHandlingSystems.hpp"

namespace System {
    InputHandling::InputHandling()
    {
        _inputHandlingSystems.push_front(&controlSystem);
    }

    /**
     * @brief 
     * Run the Text_Input System
     * 
     * @param r 
     * @param singletons 
     */
    void InputHandling::run(Registry &r, Component::Singletons &singletons)
    {
        for (auto it = _inputHandlingSystems.begin(); it != _inputHandlingSystems.end(); ++it)
            (*it)(r, singletons);
    }
};
