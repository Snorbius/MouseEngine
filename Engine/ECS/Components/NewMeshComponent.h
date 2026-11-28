#pragma once
#include "Component.h"
#include "../../Interfaces/ISerializable.h"
#include "../../Resources/Material.h"

class BaseMesh;

struct NewMeshComponent: Component, ISerializable
{
    NewMeshComponent(): NewMeshComponent(nullptr, nullptr) {}
    NewMeshComponent(BaseMesh* mesh, Material* material = nullptr)
        : mesh(mesh), material(material)
    {
        if (this->material == nullptr)
            this->material = Material::GetFallbackMaterial();
    }

    std::string FetchSaveInfo() override;

    BaseMesh* mesh = nullptr;
    Material* material = nullptr;
};
