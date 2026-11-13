#include "MaterialCreator.h"

#include <filesystem>

#include "imgui.h"
#include "../LogManager.h"
#include "../Resources/Material.h"

MaterialCreator::MaterialCreator()
{
    // windowFlags |= ImGuiWindowFlags_AlwaysAutoResize;
}

void MaterialCreator::CreateMaterial()
{
    if (strlen(materialName) == 0)
    {
        MouseLogs::print_line("You need to give your material a name.");
        return;
    }
    
    std::string filePath = std::format("{}/{}.cheese", ENGINE_MATERIAL_PATH, materialName);
    MouseLogs::print_debug_line(filePath);
    
    if (std::filesystem::exists(filePath))
    {
        MouseLogs::print_line("A material with that name already exists, please pick a different name.");
        return;
    }
    
    if (!std::filesystem::exists(vertexPath))
    {
        MouseLogs::print_line(std::format("Could not find vertex file, aborting: {}", vertexPath));
        return;
    }
    if (!std::filesystem::exists(fragmentPath))
    {
        MouseLogs::print_line(std::format("Could not find fragment file, aborting: {}", fragmentPath));
        return;
    }
    if (!std::filesystem::exists(texturePath1))
    {
        MouseLogs::print_line(std::format("Could not find texture file, aborting: {}", texturePath1));
        return;
    }
    
    MouseLogs::print_debug_line("Here we goo!!");
    
    Material material;
    material.AddValue("vertexPath", vertexPath);
    material.AddValue("fragmentPath", fragmentPath);
    material.AddValue("texturePath", texturePath1);
    material.SaveToFile(filePath);
}

void MaterialCreator::Draw()
{
    ImGui::SetNextWindowPos({0, 0}, ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize({400, 400}, ImGuiCond_FirstUseEver);
    
    if (!ImGui::Begin("Create Material", nullptr, windowFlags))
    {
        ImGui::End();
        return;
    }

    ImGui::TextWrapped("A material consists of a vertex shader, a fragment shader and a set of textures.");
    ImGui::Separator();
    ImGui::InputText("Material name", materialName, PATH_BUFFER_SIZE);
    ImGui::InputText("Vertex path", vertexPath, PATH_BUFFER_SIZE);
    ImGui::InputText("Fragment path", fragmentPath, PATH_BUFFER_SIZE);
    ImGui::InputText("Texture path", texturePath1, PATH_BUFFER_SIZE);
    ImGui::Separator();
    if (ImGui::Button("Save material"))
        CreateMaterial();
    
    ImGui::End();
}
