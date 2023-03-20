/*
** EPITECH PROJECT, 2022
** Project R-TYPE
** File description:
** Error class for DILoader
*/

#ifndef ERRORLOADER_HPP_
#define ERRORLOADER_HPP_

#include <functional>
#include <string>

class ErrorLoader : public std::exception {
    public:
        enum ErrorType {
            CUSTOM,
            SYM_FAIL
        };
        ErrorLoader() {};
        ErrorLoader(std::string const &msg);
        ErrorLoader(ErrorType const &type);
        ~ErrorLoader() {};

        const char *what() const noexcept override;
    private:
        ErrorType _error;
        std::string _error_msg;
};

class ErrorReadFile : public std::exception {
    public:
        ErrorReadFile() {};
        ErrorReadFile(std::string const &msg);
        ~ErrorReadFile() {};

        const char *what() const noexcept override;
        private:
            std::string _errorMsg;
};

class ErrorJSON : public std::exception {
    public:
        ErrorJSON() {};
        ErrorJSON(std::string const &msg) : _errorMsg(msg) {};
        ~ErrorJSON() {};

        const char *what() const noexcept override {
            return this->_errorMsg.c_str();
        };
    private:
        std::string _errorMsg;
};


class ErrorSerialisation : public std::exception {
    public:
        ErrorSerialisation() {};
        ErrorSerialisation(std::string const &msg) : _errorMsg(msg) {};
        ~ErrorSerialisation() {};

        const char *what() const noexcept override {
            return this->_errorMsg.c_str();
        };
    private:
        std::string _errorMsg;
};

class ErrorSingletons : public std::exception {
    public:
        ErrorSingletons() {};
        ErrorSingletons(std::string const &msg) : _errorMsg(msg) {};
        ~ErrorSingletons() {};

        const char *what() const noexcept override {
            return this->_errorMsg.c_str();
        };
    private:
        std::string _errorMsg;
};

class ErrorConnection : public std::exception {
    public:
        ErrorConnection() {};
        ErrorConnection(std::string const &msg) : _errorMsg(msg) {};
        ~ErrorConnection() {};

        const char *what() const noexcept override {
            return this->_errorMsg.c_str();
        };
    private:
        std::string _errorMsg;
};

class ErrorGame : public std::exception {
    public:
        ErrorGame() {};
        ErrorGame(std::string const &msg) : _errorMsg(msg) {};
        ~ErrorGame() {};

        const char *what() const noexcept override {
            return this->_errorMsg.c_str();
        };
    private:
        std::string _errorMsg;
};

class ErrorNetwork : public std::exception {
    public:
        ErrorNetwork() {};
        ErrorNetwork(std::string const &msg) : _errorMsg(msg) {};
        ~ErrorNetwork() {};

        const char *what() const noexcept override {
            return this->_errorMsg.c_str();
        };
    private:
        std::string _errorMsg;
};

#endif /* !ERRORLOADER_HPP_ */
