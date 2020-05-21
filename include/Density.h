#pragma once

#include "NavierStokes.h"
#include "Quantity.h"

class Density : public NavierStokes, public SingleQuantity {
private:
    uint32_t m_quantity[2];

    const char CLEAR_PROGRAM_PATH = "resources/shader/compute/clear.cs";
    const Shader CLEAR_PROGRAM = Shader(CLEAR_PROGRAM_PATH);

public:
    Density(int N, Solver *solver);

    ~Density();

    void clear();

    void clearPrev();

    static void blur(const float *density, int gridSize, float sigma, float *target);

    void process(float dt, float diffusion, float *u, float *v) override;

    float *getQuantity() override;

    float *getPrevQuantity() override;
};
