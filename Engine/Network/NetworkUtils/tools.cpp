/*
** EPITECH PROJECT, 2022
** Project R-TYPE
** File description:
** tools.cpp
*/

#include <asio.hpp>

/**
 * @brief
 * Get the Free Port object
 * 
 * @return int 
 */
int getFreePort()
{
    struct sockaddr_in sin;
    socklen_t len = sizeof(sin);

    if (getsockname(0, (struct sockaddr *)&sin, &len) == -1)
        return ntohs(sin.sin_port);
    return -1;
}