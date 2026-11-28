#pragma once
#include <string>

#include "Component.h"
#include "../../Interfaces/ISerializable.h"

struct NameComponent: Component, ISerializable
{
    
public:
    NameComponent(): NameComponent("placeholder") { }
    NameComponent(std::string name);
    
public:
    std::string name;
    
    std::string FetchSaveInfo() override;
};
