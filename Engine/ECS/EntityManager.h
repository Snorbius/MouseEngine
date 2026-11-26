#pragma once
#include <vector>

typedef unsigned int Entity;

class EntityManager
{
private:
    Entity currentEntity = 100;
    std::vector<Entity> existingEntities;
    
public:
    Entity CreateEntity();
    std::vector<Entity> GetAllEntities() { return existingEntities; }
};
