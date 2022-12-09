#pragma once

#include "ISerializer.hpp"

class Serializer : public ISerializer
{

public:

    void save() override;
    void load() override;
};
