#pragma once
#include <map>

class Entity
{
private:
    std::multimap<size_t, unsigned int> componentMap;
    friend class ComponentSystem;
    
public:
    
};
