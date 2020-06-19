//
// Created by Edge on 2020/5/21.
//

#include <GL/glew.h>
#include "ShaderUtility.h"

ShaderUtility *ShaderUtility::instance = nullptr;

constexpr char ShaderUtility::SET_DENSITY_BOUND_PROGRAM_PATH[];

constexpr char ShaderUtility::SET_U_VELOCITY_BOUND_PROGRAM_PATH[];

constexpr char ShaderUtility::SET_V_VELOCITY_BOUND_PROGRAM_PATH[];

constexpr char ShaderUtility::GET_U_SUBROUTINE_SHADER_PATH[];

constexpr char ShaderUtility::GET_V_SUBROUTINE_SHADER_PATH[];

constexpr char ShaderUtility::GET_DENSITY_SUBROUTINE_SHADER_PATH[];

constexpr char ShaderUtility::LINEAR_INTERPOLATE_2D_SUBROUTINE_SHADER_PATH[];

constexpr char ShaderUtility::CLEAR_DENSITY_PROGRAM_PATH[];
constexpr char ShaderUtility::ADD_DENSITY_PROGRAM_PATH[];
constexpr char ShaderUtility::ADVECT_DENSITY_PROGRAM_PATH[];

constexpr char ShaderUtility::CLEAR_VELOCITY_PROGRAM_PATH[];
constexpr char ShaderUtility::ADD_VELOCITY_PROGRAM_PATH[];
constexpr char ShaderUtility::ADVECT_U_VELOCITY_PROGRAM_PATH[];
constexpr char ShaderUtility::ADVECT_V_VELOCITY_PROGRAM_PATH[];
//constexpr char ShaderUtility::CONFINE_VORTICITY_VELOCITY_PROGRAM_PATH[];
constexpr char ShaderUtility::BUILD_PRESSURE_PROGRAM_PATH[];
constexpr char ShaderUtility::CONSERVE_MASS_PROGRAM_PATH[];


constexpr char ShaderUtility::JACOBI_SOLVER_PROGRAM_PATH[];

constexpr char ShaderUtility::RECTANGLE_VERT_PATH[];
constexpr char ShaderUtility::ADVECT_ENVIRONMENT_PROGRAM_FRAG_PATH[];
constexpr char ShaderUtility::RECTANGLE_FRAG_PATH[];

