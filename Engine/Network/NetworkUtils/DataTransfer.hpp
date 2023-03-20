/*
** EPITECH PROJECT, 2022
** Project R-TYPE
** File description:
** DataTransfer.hpp
*/

#ifndef DATATRANSFER_HPP_
#define DATATRANSFER_HPP_

#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>

namespace EngineNetwork {
    class DataTransfer {
        public:
            template<typename T>
            std::string classToString(T const &data)
            {
                std::ostringstream op;
                std::string output;

                convert_to_hex_string(op, reinterpret_cast<const unsigned char*>(&data), sizeof(T));
                output = op.str();
                return output;
            }

            template<typename T>
            T stringToClass(std::string const &str)
            {
                std::istringstream ip(str);
                T data = {0};

                convert_to_struct(ip, reinterpret_cast<unsigned char*>(&data), sizeof(T));
                return data;
            }
        private:
            void convert_to_hex_string(std::ostringstream &op, const unsigned char* data, int size);
            void convert_to_struct(std::istream& ip, unsigned char* data, int size);
    };
}

#endif /* !DATATRANSFER_HPP_ */
