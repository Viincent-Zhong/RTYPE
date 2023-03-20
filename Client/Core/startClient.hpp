/*
** EPITECH PROJECT, 2022
** Project R-TYPE
** File description:
** startClient.hpp
*/

#ifndef STARTCLIENT_HPP_
#define STARTCLIENT_HPP_

#include <string>

bool startUDPClient(std::string const &host, std::string const &port);
void startTCPClient();

#endif /* !STARTCLIENT_HPP_ */
