#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <string>

class Logger
{
public:
    static const Logger& log(){
        static Logger logger;
        return logger;
    }
    void info( std::string i)const{
        std::cout << i << std::endl;
    }

    void error( std::string i)const{
        std::cerr << i << std::endl;

    }
    void criticalError(const std::string i)const{
        error(i);
        throw std::exception();
    }
};

#endif // LOGGER_H
