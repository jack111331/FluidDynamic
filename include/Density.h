#pragma once

#include <cstdint>
#include "NavierStokes.h"
#include "Quantity.h"
#include "Shader.h"
#include "ShaderUtility.h"

class Density {
private:
    ShaderUtility *m_shaderUtility;
    JacobiSolver *m_solver;

    uint32_t m_quantity[2];
    int m_grid;
    bool m_currentContext;

public:
    Density(int N);

    ~Density();

    void clear(bool isPrevious);

    static void blur(const float *density, int gridSize, float sigma, float *target);

    void addDensity(float dt);

    void diffuse(float dt, float diffusion);

    void advect(float dt, uint32_t u, uint32_t v);

    void process(float dt, float diffusion, uint32_t u, uint32_t v);

    float *enableAndGetReadWriteQuantity(bool isPrevious);

    const float *enableAndGetReadQuantity(bool isPrevious);

    void disableReadOrWriteQuantity(bool isPrevious);
};
