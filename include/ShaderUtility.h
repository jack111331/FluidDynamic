//
// Created by Edge on 2020/5/21.
//

#ifndef FLUIDDYNAMIC_SHADERUTILITY_H
#define FLUIDDYNAMIC_SHADERUTILITY_H


#include "Shader.h"

class ShaderUtility {
public:
    static ShaderUtility *getInstance();

    Shader SET_DENSITY_BOUND_PROGRAM;
    Shader SET_U_VELOCITY_BOUND_PROGRAM;
    Shader SET_V_VELOCITY_BOUND_PROGRAM;
    Shader GET_U_SUBROUTINE_SHADER;
    Shader GET_V_SUBROUTINE_SHADER;
    Shader GET_DENSITY_SUBROUTINE_SHADER;
    Shader LINEAR_INTERPOLATE_2D_SUBROUTINE_SHADER;

    Shader CLEAR_DENSITY_PROGRAM;
    Shader ADD_DENSITY_PROGRAM;
    Shader ADVECT_DENSITY_PROGRAM;

    Shader CLEAR_VELOCITY_PROGRAM;
    Shader ADD_VELOCITY_PROGRAM;
    Shader ADVECT_U_VELOCITY_PROGRAM;
    Shader ADVECT_V_VELOCITY_PROGRAM;
    //    Shader CONFINE_VORTICITY_VELOCITY_PROGRAM = Shader(Velocity::CONFINE_VORTICITY_VELOCITY_PROGRAM_PATH);
    Shader BUILD_PRESSURE_PROGRAM;
    Shader CONSERVE_MASS_PROGRAM;


    Shader JACOBI_SOLVER_PROGRAM;


    Shader ADVECT_ENVIRONMENT_PROGRAM;
    Shader RECTANGLE_PROGRAM;

private:
    ShaderUtility();
    static ShaderUtility *instance;

    /* Common Shader */
    static constexpr char SET_DENSITY_BOUND_PROGRAM_PATH[] = "resources/shader/compute/common/SetDensityBoundary.shader";

    static constexpr char SET_U_VELOCITY_BOUND_PROGRAM_PATH[] = "resources/shader/compute/common/SetUVelocityBoundary.shader";

    static constexpr char SET_V_VELOCITY_BOUND_PROGRAM_PATH[] = "resources/shader/compute/common/SetVVelocityBoundary.shader";

    static constexpr char GET_U_SUBROUTINE_SHADER_PATH[] = "resources/shader/compute/common/GetU.shader";

    static constexpr char GET_V_SUBROUTINE_SHADER_PATH[] = "resources/shader/compute/common/GetV.shader";

    static constexpr char GET_DENSITY_SUBROUTINE_SHADER_PATH[] = "resources/shader/compute/common/GetDensity.shader";

    static constexpr char LINEAR_INTERPOLATE_2D_SUBROUTINE_SHADER_PATH[] = "resources/shader/compute/common/LinearInterpolate2D.shader";


    /* Density Relate Shader */

    // location = 0: quantity
    static constexpr char CLEAR_DENSITY_PROGRAM_PATH[] = "resources/shader/compute/ClearDensity.shader";

    // location = 0: current quantity
    // location = 1: previous quantity
    static constexpr char ADD_DENSITY_PROGRAM_PATH[] = "resources/shader/compute/AddDensity.shader";

    // location = 0: current quantity
    // location = 1: previous quantity
    // location = 2: current u vector field
    // location = 3: current v vector field
    static constexpr char ADVECT_DENSITY_PROGRAM_PATH[] = "resources/shader/compute/AdvectDensity.shader";



    /* Velocity Relate Shader */

    // location = 0: U component quantity
    // location = 1: V component quantity
    static constexpr char CLEAR_VELOCITY_PROGRAM_PATH[] = "resources/shader/compute/ClearVelocity.shader";

    // location = 0: current U component quantity
    // location = 1: previous U component quantity
    // location = 2: current V component quantity
    // location = 3: previous V component quantity
    static constexpr char ADD_VELOCITY_PROGRAM_PATH[] = "resources/shader/compute/AddVelocity.shader";

    // location = 0: current U component quantity
    // location = 1: previous U component quantity
    // location = 2: previous V component quantity
    static constexpr char ADVECT_U_VELOCITY_PROGRAM_PATH[] = "resources/shader/compute/AdvectUVelocity.shader";

    // location = 0: current V component quantity
    // location = 1: previous U component quantity
    // location = 2: previous V component quantity
    static constexpr char ADVECT_V_VELOCITY_PROGRAM_PATH[] = "resources/shader/compute/AdvectVVelocity.shader";

    // location = 0: current U component quantity
    // location = 1: current V component quantity
    // location = 2: previous U component quantity
    // location = 3: previous V component quantity
//    static constexpr char CONFINE_VORTICITY_VELOCITY_PROGRAM_PATH[] = "resources/shader/compute/ConfineVorticityVelocity.cs";

    // location = 0: current Pressure quantity
    // location = 1: previous Pressure quantity
    // location = 2: current U component quantity
    // location = 3: current V component quantity
    static constexpr char BUILD_PRESSURE_PROGRAM_PATH[] = "resources/shader/compute/BuildPressure.shader";

    // location = 0: current U component quantity
    // location = 1: current V component quantity
    // location = 2: current Pressure quantity
    static constexpr char CONSERVE_MASS_PROGRAM_PATH[] = "resources/shader/compute/ConserveMass.shader";


    /* Solver Relate Shader */

    // location = 0: quantity
    // location = 1: previous quantity
    static constexpr char JACOBI_SOLVER_PROGRAM_PATH[] = "resources/shader/compute/Jacobi.shader";

    /* Render Relate Shader */
    static constexpr char RECTANGLE_VERT_PATH[] = "resources/shader/RectangleVert.shader";
    static constexpr char ADVECT_ENVIRONMENT_PROGRAM_FRAG_PATH[] = "resources/shader/AdvectEnvironmentFrag.shader";
    static constexpr char RECTANGLE_FRAG_PATH[] = "resources/shader/RectangleFrag.shader";
};


#endif //FLUIDDYNAMIC_SHADERUTILITY_H
