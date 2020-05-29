//
// Created by Edge on 2020/5/21.
//

#ifndef FLUIDDYNAMIC_SHADERUTILITY_H
#define FLUIDDYNAMIC_SHADERUTILITY_H


#include "Shader.h"

class ShaderUtility {
public:

    static constexpr char GAUSS_SEIDEL_SOLVER_PROGRAM_PATH[] = "resources/shader/compute/common/GaussSeidel.cs";
    static const Shader GAUSS_SEIDEL_SOLVER_PROGRAM;

    static constexpr char SET_DENSITY_BOUND_PROGRAM_PATH[] = "resources/shader/compute/common/SetDensityBoundary.shader";
    static const Shader SET_DENSITY_BOUND_PROGRAM;

    static constexpr char SET_U_VELOCITY_BOUND_PROGRAM_PATH[] = "resources/shader/compute/common/SetUVelocityBoundary.cs";
    static const Shader SET_U_VELOCITY_BOUND_PROGRAM;

    static constexpr char SET_V_VELOCITY_BOUND_PROGRAM_PATH[] = "resources/shader/compute/common/SetVVelocityBoundary.cs";
    static const Shader SET_V_VELOCITY_BOUND_PROGRAM;

    static constexpr char GET_U_SUBROUTINE_SHADER_PATH[] = "resources/shader/compute/common/GetU.shader";
    static const Shader GET_U_SUBROUTINE_SHADER;

    static constexpr char GET_V_SUBROUTINE_SHADER_PATH[] = "resources/shader/compute/common/GetV.shader";
    static const Shader GET_V_SUBROUTINE_SHADER;

    static constexpr char LINEAR_INTERPOLATE_2D_SUBROUTINE_SHADER_PATH[] = "resources/shader/compute/common/LinearInterpolate2D.shader";
    static const Shader LINEAR_INTERPOLATE_2D_SUBROUTINE_SHADER;
};


#endif //FLUIDDYNAMIC_SHADERUTILITY_H
