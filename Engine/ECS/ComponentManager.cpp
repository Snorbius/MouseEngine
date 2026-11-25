#include "ComponentManager.h"

ComponentManager::~ComponentManager()
{
    for (std::pair<const std::string, BaseComponentContainer*>& storage : containerStorage)
        delete storage.second;
}
