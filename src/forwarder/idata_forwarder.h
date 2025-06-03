#pragma once
#include "docoded_types.h"


class IDataForwarder {
public:
    virtual ~IDataForwarder() = default;
    virtual void forward(const DecodedTypes& data) = 0;
};
