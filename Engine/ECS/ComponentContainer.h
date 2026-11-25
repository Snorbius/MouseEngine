#pragma once
#include <format>
#include <unordered_map>
#include <vector>

#include "EntityManager.h"
#include "../LogManager.h"

class BaseComponentContainer{};

template <typename T>
class ComponentContainer: public BaseComponentContainer
{
public:
    std::vector<T> components;
    
    std::unordered_map<Entity, size_t> entityComponentMap;

    std::unordered_map<size_t, Entity> componentEntityMap;
    
    T& AddComponent(Entity entity);
    T& AddComponent(Entity entity, T component);
    T& GetComponent(Entity entity);
    void RemoveComponent(Entity entity);
};

template <typename T>
T& ComponentContainer<T>::AddComponent(Entity entity)
{
    return AddComponent(entity, T());
}

template <typename T>
T& ComponentContainer<T>::AddComponent(Entity entity, T component)
{
    if (entityComponentMap.contains(entity)) // TODO: Remove
    {
        MouseLogs::print_warning(std::format("Trying to add a component {} to entity {}, which already has one.", 
            typeid(T).name(), std::to_string(entity)));
        return components[entityComponentMap[entity]];
    }
    
    components.push_back(component);
    entityComponentMap[entity] = components.size() - 1;
    componentEntityMap[components.size() - 1] = entity;
    return components.back();
}

template <typename T>
T& ComponentContainer<T>::GetComponent(Entity entity)
{
    if (!entityComponentMap.contains(entity)) // TODO: Remove/re make
    {
        MouseLogs::print_warning(std::format("Entity {} does not have component of type \"{}\"",
            std::to_string(entity), typeid(T).name()));
        return components[0];
    }
    
    return components[entityComponentMap[entity]];
}

template <typename T>
void ComponentContainer<T>::RemoveComponent(Entity entity)
{
    if (!entityComponentMap.contains(entity))
        return;
    
    if (components.size() == 1)
    {
        components.clear();
        entityComponentMap.clear();
        componentEntityMap.clear();
        return;
    }
    
    size_t indexToRemove = entityComponentMap[entity];
    
    components[indexToRemove] = components.back();
    components.pop_back();
    
    Entity oldLast = componentEntityMap[components.size()];
    entityComponentMap[oldLast] = indexToRemove;
    entityComponentMap.erase(entity);
    componentEntityMap[indexToRemove] = oldLast;
    componentEntityMap.erase(components.size());
}
