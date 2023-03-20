/*
** EPITECH PROJECT, 2022
** Project R-TYPE
** File description:
** DataTransfer.cpp
*/

#include "DataTransfer.hpp"

/**
 * @brief 
 * Convert a string to Hexadecimal notation for sending a structure
 * 
 * @param op 
 * @param data 
 * @param size 
 */
void EngineNetwork::DataTransfer::convert_to_hex_string(std::ostringstream &op, const unsigned char* data, int size)
{
    std::ostream::fmtflags old_flags = op.flags();
    char old_fill  = op.fill();
    op << std::hex << std::setfill('0');
    for (int i = 0; i < size; i++) {
        if (i>0)
            op << ' ';
        op << "0x" << std::setw(2) << static_cast<int>(data[i]);
    }
    op.flags(old_flags);
    op.fill(old_fill);
}

/**
 * @brief 
 * Convert a Hexadecimal notation into a string to receive a structure
 * 
 * @param ip 
 * @param data 
 * @param size 
 */
void EngineNetwork::DataTransfer::convert_to_struct(std::istream& ip, unsigned char* data, int size)
{
    std::string line;
    getline(ip, line);
    std::istringstream ip_convert(line);
    ip_convert >> std::hex;
    unsigned int u = 0;
    int i = 0;
    while ((ip_convert >> u) && (i < size))
        if((0x00 <= u) && (0xff >= u))
            data[i++] = static_cast<unsigned char>(u);
}
