/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** CSV
*/

#include <fstream>
#include <sstream>
#include <iostream>
#include "CSV.hpp"

namespace EngineUtils {
    namespace CSV {
        /**
         * @brief 
         * Read a CSV file and return all the content parsed 
         * 
         * @param filepath 
         * @return std::vector<std::vector<std::string>> 
         */
        std::vector<std::vector<std::string>> readCSV(std::string const &filepath)
        {
            std::vector<std::vector<std::string>> content;
            std::vector<std::string> row;
            std::string line, data;
            std::fstream file;

            file.open(filepath, std::fstream::in);
            if (!file)
                throw ErrorReadFile("Couldn't open file");
            getline(file, line);
            while (getline(file, line)) {
                row.clear();
                std::stringstream str(line);
                while (getline(str, data, ','))
                    row.push_back(data);
                content.push_back(row);
            }
            return content;
        }
    };
}