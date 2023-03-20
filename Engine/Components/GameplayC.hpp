/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Playable
*/

#pragma once

#include "IEntity.hpp"
#include "Time.hpp"

namespace EngineComponent {

    enum KEY_VALUE {
        NOTHING,
        ARROW_LEFT,
        ARROW_RIGHT,
        ARROW_UP,
        ARROW_DOWN,
        SPACE,
        ENTER,
        ESCAP,
        MY_DELETE,
        POINT = '.',
        A = 'a',
        B = 'b',
        C = 'c',
        D = 'd',
        E = 'e',
        F = 'f',
        G = 'g',
        H = 'h',
        I = 'i',
        J = 'j',
        K = 'k',
        L = 'l',
        M = 'm',
        N = 'n',
        O = 'o',
        P = 'p',
        Q = 'q',
        R = 'r',
        S = 's',
        T = 't',
        U = 'u',
        V = 'v',
        W = 'w',
        X = 'x',
        Y = 'y',
        Z = 'z',
        ZERO = '0',
        ONE = '1',
        TWO = '2',
        THREE = '3',
        FOUR = '4',
        FIVE = '5',
        SIX = '6',
        SEVEN = '7',
        EIGHT = '8',
        NINE = '9'
    };

    struct Controllable {
        bool controllable;
    };

    struct Direction {
        float xDirection;
        float yDirection;
    };

    struct HP {
        std::size_t hp;
    };

    struct HitDamage {
        std::size_t dmg;
    };

    struct ProjectileStats {
        std::string normal;
        std::string strong;
    };

    struct Faction {
        unsigned int faction;
    };
    
    struct Bonus {
        bool isBonus;
        std::size_t dmg;
        std::size_t nbr;
    };

    struct Collision {
        bool hasCollided;
        std::size_t lr;
        std::size_t ud;
        // hitbox ??
    };

    struct IP {
        // ip du client
    };

    struct Interactible {
        bool isInteractible;
        // callback 
    };

    struct IA {
        std::size_t type;
    };

    struct AttachedID {
        std::size_t parentID;
    };
}
