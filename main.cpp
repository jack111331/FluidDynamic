#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <Fluid2D.h>
#include <vo/GLFWWindowInfo.h>
#include <Control.h>

using namespace std;

Fluid2D *fluid2D;
static int N = 256;
static int timestep = 20;
static float dt = 0.1f;
static float diffusion = 0.0f;
static float viscosity = 0.0f;
static float source = 100.0f;
static float force = 5.0f;

static GLFWWindowInfo windowInfo{
        .windowWidth = 800,
        .windowHeight = 600
};

static bool displayMode = false;

static void cursorPositionCallback(GLFWwindow *window, double xpos, double ypos) {
    if (windowInfo.mouseAction[GLFWWindowInfo::MOUSE_LEFT] || windowInfo.mouseAction[GLFWWindowInfo::MOUSE_RIGHT]) {
        windowInfo.mouseXPos = xpos;
        windowInfo.mouseYPos = ypos;
    } else {
        windowInfo.prevMouseXPos = windowInfo.mouseXPos = xpos;
        windowInfo.prevMouseYPos = windowInfo.mouseYPos = ypos;
    }
}

static void mouseButtonCallback(GLFWwindow *window, int button, int action, int mods) {
    if (action == GLFW_PRESS) {
        windowInfo.mouseAction[button] = true;
    } else if (action == GLFW_RELEASE) {
        windowInfo.mouseAction[button] = false;
    }
}

static void keyboardCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        if (key == GLFW_KEY_V) {
            displayMode = !displayMode;
        }
        if (key == GLFW_KEY_C) {
            fluid2D->clear();
        }
        if (key == GLFW_KEY_ESCAPE) {
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        }
    }
}

static void GLFWErrorCallback(int error, const char *description) {
    cout << "[GLFW] " << description << endl;
}

int main() {
    // Environment preparation
    if (!glfwInit()) {
        cout << "[GLFW] init Failed" << endl;
        return 0;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwSetErrorCallback(GLFWErrorCallback);

    GLFWwindow *window = glfwCreateWindow(windowInfo.windowWidth, windowInfo.windowHeight, "Fluid2D Simulation", NULL,
                                          NULL);
    if (window == nullptr) {
        std::cout << "[GLFW] failed to create window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    glfwSetCursorPosCallback(window, cursorPositionCallback);
    glfwSetKeyCallback(window, keyboardCallback);

    glewInit();

    // Initial Setup
    fluid2D = new Fluid2D();
    fluid2D->init(N, timestep);

    TargetDrivenControl *control = new TargetDrivenControl("resources/animation/from_3_to_4/animation.kfd", dt);
    control->setTarget(fluid2D);
//    Control2D *control = new GenerateRisingSmoke();
//    control->setTarget(fluid2D);

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwPollEvents();
        fluid2D->input(&windowInfo, force, source);
//        control->control();

        fluid2D->update(dt, diffusion, viscosity);
        fluid2D->display(displayMode);
        glfwSwapBuffers(window);
        // TODO DEBUG
    }

    glfwTerminate();
    return 0;
}
