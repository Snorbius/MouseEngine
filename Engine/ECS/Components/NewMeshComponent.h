#pragma once

class BaseMesh;

struct NewMeshComponent
{
    NewMeshComponent(): NewMeshComponent(nullptr) {}
    NewMeshComponent(BaseMesh* mesh)
        : mesh(mesh)
    {
    }

    BaseMesh* mesh = nullptr;
};
