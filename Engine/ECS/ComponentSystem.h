#pragma once
#include <map>
#include <string>
#include <typeinfo>

#include "ComponentContainer.h"
#include "Entity.h"

class Entity;
class Component;

class ComponentSystem
{
public:
    ComponentSystem() = default;
    ~ComponentSystem();
    
public:
    std::map<size_t, BaseComponentContainer*> containerStorage;
    
public:
    template <typename T>
    ComponentContainer<T>* GetContainer();
    
    template <typename T>
    unsigned int AddComponent(Entity* entity);
    
    template <typename T>
    bool HasComponent(Entity* entity);
    
    template <typename T>
    T* GetComponent(Entity* entity);
    
    template <typename T>
    std::vector<Component*> GetComponents(Entity* entity);
};

template <typename T>
ComponentContainer<T>* ComponentSystem::GetContainer()
{
    if (!containerStorage.contains(typeid(T).hash_code()))
    {
        containerStorage[typeid(T).hash_code()] = new ComponentContainer<T>();
    }

    return static_cast<ComponentContainer<T>*>(containerStorage[typeid(T).hash_code()]);
}

template <typename T>
unsigned int ComponentSystem::AddComponent(Entity* entity)
{
    ComponentContainer<T>* container = GetContainer<T>();
    
    unsigned int handle = container->AddComponent();
    
    entity->componentMap.emplace(typeid(T).hash_code(), handle);
    
    return container->AddComponent();
}

template <typename T>
bool ComponentSystem::HasComponent(Entity* entity)
{
    return entity->componentMap.contains(typeid(T).hash_code());
}

template <typename T>
T* ComponentSystem::GetComponent(Entity* entity)
{
    if (entity == nullptr)
        return nullptr;
    
    size_t hash = typeid(T).hash_code();
    auto index = entity->componentMap.find(hash);
    if (index == entity->componentMap.end())
        return nullptr;
    
    ComponentContainer<T>* container = GetContainer<T>();

    return container->GetComponent(index->second);
}

template <typename T>
std::vector<Component*> ComponentSystem::GetComponents(Entity* entity)
{
    if (entity == nullptr)
        return {};
    
    size_t hash = typeid(T).hash_code();
    auto range = entity->componentMap.equal_range(hash);
    
    ComponentContainer<T>* container = GetContainer<T>();
    std::vector<T*> result;
    
    for (auto i = range.first; i != range.second; ++i)
        result.push_back(container->GetComponent(i));
    

    return result;
}
