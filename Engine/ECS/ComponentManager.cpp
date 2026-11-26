#include "ComponentManager.h"

#include "../MouseEngineContext.h"

ComponentManager::~ComponentManager()
{
    for (std::pair<const std::string, BaseComponentContainer*>& storage : containerStorage)
        delete storage.second;
}


