#pragma once
#include <string>

class ISerializable
{
public:
    virtual std::string FetchSaveInfo() = 0;
};
