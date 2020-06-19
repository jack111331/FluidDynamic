//
// Created by Edge on 2020/4/23.
//

#ifndef FLUIDDYNAMIC_GLFWWINDOWINFO_H
#define FLUIDDYNAMIC_GLFWWINDOWINFO_H


#include <GLFW/glfw3.h>

class GLFWWindowInfo {
public:
    static GLFWWindowInfo *getInstance();

    int windowWidth, windowHeight;
    double prevMouseXPos, prevMouseYPos;
    double mouseXPos, mouseYPos;
    bool mouseAction[8];

    static const int MOUSE_LEFT = GLFW_MOUSE_BUTTON_LEFT;
    static const int MOUSE_RIGHT = GLFW_MOUSE_BUTTON_RIGHT;
private:
    static GLFWWindowInfo *instance;
};


#endif //FLUIDDYNAMIC_GLFWWINDOWINFO_H
