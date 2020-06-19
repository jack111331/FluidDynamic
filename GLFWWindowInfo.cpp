//
// Created by Edge on 2020/6/19.
//

#include "vo/GLFWWindowInfo.h"

GLFWWindowInfo *GLFWWindowInfo::instance = nullptr;

GLFWWindowInfo *GLFWWindowInfo::getInstance() {
    if(GLFWWindowInfo::instance == nullptr) {
        GLFWWindowInfo::instance = new GLFWWindowInfo();
    }
    return GLFWWindowInfo::instance;
}