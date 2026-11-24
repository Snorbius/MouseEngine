#pragma once
#include <assert.h>
#include <vector>

#include "../LogManager.h"

class BaseComponentContainer{};

template <typename T>
class ComponentContainer: public BaseComponentContainer
{
public:
    std::vector<T> components;
    std::vector<size_t> freeIndices;
    
    unsigned int AddComponent();
    T* GetComponent(unsigned int index);
};

template <typename T>
unsigned int ComponentContainer<T>::AddComponent()
{
    if (!freeIndices.empty())
    {
        unsigned int result = freeIndices[freeIndices.size() - 1];
        freeIndices.pop_back();
        return result;
    }
    
    components.resize(components.size() + 1);
    return components.size();
}

template <typename T>
T* ComponentContainer<T>::GetComponent(unsigned int index)
{
    if (std::ranges::find(freeIndices.begin(), freeIndices.end(), index) == freeIndices.end())
        MouseLogs::print_warning("You're somehow fetching a component whose index should not be in use."
                                 "Something might've gone wrong.");
    
    assert(index < components.size());
    
    return &components[index];
}
