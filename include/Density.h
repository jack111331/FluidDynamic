#pragma once

#include <cstdint>
#include "NavierStokes.h"
#include "Quantity.h"
#include "Shader.h"
#include "ShaderUtility.h"

class Density : public SingleQuantity {
private:
    static constexpr char CLEAR_DENSITY_PROGRAM_PATH[] = "resources/shader/compute/ClearDensity.cs";
    const Shader CLEAR_DENSITY_PROGRAM = Shader(Density::CLEAR_DENSITY_PROGRAM_PATH)
            .buildShader();

    static constexpr char ADD_DENSITY_PROGRAM_PATH[] = "resources/shader/compute/AddDensity.cs";
    const Shader ADD_DENSITY_PROGRAM = Shader(Density::ADD_DENSITY_PROGRAM_PATH)
            .buildShader();

    static constexpr char DIFFUSE_DENSITY_PROGRAM_PATH[] = "resources/shader/compute/DiffuseDensity.cs";
    const Shader DIFFUSE_DENSITY_PROGRAM = Shader(Density::DIFFUSE_DENSITY_PROGRAM_PATH)
            .addAttachShader(&ShaderUtility::GAUSS_SEIDEL_SOLVER_PROGRAM)
            .buildShader();

    static constexpr char ADVECT_DENSITY_PROGRAM_PATH[] = "resources/shader/compute/AdvectDensity.cs";
    const Shader ADVECT_DENSITY_PROGRAM = Shader(Density::ADVECT_DENSITY_PROGRAM_PATH)
            .addAttachShader(&ShaderUtility::SET_DENSITY_BOUND_PROGRAM)
            .buildShader();

    uint32_t m_quantity[2];
    int m_grid;
    bool m_currentContext;

public:
    Density(int N);

    ~Density();

    void clear(bool isPrevious);

    static void blur(const float *density, int gridSize, float sigma, float *target);

    void addQuantity(float dt);

    void diffuse(float dt, float diffusion);

    void advect(float dt, uint32_t u, uint32_t v);

    void process(float dt, float diffusion, uint32_t u, uint32_t v);

    uint32_t getQuantity() override;

    uint32_t getPrevQuantity() override;
};
