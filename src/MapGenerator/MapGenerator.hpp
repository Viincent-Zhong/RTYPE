/*
** EPITECH PROJECT, 2022
** B-CPP-500-PAR-5-1-rtype-pierre-alexandre.delgado-arevalo
** File description:
** MapGenerator
*/

#pragma once

#include <iostream>
#include <fstream>
#include <list>
#include <vector>

static std::vector<std::string> nameEnemy = {"basicEnemy", "fastEnemy", "hazeEnemy", "advanceEnemy", "robotEnemy", "specialEnemy", "specialEnemyUpsideDown"};

#define EASY_ENEMY 3
#define ADVANCE_ENEMY 5

namespace MapRandom {
    enum Difficulty {
        EASY,
        NORMAL,
        HARD
    };

    // enum Difficulty {
    //     TUTORIAL,
    //     EASY,
    //     NORMAL,
    //     ADVANCE,
    //     HARD,
    //     FURIOUS,
    //     IMPOSSIBLE
    // };

    class MapGenerator {
        public:
            MapGenerator();
            ~MapGenerator();
            void createRandomMapCSV();
            void changeDifficultyTemporary(int ac);
            void EasyDifficulty(std::ofstream &file);
            void NormalDifficulty(std::ofstream &file);
            void HardDifficulty(std::ofstream &file);

        private:
            Difficulty _difficulty;
            int _waves;
    };
}