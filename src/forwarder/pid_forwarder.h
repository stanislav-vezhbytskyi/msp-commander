#pragma once
#include <any>

#include "idata_forwarder.h"

class PIDForwarder : public IDataForwarder {
public:
    void forward(const std::any& data) override;
};
