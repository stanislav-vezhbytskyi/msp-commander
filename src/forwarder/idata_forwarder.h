#pragma once


class IDataForwarder {
public:
    virtual ~IDataForwarder() = default;
    virtual void forward(const std::any& data) = 0;
};
