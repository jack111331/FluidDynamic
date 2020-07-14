#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <Fluid2D.h>
#include <vo/GLFWWindowInfo.h>
#include <Control.h>

using namespace std;

Fluid2D *fluid2D;
static int N = 128;
static int timestep = 20;
static float dt = 0.1f;
static float diffusion = 1.0f;
static float viscosity = 0.0f;
static float source = 100.0f;
static float force = 5.0f;

int windowWidth = 800;
int windowHeight = 600;

static int displayMode = 0;

static void cursorPositionCallback(GLFWwindow *window, double xpos, double ypos) {
    GLFWWindowInfo *glfwWindowInfo = GLFWWindowInfo::getInstance();
    if (glfwWindowInfo->mouseAction[GLFWWindowInfo::MOUSE_LEFT] || glfwWindowInfo->mouseAction[GLFWWindowInfo::MOUSE_RIGHT]) {
        glfwWindowInfo->mouseXPos = xpos;
        glfwWindowInfo->mouseYPos = ypos;
    } else {
        glfwWindowInfo->prevMouseXPos = glfwWindowInfo->mouseXPos = xpos;
        glfwWindowInfo->prevMouseYPos = glfwWindowInfo->mouseYPos = ypos;
    }
}

static void mouseButtonCallback(GLFWwindow *window, int button, int action, int mods) {
    GLFWWindowInfo *glfwWindowInfo = GLFWWindowInfo::getInstance();
    if (action == GLFW_PRESS) {
        glfwWindowInfo->mouseAction[button] = true;
    } else if (action == GLFW_RELEASE) {
        glfwWindowInfo->mouseAction[button] = false;
    }
}

static void keyboardCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        if (key == GLFW_KEY_V) {
            displayMode = (displayMode + 1) % 3;
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

    GLFWWindowInfo *glfwWindowInfo = GLFWWindowInfo::getInstance();
    glfwWindowInfo->windowWidth = windowWidth;
    glfwWindowInfo->windowHeight = windowHeight;

    GLFWwindow *window = glfwCreateWindow(windowWidth, windowHeight, "Fluid2D Simulation", NULL,
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

    const GLubyte *vendor = glGetString(GL_VENDOR); // Returns the vendor
    const GLubyte *renderer = glGetString(GL_RENDERER);
    std::cout << "Current Vendor: " << (const char *) vendor << std::endl;
    std::cout << "Current Renderer: " << (const char *) renderer << std::endl;

    // Initial Setup
    const char image[] = "image.png";
    fluid2D = new Fluid2D();
    fluid2D->init(N, timestep);
    fluid2D->addEnvironment(new Environment(image));

//    TargetDrivenControl *control = new TargetDrivenControl("resources/animation/from_3_to_4/animation.kfd", dt);
//    control->setTarget(fluid2D);
    Control2D *control = new GenerateRisingSmoke();
    control->setTarget(fluid2D);

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwPollEvents();
        fluid2D->input(force, source);
        control->control();

        fluid2D->update(dt, diffusion, viscosity);
        fluid2D->display(displayMode);
        glfwSwapBuffers(window);
//        getchar();
        // TODO DEBUG
    }

    glfwTerminate();
    return 0;
}
