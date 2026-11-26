#include "EntityManager.h"

Entity EntityManager::CreateEntity()
{
    Entity entity = currentEntity++;
    existingEntities.push_back(entity);
    
    return entity;
}
