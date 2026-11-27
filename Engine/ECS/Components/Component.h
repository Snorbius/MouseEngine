#pragma once
#include <optional>

#include "../ComponentManager.h"
#include "../EntityManager.h"
#include "../../MouseEngineContext.h"

class MouseEngineContext;

struct Component
{
protected:
    MouseEngineContext* EngineContext = MouseEngineContext::GetInstance();
    
    /**
     * Helper function to fetch a component of specified type that belongs to the same entity as this component.
     * @tparam T Type of the component you want to fetch.
     * @return An optional, containing the component, if found.
     */
    template <typename T> 
    bool TryGetSiblingComponent(T& component) const;
    
public:
    Entity owningEntity = 0;
};

template <typename T>
bool Component::TryGetSiblingComponent(T& component) const
{
    return EngineContext->Components->TryGetComponent<T>(owningEntity, component);
}
