#include "EngineMenuBar.h"

#include "EngineUI.h"
#include "imgui.h"
#include "../MouseEngineContext.h"

EngineMenuBar::EngineMenuBar(EngineUI* root)
{
    this->root = root;
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
                ImGui::SliderInt("Number of players", &MouseEngineContext::GetInstance()->numPlayers, 1, 4);
                
                ImGui::EndMenu();
            }
            
            ImGui::EndMenu();
        }
    }
    
    ImGui::EndMainMenuBar();
}
