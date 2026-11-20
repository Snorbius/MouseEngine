#pragma once
#include <string>
#include <vector>

class EngineUI;

class EngineMenuBar
{
public:
    EngineMenuBar(EngineUI* root);
    
private:
    EngineUI* root;
    
    std::vector<std::pair<std::string, std::string>> availableScenes;
    
    void FetchAvailableScenes();
    
public:
    void Draw();
};
