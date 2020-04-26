//
// Created by Edge on 2020/4/25.
//

#include <cmath>
#include "Control.h"

Control2D::Control2D() : m_target(nullptr) {

}

void Control2D::setTarget(Fluid2D *fluid2D) {
    m_target = fluid2D;
}

void Control2D::addDensity(int gridWidth, float width, int (&initWindLocation)[2], float source) {
    if (m_target) {
        m_target->addDensity(gridWidth, width, initWindLocation, source);
    }
}

void Control2D::addGaussianWindForce(int gridWidth, float width, double windDirection, int (&initWindLocation)[2]) {
    if (m_target) {
        m_target->addGaussianWindForce(gridWidth, width, windDirection, initWindLocation);
    }
}

void Control2D::addVortexForce(int gridWidth, float width, float r, int (&initVortexLocation)[2]) {
    if (m_target) {
        m_target->addVortexForce(gridWidth, width, r, initVortexLocation);
    }
}

void GenerateRisingSmoke::control() {
    double pi = acos(-1);
    // FIXME fixed grid size
    int initWindLocation[2] = {64, 3};
    addDensity(3, 1, initWindLocation, 10.0f);
//    addGaussianWindForce(3, 0.2f, pi * 0.5f, initWindLocation);
}

OptimizationControl::OptimizationControl(const std::string &keyframeAnimationFilename) {
    m_animation = new KeyframeAnimation();
    m_animation->loadAnimation(keyframeAnimationFilename);
}

void OptimizationControl::control() {
    Keyframe keyframe;
    int t = 2;
    m_animation->getKeyframeAtTime(t, keyframe);
}

OptimizationControl::~OptimizationControl() {
    delete m_animation;
}
