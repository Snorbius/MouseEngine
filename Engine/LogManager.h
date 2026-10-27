#pragma once

#define DEBUG_ENABLED true
#include <string>

namespace MouseLogs
{
    enum DEBUG_TYPE
    {
        DEFAULT_DEBUG,
    };
    
    void print_line(const std::string& message);
    void print(const std::string& message);
    void print_warning(const std::string& message);
    void print_error(const std::string& message);
    void print_debug(const std::string& message, DEBUG_TYPE type = DEFAULT_DEBUG);
    void print_debug_line(const std::string& message, DEBUG_TYPE type = DEFAULT_DEBUG);

    class LogManager
    {
    public:
        
    };
}

