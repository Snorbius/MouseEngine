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
    bool HasComponent(Entity entity);
    
    template <typename T>
    T& AddComponent(Entity entity);
    
    template <typename T>
    T& AddComponent(Entity entity, T component);
    
    template <typename T>
    bool TryGetComponent(Entity entity, T& component);
    
    template <typename T>
    T& GetComponent(Entity entity);
    
    template <typename T>
    void RemoveComponent(Entity entity);
    
    template <typename T, typename... Types>
    std::vector<Entity> FilterEntities(std::vector<Entity> entities);
};

template <typename T>
ComponentContainer<T>* ComponentManager::GetContainer()
{
    if (!containerStorage.contains(typeid(T).name()))
        containerStorage[typeid(T).name()] = new ComponentContainer<T>();
    
    return static_cast<ComponentContainer<T>*>(containerStorage[typeid(T).name()]);
}

template <typename T>
bool ComponentManager::HasComponent(Entity entity)
{
    return GetContainer<T>()->HasComponent(entity);
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
bool ComponentManager::TryGetComponent(Entity entity, T& component)
{
    ComponentContainer<T>* container = GetContainer<T>();
    
    return container->TryGetComponent(entity, component);
}

template <typename T>
T& ComponentManager::GetComponent(Entity entity)
{
    return GetContainer<T>()->GetComponent(entity);
}

template <typename T>
void ComponentManager::RemoveComponent(Entity entity)
{
    ComponentContainer<T>* container = GetContainer<T>();
    
    container->RemoveComponent(entity);
}

template <typename T, typename ... Types>
std::vector<Entity> ComponentManager::FilterEntities(std::vector<Entity> entities)
{
    ComponentContainer<T>* container = GetContainer<T>();
    std::vector<Entity> filtered = container->FilterEntities(entities);
    
    if constexpr (sizeof...(Types) > 0)
        return FilterEntities<Types...>(filtered);
        
    return filtered;
}
