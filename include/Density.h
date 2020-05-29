#pragma once

#include <cstdint>
#include "NavierStokes.h"
#include "Quantity.h"
#include "Shader.h"
#include "ShaderUtility.h"

class Density : public SingleQuantity {
private:
    static constexpr char CLEAR_DENSITY_PROGRAM_PATH[] = "resources/shader/compute/ClearDensity.shader";
    const Shader CLEAR_DENSITY_PROGRAM = Shader(Density::CLEAR_DENSITY_PROGRAM_PATH)
            .buildShader();

    static constexpr char ADD_DENSITY_PROGRAM_PATH[] = "resources/shader/compute/AddDensity.shader";
    const Shader ADD_DENSITY_PROGRAM = Shader(Density::ADD_DENSITY_PROGRAM_PATH)
            .buildShader();

    static constexpr char ADVECT_DENSITY_PROGRAM_PATH[] = "resources/shader/compute/AdvectDensity.shader";
    const Shader ADVECT_DENSITY_PROGRAM = Shader(Density::ADVECT_DENSITY_PROGRAM_PATH)
            // FIXME May have latter load problem
            .addAttachShader(&ShaderUtility::GET_U_SUBROUTINE_SHADER)
            .addAttachShader(&ShaderUtility::GET_V_SUBROUTINE_SHADER)
            .addAttachShader(&ShaderUtility::LINEAR_INTERPOLATE_2D_SUBROUTINE_SHADER)
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
