#include "ComponentSystem.h"

ComponentSystem::~ComponentSystem()
{
    for (const std::pair<const unsigned long long, BaseComponentContainer*>& storage : containerStorage)
        delete storage.second;
}
