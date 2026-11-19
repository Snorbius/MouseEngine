#pragma once
#include <filesystem>
#include <format>
#include <fstream>
#include <map>
#include <string>

#include "../AssetManager.h"
#include "../LogManager.h"
#include "../MouseEngineContext.h"

class Resource
{
public:
    Resource() = default;
    virtual ~Resource() = default;
    
private:
    
public:
    /**
     * A path to where the resource was loaded from.
     */
    std::string resourcePath = "null";
    
    /**
     * A map containing values for the resource. Used by the underlying resource system.
     */
    std::map<std::string, std::vector<std::string>> values;

    /**
     * Fetches a resource identifier for a specific resource type. This is meant to be overriden for each resource subclass.
     * The identifier should tell you what the resource is, such as "material", "scene", "mesh" or similar.
     * @return The unique resource identifier
     */
    virtual std::string GetResourceIdentifier() { return "BaseResource"; }

    /**
     * Fetches a resources unique file ending. This is meant to be overriden for each resource subclass.
     * @return The file ending for the specific resource.
     */
    virtual std::string GetResourceFileEnding() { return "cheese"; }
    
    /**
     * Virtual function called when a resource has been loaded. Should likely never be called manually.
     * The "values" map has been populated at this point and is meant to be used during initialization.
     */
    virtual void InitializeResource() = 0;
    
    /**
     * Adds a value to the resource. This value will be included in the resource file whenever SaveToFile is called.
     * @param key Key
     * @param value Value
     * @param override Whether to override any existing value
     */
    void AddValue(std::string key, std::string value, bool override = false);

    /**
     * Saves this resource as a file at the given location. All resource files will be appended with 
     * whatever GetResourceFileEnding returns if the path does not already include it.
     * Does not currently support overriding existing files.
     * @param path The path to the file.
     */
    virtual void SaveToFile(std::string path);

    /**
     * Loads a resource from a file. Any values inside the resource will be used to populate the 'values' map.
     * @param filePath The path to the file.
     * @return The newly created resource, or null if the resource could not be loaded.
     */
    template<class T>
    static T* LoadResource(std::string filePath) //inline to make template work
    {
        T* res = static_cast<T*>(MouseEngineContext::GetInstance()->Assets->FetchResource(filePath));
        if (res != nullptr)
            return res;
        
        if (!std::filesystem::exists(filePath))
            print_line(std::format("Could not find specified file: {}", filePath));
        
        res = new T();
        
        res->resourcePath = filePath;
        
        if (!filePath.ends_with("." + res->GetResourceFileEnding()))
        {
            print_warning(std::format("You are trying to load a resource file that does not end with the correct file format ({}) "
                                     "Make sure that this is what you want.", "." + res->GetResourceFileEnding()));
        }
            
        std::fstream file(filePath);
            
        if (!file.is_open())
        {
            print_warning(std::format("Could not open file located at: {}", filePath));
            delete res;
            return nullptr;
        }
        
        std::string line;
        while (std::getline(file, line))
        {
            size_t separator = line.find(':');
            if (separator == std::string::npos)
                continue;
                
            res->AddValue(line.substr(0, separator), line.substr(separator + 1));
        }
            
        res->InitializeResource();
        
        MouseEngineContext::GetInstance()->Assets->RegisterResource(filePath, res);
        
        return res;
    }
};
