#include "LogManager.h"

#include <iostream>

namespace MouseLogs
{
    void print_line(const std::string& message)
    {
        std::cout << message << '\n';
    }

    void print(const std::string& message)
    {
        std::cout << message;
    }

    void print_warning(const std::string& message)
    {
        std::cout << "WARNING: " + message << '\n';
    }

    void print_error(const std::string& message)
    {
        std::cout << "ERROR: " + message << '\n';
    }

    void print_debug(const std::string& message, DEBUG_TYPE type)
    {
        std::cout << "DEBUG: " + message;
    }
    
    void print_debug_line(const std::string& message, DEBUG_TYPE type)
    {
        std::cout << "DEBUG: " + message << '\n';
    }
}
