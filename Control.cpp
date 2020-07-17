//
// Created by Edge on 2020/4/25.
//

#include <cmath>
#include <iostream>
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
//    m_controlForceSequence add 9 gauss wind and 2 vortex

// TODO
//    evaluate()
}

OptimizationControl::EvaluateResult OptimizationControl::evaluate(const std::vector<ControlForce> &controlForceSequence) {
    if(controlForceSequence.empty()) {
        std::cerr << "No control force sequence" << std::endl;
        exit(1);
    }
    EvaluateResult result;
    result.phi = 0.0f;
    for(int i = 0;i < controlForceSequence[0].gaussianWindForceList.size();++i) {
        result.gaussianWindForceDerivativeList.push_back({0.0f, 0.0f});
    }
    for(int i = 0;i < controlForceSequence[0].vortexForceList.size();++i) {
        result.vortexForceDerivativeList.push_back({0.0f});
    }
//    TODO add velocity derivative and density derivative class
}

OptimizationControl::~OptimizationControl() {
    delete m_animation;
}

TargetDrivenControl::TargetDrivenControl(const std::string &keyframeAnimationFilename, float dt) {
    m_animation = new KeyframeAnimation();
    m_animation->loadAnimation(keyframeAnimationFilename);
    m_dt = dt;
}

void TargetDrivenControl::control() {
    if (m_target) {
        Keyframe keyframe;
        int t = 0;
        m_animation->getKeyframeAtTime(t, keyframe);
        // Add driving force
        float vf = 3.0f;
        int initWindLocation[2] = {32, 40};
        addDensity(3, 1, initWindLocation, 1000.0f);

        m_target->addDrivingForce(m_dt, vf, keyframe.m_pixel);
    }
}

TargetDrivenControl::~TargetDrivenControl() {
    delete m_animation;
}