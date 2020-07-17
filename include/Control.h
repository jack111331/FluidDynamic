//
// Created by Edge on 2020/4/25.
//

#ifndef FLUIDDYNAMIC_CONTROL_H
#define FLUIDDYNAMIC_CONTROL_H


#include "Fluid2D.h"
#include "Keyframe.h"
#include "DensityDerivative.h"
#include "VelocityDerivative.h"
#include <string>

class Control2D {
public:
    Control2D();

    void setTarget(Fluid2D *fluid2D);

    virtual void control() = 0;

protected:
    void addDensity(int gridWidth, float width, int (&initWindLocation)[2], float source);

    void addGaussianWindForce(int gridWidth, float width, double windDirection, int (&initWindLocation)[2]);

    void addVortexForce(int gridWidth, float width, float r, int (&initVortexLocation)[2]);

    Fluid2D *m_target;
};

class GenerateRisingSmoke : public Control2D {
public:
    virtual void control();
};

class ControlForce {
public:
    // in my setting, to simply, we only optimize wind force direction and vortex force's r
    struct GaussianWindForce {
        int centerX, centerY;
        float a = 1.0f;
        // optimize over below two
        float directionX, directionY;
    };
    struct GaussianWindForceDerivative {
        float dDirectionX, dDirectionY;
    };
    struct VortexForce {
        int centerX, centerY;
        float a = 1.0f;
        // optimize over below one
        float r;
    };
    struct VortexForceDerivative {
        float dR;
    };

    std::vector<GaussianWindForce> gaussianWindForceList;
    std::vector<VortexForce> vortexForceList;
};

class OptimizationControl : public Control2D {
public:
    OptimizationControl(const std::string &keyframeAnimationFilename);

    virtual void control();

    struct EvaluateResult {
        float phi;
        std::vector<ControlForce::GaussianWindForceDerivative> gaussianWindForceDerivativeList;
        std::vector<ControlForce::VortexForceDerivative> vortexForceDerivativeList;
    };

    EvaluateResult evaluate(const std::vector<ControlForce> &controlForceSequence);

    virtual ~OptimizationControl();

private:
    KeyframeAnimation *m_animation;
    std::vector<ControlForce> m_controlForceSequence;
    std::vector<DensityDerivative *> m_densityDerivativeList;
    std::vector<VelocityDerivative *> m_velocityDerivativeList;
};

class TargetDrivenControl : public Control2D {
public:
    TargetDrivenControl(const std::string &keyframeAnimationFilename, float dt);

    virtual void control();

    virtual ~TargetDrivenControl();

private:
    KeyframeAnimation *m_animation;
    float m_dt;
};

#endif //FLUIDDYNAMIC_CONTROL_H