ShaderUtility::ShaderUtility() {
    SET_DENSITY_BOUND_PROGRAM.addShader(GL_COMPUTE_SHADER, ShaderUtility::SET_DENSITY_BOUND_PROGRAM_PATH);
    SET_DENSITY_BOUND_PROGRAM.buildShader();

    SET_U_VELOCITY_BOUND_PROGRAM.addShader(GL_COMPUTE_SHADER,
                                           ShaderUtility::SET_U_VELOCITY_BOUND_PROGRAM_PATH);
    SET_U_VELOCITY_BOUND_PROGRAM.buildShader();

    SET_V_VELOCITY_BOUND_PROGRAM.addShader(GL_COMPUTE_SHADER,
                                           ShaderUtility::SET_V_VELOCITY_BOUND_PROGRAM_PATH);
    SET_V_VELOCITY_BOUND_PROGRAM.buildShader();

    GET_U_SUBROUTINE_SHADER.addShader(GL_COMPUTE_SHADER, ShaderUtility::GET_U_SUBROUTINE_SHADER_PATH);

    GET_V_SUBROUTINE_SHADER.addShader(GL_COMPUTE_SHADER, ShaderUtility::GET_V_SUBROUTINE_SHADER_PATH);

    GET_DENSITY_SUBROUTINE_SHADER.addShader(GL_COMPUTE_SHADER, ShaderUtility::GET_DENSITY_SUBROUTINE_SHADER_PATH);

    LINEAR_INTERPOLATE_2D_SUBROUTINE_SHADER.addShader(GL_COMPUTE_SHADER,
                                                      ShaderUtility::LINEAR_INTERPOLATE_2D_SUBROUTINE_SHADER_PATH);

    CLEAR_DENSITY_PROGRAM.addShader(GL_COMPUTE_SHADER, ShaderUtility::CLEAR_DENSITY_PROGRAM_PATH);
    CLEAR_DENSITY_PROGRAM.buildShader();
    ADD_DENSITY_PROGRAM.addShader(GL_COMPUTE_SHADER, ShaderUtility::ADD_DENSITY_PROGRAM_PATH);
    ADD_DENSITY_PROGRAM.buildShader();
    ADVECT_DENSITY_PROGRAM.addShader(GL_COMPUTE_SHADER, ShaderUtility::ADVECT_DENSITY_PROGRAM_PATH);
    ADVECT_DENSITY_PROGRAM.addAttachShader(&GET_U_SUBROUTINE_SHADER);
    ADVECT_DENSITY_PROGRAM.addAttachShader(&GET_V_SUBROUTINE_SHADER);
    ADVECT_DENSITY_PROGRAM.addAttachShader(&GET_DENSITY_SUBROUTINE_SHADER);
    ADVECT_DENSITY_PROGRAM.addAttachShader(&LINEAR_INTERPOLATE_2D_SUBROUTINE_SHADER);
    ADVECT_DENSITY_PROGRAM.buildShader();

    CLEAR_VELOCITY_PROGRAM.addShader(GL_COMPUTE_SHADER, ShaderUtility::CLEAR_VELOCITY_PROGRAM_PATH);
    CLEAR_VELOCITY_PROGRAM.buildShader();

    ADD_VELOCITY_PROGRAM.addShader(GL_COMPUTE_SHADER, ShaderUtility::ADD_VELOCITY_PROGRAM_PATH);
    ADD_VELOCITY_PROGRAM.buildShader();

    ADVECT_U_VELOCITY_PROGRAM.addShader(GL_COMPUTE_SHADER, ShaderUtility::ADVECT_U_VELOCITY_PROGRAM_PATH);
    ADVECT_U_VELOCITY_PROGRAM.addAttachShader(&GET_U_SUBROUTINE_SHADER);
    ADVECT_U_VELOCITY_PROGRAM.addAttachShader(&GET_V_SUBROUTINE_SHADER);
    ADVECT_U_VELOCITY_PROGRAM.addAttachShader(&LINEAR_INTERPOLATE_2D_SUBROUTINE_SHADER);
    ADVECT_U_VELOCITY_PROGRAM.buildShader();

    ADVECT_V_VELOCITY_PROGRAM.addShader(GL_COMPUTE_SHADER, ShaderUtility::ADVECT_V_VELOCITY_PROGRAM_PATH);
    ADVECT_V_VELOCITY_PROGRAM.addAttachShader(&GET_U_SUBROUTINE_SHADER);
    ADVECT_V_VELOCITY_PROGRAM.addAttachShader(&GET_V_SUBROUTINE_SHADER);
    ADVECT_V_VELOCITY_PROGRAM.addAttachShader(&LINEAR_INTERPOLATE_2D_SUBROUTINE_SHADER);
    ADVECT_V_VELOCITY_PROGRAM.buildShader();

    CONSERVE_MASS_PROGRAM.addShader(GL_COMPUTE_SHADER, ShaderUtility::CONSERVE_MASS_PROGRAM_PATH);
    CONSERVE_MASS_PROGRAM.addAttachShader(&GET_U_SUBROUTINE_SHADER);
    CONSERVE_MASS_PROGRAM.addAttachShader(&GET_V_SUBROUTINE_SHADER);
    CONSERVE_MASS_PROGRAM.addAttachShader(&GET_DENSITY_SUBROUTINE_SHADER);
    CONSERVE_MASS_PROGRAM.buildShader();

    BUILD_PRESSURE_PROGRAM.addShader(GL_COMPUTE_SHADER, ShaderUtility::BUILD_PRESSURE_PROGRAM_PATH);
    BUILD_PRESSURE_PROGRAM.addAttachShader(&GET_U_SUBROUTINE_SHADER);
    BUILD_PRESSURE_PROGRAM.addAttachShader(&GET_V_SUBROUTINE_SHADER);
    BUILD_PRESSURE_PROGRAM.addAttachShader(&GET_DENSITY_SUBROUTINE_SHADER);
    BUILD_PRESSURE_PROGRAM.buildShader();

    JACOBI_SOLVER_PROGRAM.addShader(GL_COMPUTE_SHADER, ShaderUtility::JACOBI_SOLVER_PROGRAM_PATH);
    JACOBI_SOLVER_PROGRAM.addAttachShader(&GET_DENSITY_SUBROUTINE_SHADER);
    JACOBI_SOLVER_PROGRAM.buildShader();

    ADVECT_ENVIRONMENT_PROGRAM.addShader(GL_VERTEX_SHADER, ShaderUtility::RECTANGLE_VERT_PATH);
    ADVECT_ENVIRONMENT_PROGRAM.addShader(GL_FRAGMENT_SHADER, ShaderUtility::ADVECT_ENVIRONMENT_PROGRAM_FRAG_PATH);
    ADVECT_ENVIRONMENT_PROGRAM.buildShader();

    RECTANGLE_PROGRAM.addShader(GL_VERTEX_SHADER, ShaderUtility::RECTANGLE_VERT_PATH);
    RECTANGLE_PROGRAM.addShader(GL_FRAGMENT_SHADER, ShaderUtility::RECTANGLE_FRAG_PATH);
    RECTANGLE_PROGRAM.buildShader();
}

ShaderUtility *ShaderUtility::getInstance() {
    if (ShaderUtility::instance == nullptr) {
        ShaderUtility::instance = new ShaderUtility();
    }
    return instance;
}
