/*
** EPITECH PROJECT, 2022
** B-CPP-500-PAR-5-1-rtype-pierre-alexandre.delgado-arevalo
** File description:
** MapGenerator
*/

#include "MapGenerator.hpp"

namespace MapRandom {
    MapGenerator::MapGenerator() : _difficulty(Difficulty::HARD)
    {
    }

    MapGenerator::~MapGenerator()
    {
    }

    /**
     * @brief 
     * Create a randomMap in a CSV file
     * 
     */
    void MapGenerator::createRandomMapCSV()
    {
        std::ofstream file("randomWaves.csv");

        file << "enemyOne,nameOne,enemyTwo,nameTwo,enemyThree,nameThree,enemyFour,nameFour,enemyFive,nameFive" << std::endl;
        // file << "enemyOne,nameOne,enemyTwo,nameTwo,enemyThree,nameThree,enemyFour,nameFour" << std::endl;
        srand(time(NULL));

        switch (_difficulty)
        {
        case Difficulty::EASY:
            EasyDifficulty(file);
            break;
        case Difficulty::NORMAL:
            NormalDifficulty(file);
            break;
        case Difficulty::HARD:
            HardDifficulty(file);
            break;
        default:
            break;
        }
        file.close();
    }

    /**
     * @brief 
     * Create an Easy Map
     * 
     * @param file 
     */
    void MapGenerator::EasyDifficulty(std::ofstream &file)
    {
        size_t waves = rand() % 2 + 5;
        int numberEasyEnemies = 2;
        int numberAdvanceEnemies = 2;
        std::vector<int> numbers = {0, 0, 0, 0};

        for (size_t i = 0; i < waves; ++i) {
            numberEasyEnemies += i + 1;
            numberAdvanceEnemies += i*100/25 < waves ? 0 : i - 2;
            for (size_t x = 0; x < (i*100/25 < waves ? 2 : (i*100/50 < waves ? 3 : 4)); ++x)
                numbers.at(x) = rand() % ((x < 2 ? numberEasyEnemies : numberAdvanceEnemies) - numbers.at(x)) + numbers.at(x);
            
            file << std::to_string(numbers.at(0)) << ',' << nameEnemy.at(rand() % EASY_ENEMY) << ',' <<
                std::to_string(numbers.at(1)) << ',' << nameEnemy.at(rand() % EASY_ENEMY) << ',' <<
                std::to_string(numbers.at(2)) << ',' << nameEnemy.at(rand() % ADVANCE_ENEMY) << ',' <<
                std::to_string(numbers.at(3)) << ',' << nameEnemy.at(rand() % ADVANCE_ENEMY) << ',' <<
                std::to_string((i*100/75 >= waves ? 1 : 0 )) << ',' << nameEnemy.at((rand() % 2) + 5) << std::endl;
        }
    }

    /**
     * @brief 
     * Create a Normal Map
     * 
     * @param file 
     */
    void MapGenerator::NormalDifficulty(std::ofstream &file)
    {
        size_t waves = rand() % 2 + 7;
        int numberEasyEnemies = 4;
        int numberAdvanceEnemies = 2;
        std::vector<int> numbers = {0, 0, 0, 0};

        for (size_t i = 0; i < waves; ++i) {
            numberEasyEnemies += i;
            numberAdvanceEnemies += i*100/25 < waves ? 0 : i - 2;
            for (size_t x = 0; x < (i*100/25 < waves ? 2 : (i*100/50 < waves ? 3 : 4)); ++x)
                numbers.at(x) = rand() % ((x < 2 ? numberEasyEnemies : numberAdvanceEnemies) - numbers.at(x)) + numbers.at(x);
            
            file << std::to_string(numbers.at(0)) << ',' << nameEnemy.at(rand() % EASY_ENEMY) << ',' <<
                std::to_string(numbers.at(1)) << ',' << nameEnemy.at(rand() % EASY_ENEMY) << ',' <<
                std::to_string(numbers.at(2)) << ',' << nameEnemy.at(rand() % ADVANCE_ENEMY) << ',' <<
                std::to_string(numbers.at(3)) << ',' << nameEnemy.at(rand() % ADVANCE_ENEMY) << ',' <<
                std::to_string((i*100/75 >= waves ? 1 : 0 )) << ',' << nameEnemy.at((rand() % 2) + 5) << std::endl;
        }
    }

    /**
     * @brief 
     * Create a Hard Map
     * 
     * @param file 
     */
    void MapGenerator::HardDifficulty(std::ofstream &file)
    {
        size_t waves = rand() % 2 + 9;
        int numberEasyEnemies = 3;
        int numberAdvanceEnemies = 1;
        std::vector<int> numbers = {0, 0, 0, 0};

        for (size_t i = 0; i < waves; ++i) {
            numberEasyEnemies += i + 1;
            numberAdvanceEnemies += i - 1;
            for (size_t x = 0; x < (i*100/25 < waves ? 2 : (i*100/50 < waves ? 3 : 4)); ++x)
                numbers.at(x) = rand() % ((x < 2 ? numberEasyEnemies : numberAdvanceEnemies) - numbers.at(x)) + numbers.at(x);
            
            file << std::to_string(numbers.at(0)) << ',' << nameEnemy.at(rand() % EASY_ENEMY) << ',' <<
                std::to_string(numbers.at(1)) << ',' << nameEnemy.at(rand() % EASY_ENEMY) << ',' <<
                std::to_string(numbers.at(2)) << ',' << nameEnemy.at(rand() % ADVANCE_ENEMY) << ',' <<
                std::to_string(numbers.at(3)) << ',' << nameEnemy.at(rand() % ADVANCE_ENEMY) << ',' <<
                std::to_string((i*100/75 >= waves ? (i*100/90 >= waves ? 2 : 1) : 0 )) << ',' << nameEnemy.at((rand() % 2) + 5) << std::endl;
        }
    }
    /**
     * @brief 
     * change the difficulty of the level temporary
     * 
     * @param nb 
     */
    void MapGenerator::changeDifficultyTemporary(int nb)
    {
        _difficulty = (nb == 1 ? Difficulty::EASY : (nb == 2 ? Difficulty::NORMAL : Difficulty::HARD));
    }
}
