#pragma once
#include "../../Resources/Material.h"

class BaseMesh;

struct NewMeshComponent
{
    NewMeshComponent(): NewMeshComponent(nullptr, nullptr) {}
    NewMeshComponent(BaseMesh* mesh, Material* material = nullptr)
        : mesh(mesh), material(material)
    {
        if (this->material == nullptr)
            this->material = Material::GetFallbackMaterial();
    }

    BaseMesh* mesh = nullptr;
    Material* material = nullptr;
};
