/*
** EPITECH PROJECT, 2022
** R-TYPE
** File description:
** main.cpp
*/

#include "startServer.hpp"

/**
 * @brief 
 * Start the TCP Server, Server-side
 * 
 * @param ac 
 * @param av 
 * @return int 
 */
int main(int ac, char **av)
{
    if (startTCPServer())
        return 84;
    return 0;
}
