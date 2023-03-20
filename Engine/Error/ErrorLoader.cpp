/*
** EPITECH PROJECT, 2022
** Project R-TYPE
** File description:
** Error class for DILoader
*/

#include "ErrorLoader.hpp"

ErrorLoader::ErrorLoader(std::string const &msg)
{
    this->_error_msg = msg;
    this->_error = ErrorType::CUSTOM;
}

ErrorLoader::ErrorLoader(ErrorType const &type)
{
    this->_error = type;
}

/**
 * @brief 
 * Error Class for the Loader for unexpected errors and return the error's message
 * 
 * @return const char* 
 */
const char *ErrorLoader::what() const noexcept
{
    if (this->_error == ErrorType::CUSTOM)
        return this->_error_msg.c_str();
    if (this->_error == ErrorType::SYM_FAIL)
        return "Sym failed";
    return "Unknow error";
}

/**
 * @brief 
 * Construct a new Error Read File:: Error Read File object
 * Send a specific Error message
 * 
 * @param msg 
 */
ErrorReadFile::ErrorReadFile(std::string const &msg)
{
    this->_errorMsg = msg;
}

/**
 * @brief 
 * Error Class for the Read File for unexpected errors and return the error's message
 * 
 * @return const char* 
 */
const char *ErrorReadFile::what() const noexcept
{
    return this->_errorMsg.c_str();
}
