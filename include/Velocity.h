#pragma once

#include "Quantity.h"
#include "Shader.h"
#include "ShaderUtility.h"
#include <cstdint>

class Velocity : public MultipleQuantity {
private:
    static constexpr char CLEAR_VELOCITY_PROGRAM_PATH[] = "resources/shader/compute/ClearDensity.cs";
    const Shader CLEAR_VELOCITY_PROGRAM = Shader(Velocity::CLEAR_VELOCITY_PROGRAM_PATH)
            .buildShader();


    static constexpr char ADD_VELOCITY_PROGRAM_PATH[] = "resources/shader/compute/AddVelocity.cs";
    const Shader ADD_VELOCITY_PROGRAM = Shader(Velocity::ADD_VELOCITY_PROGRAM_PATH)
            .addAttachShader(&ShaderUtility::SET_U_VELOCITY_BOUND_PROGRAM)
            .addAttachShader(&ShaderUtility::SET_V_VELOCITY_BOUND_PROGRAM)
            .buildShader();

    static constexpr char ADVECT_U_VELOCITY_PROGRAM_PATH[] = "resources/shader/compute/AdvectUVelocity.cs";
    const Shader ADVECT_U_VELOCITY_PROGRAM = Shader(Velocity::ADVECT_U_VELOCITY_PROGRAM_PATH)
            .addAttachShader(&ShaderUtility::SET_U_VELOCITY_BOUND_PROGRAM)
            .buildShader();

    static constexpr char ADVECT_V_VELOCITY_PROGRAM_PATH[] = "resources/shader/compute/AdvectVVelocity.cs";
    const Shader ADVECT_V_VELOCITY_PROGRAM = Shader(Velocity::ADVECT_V_VELOCITY_PROGRAM_PATH)
            .addAttachShader(&ShaderUtility::SET_V_VELOCITY_BOUND_PROGRAM)
            .buildShader();

    static constexpr char CONFINE_VORTICITY_VELOCITY_PROGRAM_PATH[] = "resources/shader/compute/ConfineVorticityVelocity.cs";
    const Shader CONFINE_VORTICITY_VELOCITY_PROGRAM = Shader(Velocity::CONFINE_VORTICITY_VELOCITY_PROGRAM_PATH)
            .addAttachShader(&ShaderUtility::SET_U_VELOCITY_BOUND_PROGRAM)
            .addAttachShader(&ShaderUtility::SET_V_VELOCITY_BOUND_PROGRAM)
            .buildShader();

    int m_grid;
    int m_currentContext;
    uint32_t m_uQuantity[2];
    uint32_t m_vQuantity[2];

    void addForce(float dt);

    void advectU(float dt);

    void advectV(float dt);

    void vorticityConfinement(float dt, float vorticity);

    void massConserve(float dt);

public:
    Velocity(int N);

    ~Velocity();

    void clear(bool isPrevious);

    void process(float dt, float vorticity);

    uint32_t getQuantity(int component) override;

    uint32_t getPrevQuantity(int component) override;

    static const int U_COMPONENT = 1;
    static const int V_COMPONENT = 2;
};
