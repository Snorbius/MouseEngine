#include "EngineMenuBar.h"

#include "EngineUI.h"
#include "imgui.h"

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
    }
    
    ImGui::EndMainMenuBar();
}
