#pragma once
#include "../docoded_types.h"


class DataForwarder {
public:
     ~DataForwarder() = default;
     void forward(const DecodedTypes& data);
};
