//
// Created by Edge on 2020/5/21.
//

#include "ShaderUtility.h"

const Shader ShaderUtility::GAUSS_SEIDEL_SOLVER_PROGRAM = Shader(ShaderUtility::GAUSS_SEIDEL_SOLVER_PROGRAM_PATH)
        .buildShader();

const Shader ShaderUtility::SET_DENSITY_BOUND_PROGRAM = Shader(ShaderUtility::SET_DENSITY_BOUND_PROGRAM_PATH)
        .buildShader();

const Shader ShaderUtility::SET_U_VELOCITY_BOUND_PROGRAM = Shader(ShaderUtility::SET_U_VELOCITY_BOUND_PROGRAM_PATH)
        .buildShader();

const Shader ShaderUtility::SET_V_VELOCITY_BOUND_PROGRAM = Shader(ShaderUtility::SET_V_VELOCITY_BOUND_PROGRAM_PATH)
        .buildShader();

const Shader ShaderUtility::GET_U_SUBROUTINE_SHADER = Shader(ShaderUtility::GET_U_SUBROUTINE_SHADER_PATH)
        .buildShader();

const Shader ShaderUtility::GET_V_SUBROUTINE_SHADER = Shader(ShaderUtility::GET_V_SUBROUTINE_SHADER_PATH)
        .buildShader();

const Shader ShaderUtility::LINEAR_INTERPOLATE_2D_SUBROUTINE_SHADER = Shader(ShaderUtility::LINEAR_INTERPOLATE_2D_SUBROUTINE_SHADER_PATH)
        .buildShader();
