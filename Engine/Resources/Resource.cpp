#include "Resource.h"

#include <filesystem>
#include <fstream>

#include "../LogManager.h"

void Resource::AddValue(std::string key, std::string value, bool override)
{
    if (override && values.contains(key))
        return;
    
    if (!values.contains(key))
        values[key] = {};
    
    values[key].push_back(value);
}

void Resource::SaveToFile(std::string path)
{
    std::string fileEnding = GetResourceFileEnding();
    if (!path.ends_with("." + fileEnding))
        path += "." + fileEnding;

    std::ofstream matFile(path);
    
    if (!matFile.is_open())
    {
        MouseLogs::print_warning(std::format("Could not create file at \"{}\", could not open file.", path));
        matFile.close();
        return;
    }
    
    matFile << GetResourceIdentifier() << "\n";

    for (std::pair<const std::string, std::vector<std::string>>& pair : values)
        for (const std::string& entry : pair.second)
            matFile << std::format("{}:{}", pair.first, entry) << "\n";
    
    matFile.close();
}