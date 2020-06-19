#pragma once

#include "Quantity.h"
#include "Shader.h"
#include "ShaderUtility.h"
#include "Solver.h"
#include <cstdint>

class Velocity {
private:

    ShaderUtility *m_shaderUtility;
    JacobiSolver *m_solver;

    int m_grid;
    int m_currentContext;
    uint32_t m_uQuantity[2];
    uint32_t m_vQuantity[2];
    uint32_t m_texture;

    void addForce(float dt);

    void advectU(float dt);

    void advectV(float dt);

//    void vorticityConfinement(float dt, float vorticity);

    void massConserve();

public:
    Velocity(int N);

    ~Velocity();

    void clear(bool isPrevious);

    void process(float dt, float vorticity);

    float *enableAndGetReadWriteQuantity(int component, bool isPrevious);

    const float *enableAndGetReadQuantity(int component, bool isPrevious);

    void disableReadOrWriteQuantity(int component, bool isPrevious);

    uint32_t getBufferId(int component, bool isPrevious);

    uint32_t getTextureId();

    static const int U_COMPONENT = 1;
    static const int V_COMPONENT = 2;
};
