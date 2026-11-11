#pragma once

#define PATH_BUFFER_SIZE 256
#define ENGINE_MATERIAL_PATH R"(Engine/Content/Materials)"
#include "imgui.h"

class MaterialCreator
{
public:
    MaterialCreator();
    
private:
    ImGuiWindowFlags windowFlags = 0;
    
    char materialName[PATH_BUFFER_SIZE] = "Placeholder";
    char vertexPath[PATH_BUFFER_SIZE] = {};
    char fragmentPath[PATH_BUFFER_SIZE] = {};
    
    char texturePath1[PATH_BUFFER_SIZE] = {};
    
    void CreateMaterial();
    
public:
    void DrawWindow();
};
