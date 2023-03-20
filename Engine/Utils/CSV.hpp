/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** CSV
*/

#pragma once

#include <string>
#include <vector>
#include "ErrorLoader.hpp"

namespace EngineUtils {
    namespace CSV {
        /**
         * @brief Throw an ErrorReadFile error in case it fails
         */
        std::vector<std::vector<std::string>> readCSV(std::string const &filepath);
    };
};

