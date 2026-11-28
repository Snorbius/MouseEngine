#include "NameComponent.h"

NameComponent::NameComponent(std::string name)
{
    this->name = name;
}

std::string NameComponent::FetchSaveInfo()
{
    return name;
}
