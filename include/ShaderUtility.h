//
// Created by Edge on 2020/5/21.
//

#ifndef FLUIDDYNAMIC_SHADERUTILITY_H
#define FLUIDDYNAMIC_SHADERUTILITY_H


#include "Shader.h"

class ShaderUtility {
public:

    static constexpr char GAUSS_SEIDEL_SOLVER_PROGRAM_PATH[] = "resources/shader/compute/GaussSeidel.cs";
    static const Shader GAUSS_SEIDEL_SOLVER_PROGRAM;

    static constexpr char SET_DENSITY_BOUND_PROGRAM_PATH[] = "resources/shader/compute/SetDensityBoundary.cs";
    static const Shader SET_DENSITY_BOUND_PROGRAM;

    static constexpr char SET_U_VELOCITY_BOUND_PROGRAM_PATH[] = "resources/shader/compute/SetUVelocityBoundary.cs";
    static const Shader SET_U_VELOCITY_BOUND_PROGRAM;

    static constexpr char SET_V_VELOCITY_BOUND_PROGRAM_PATH[] = "resources/shader/compute/SetVVelocityBoundary.cs";
    static const Shader SET_V_VELOCITY_BOUND_PROGRAM;
};


#endif //FLUIDDYNAMIC_SHADERUTILITY_H
