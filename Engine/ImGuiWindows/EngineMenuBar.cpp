#include "EngineMenuBar.h"

#include <filesystem>
#include <fstream>

#include "EngineUI.h"
#include "imgui.h"
#include "../MouseEngineContext.h"

EngineMenuBar::EngineMenuBar(EngineUI* root)
{
    this->root = root;
    
    FetchAvailableScenes();
}

void EngineMenuBar::FetchAvailableScenes()
{
    const std::filesystem::path sceneDirectory("Engine/Content/Scenes");

    for (auto const& entry : std::filesystem::directory_iterator(sceneDirectory))
    {
        std::fstream file(entry.path());
            
        if (!file.is_open())
            continue;
        
        std::string line;
        std::string sceneName = entry.path().string();
        while (std::getline(file, line))
        {
            if (line.starts_with("sceneName"))
            {
                size_t index = line.find(':');
                sceneName = line.substr(index + 1);
            }
        }
        
        availableScenes.push_back({sceneName, entry.path().string()});
        
        file.close();
    }
}

void EngineMenuBar::Draw()
{
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("Window"))
        {
            ImGui::MenuItem("Material", nullptr, &root->showMaterialWindow);
            
            ImGui::EndMenu();
        }
        
        if (ImGui::BeginMenu("Players"))
        {
            if (ImGui::BeginMenu("Amount"))
            {
                if (ImGui::SliderInt("Number of players", &MouseEngineContext::GetInstance()->numPlayers, 1, 4))
                {
                    MouseEngineContext::GetInstance()->RefreshPlayerCount();
                }
                
                ImGui::EndMenu();
            }
            
            ImGui::EndMenu();
        }
        
        if (ImGui::BeginMenu("Scene"))
        {
            if (ImGui::BeginMenu("Change Scene"))
            {
                for (std::pair<std::string, std::string>& scene : availableScenes)
                {
                    if (ImGui::MenuItem(scene.first.c_str()))
                    {
                        MouseEngineContext::GetInstance()->LoadScene(scene.second);
                    }
                }
                
                ImGui::EndMenu();
            }
            
            ImGui::EndMenu();
        }
    }
    
    ImGui::EndMainMenuBar();
}
