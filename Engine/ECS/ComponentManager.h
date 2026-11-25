#pragma once
#include <string>
#include <unordered_map>

#include "ComponentContainer.h"

class ComponentManager
{
public:
    ComponentManager() = default;
    ~ComponentManager();
    
private:
    std::unordered_map<std::string, BaseComponentContainer*> containerStorage;
    
public:
    template <typename T>
    ComponentContainer<T>* GetContainer();
    
    template <typename T>
    T& AddComponent(Entity entity);
    
    template <typename T>
    T& AddComponent(Entity entity, T component);
    
    template <typename T>
    T* GetComponent(Entity entity);
    
    template <typename T>
    void RemoveComponent(Entity entity);
};

template <typename T>
ComponentContainer<T>* ComponentManager::GetContainer()
{
    if (!containerStorage.contains(typeid(T).name()))
        containerStorage[typeid(T).name()] = new ComponentContainer<T>();

    return static_cast<ComponentContainer<T>*>(containerStorage[typeid(T).name()]);
}

template <typename T>
T& ComponentManager::AddComponent(Entity entity)
{
    ComponentContainer<T>* container = GetContainer<T>();
    
    return container->AddComponent(entity);
}

template <typename T>
T& ComponentManager::AddComponent(Entity entity, T component)
{
    ComponentContainer<T>* container = GetContainer<T>();
    
    return container->AddComponent(entity, component);
}

template <typename T>
T* ComponentManager::GetComponent(Entity entity) // TODO: Should probably return std::optional, in case the entity has no such component
{
    ComponentContainer<T>* container = GetContainer<T>();
    
    return container->GetComponent(entity);
}

template <typename T>
void ComponentManager::RemoveComponent(Entity entity)
{
    ComponentContainer<T>* container = GetContainer<T>();
    
    container->RemoveComponent(entity);
}
