#include "NewMeshComponent.h"

#include "../../BaseMesh.h"

std::string NewMeshComponent::FetchSaveInfo()
{
    return std::format("{}, {}",
        mesh->meshPath, material->resourcePath);
}
