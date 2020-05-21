//
// Created by Edge on 2020/4/25.
//

#ifndef FLUIDDYNAMIC_CONTROL_H
#define FLUIDDYNAMIC_CONTROL_H


#include "Fluid2D.h"
#include "Keyframe.h"
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

class OptimizationControl : public Control2D {
public:
    OptimizationControl(const std::string &keyframeAnimationFilename);
    virtual void control();
    virtual ~OptimizationControl();
private:
    KeyframeAnimation *m_animation;
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
