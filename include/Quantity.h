#pragma once

#include <cstdint>

class SingleQuantity {
public:
    virtual uint32_t getQuantity() = 0;

    virtual uint32_t getPrevQuantity() = 0;
};

class MultipleQuantity {
public:
    virtual uint32_t getQuantity(int component) = 0;

    virtual uint32_t getPrevQuantity(int component) = 0;
};
