#include "Resource.h"

#include <filesystem>
#include <fstream>

#include "../LogManager.h"

void Resource::AddValue(std::string key, std::string value, bool override)
{
    if (override && values.contains(key))
        return;
    
    values[key] = value;
}

void Resource::SaveToFile(std::string path)
{
    if (!path.ends_with(".cheese"))
        path += ".cheese";

    if (std::filesystem::exists(path))
    {
        MouseLogs::print_warning(std::format("Could not create file at \"{}\", file already exists.", path));
        return;
    }
    
    std::ofstream matFile(path);
    
    if (!matFile.is_open())
    {
        MouseLogs::print_warning(std::format("Could not create file at \"{}\", could not open file.", path));
        matFile.close();
        return;
    }
    
    matFile << GetResourceIdentifier() << "\n";

    for (std::pair<const std::string, std::string>& pair : values)
        matFile << std::format("{}:{}", pair.first, pair.second) << "\n";
    
    matFile.close();
}