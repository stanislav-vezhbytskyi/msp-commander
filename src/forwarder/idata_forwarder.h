#pragma once
#include "docoded_types.h"


class DataForwarder {
public:
    virtual ~DataForwarder() = default;
    virtual void forward(const DecodedTypes& data);
};
