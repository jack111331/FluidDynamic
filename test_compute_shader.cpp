//
// Created by Edge on 2020/5/14.
//

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vo/GLFWWindowInfo.h>
#include <Shader.h>
#include <cassert>

#define NUM_PARTICLES 1023
#define WORK_GROUP_SIZE 128

struct pos {
    float x, y, z, w;
};

struct vel {
    float vx, vy, vz, vw;
};

struct color {
    float r, g, b, a;
};

uint32_t posSSbo;
uint32_t velSSbo;
uint32_t colSSbo;

using namespace std;

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
        }
        if (key == GLFW_KEY_ESCAPE) {
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        }
    }
}

static void GLFWErrorCallback(int error, const char *description) {
    cout << "[GLFW] " << description << endl;
}

static float RanF(float minimum, float maximum) {
    return minimum + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (maximum - minimum)));
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

    glewExperimental = GL_TRUE;
    glewInit();

    glPointSize(3.0f);

    glGenBuffers(1, &posSSbo);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, posSSbo);
    glBufferData(GL_SHADER_STORAGE_BUFFER, NUM_PARTICLES * sizeof(pos), NULL, GL_STATIC_DRAW);

    uint32_t bufMask = (GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);

    pos *points = (pos *) glMapBufferRange(GL_SHADER_STORAGE_BUFFER, 0, NUM_PARTICLES * sizeof(pos), bufMask);
    for (int i = 0; i < NUM_PARTICLES; ++i) {
        points[i].x = RanF(-0.1, 0.1);
        points[i].y = RanF(-0.1, 0.1);
        points[i].z = RanF(-0.1, 0.1);
        points[i].w = 1;
    }
    glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);

    glGenBuffers(1, &velSSbo);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, velSSbo);
    glBufferData(GL_SHADER_STORAGE_BUFFER, NUM_PARTICLES * sizeof(vel), NULL, GL_STATIC_DRAW);

    vel *vels = (vel *) glMapBufferRange(GL_SHADER_STORAGE_BUFFER, 0, NUM_PARTICLES * sizeof(vel), bufMask);
    for (int i = 0; i < NUM_PARTICLES; ++i) {
        vels[i].vx = RanF(-0.3, 0.3);
        vels[i].vy = RanF(-0.3, 0.3);
        vels[i].vz = RanF(-0.3, 0.3);
        vels[i].vw = 0.;
    }
    glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);

    glGenBuffers(1, &colSSbo);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, colSSbo);
    glBufferData(GL_SHADER_STORAGE_BUFFER, NUM_PARTICLES * sizeof(color), NULL, GL_STATIC_DRAW);
    color *cols = (color *) glMapBufferRange(GL_SHADER_STORAGE_BUFFER, 0, NUM_PARTICLES * sizeof(color), bufMask);
    for (int i = 0; i < NUM_PARTICLES; ++i) {
        cols[i].r = RanF(0.0, 1.0);
        cols[i].g = RanF(0.0, 1.0);
        cols[i].b = RanF(0.0, 1.0);
        cols[i].a = 1.;
    }
    glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);

    uint32_t vao;
    glGenVertexArrays(1, &vao);

    Shader computeShader = Shader("resources/shader/particle_system.cs")
            .buildShader();

    Shader normalShader = Shader("resources/shader/particle_system.vs", "resources/shader/particle_system.fs")
            .buildShader();

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);


        computeShader.bind();
        computeShader.bindBuffer(posSSbo, 0);
        computeShader.bindBuffer(velSSbo, 1);
        computeShader.bindBuffer(colSSbo, 2);
        computeShader.dispatch(NUM_PARTICLES, 1, 1);

        glBindBuffer(GL_SHADER_STORAGE_BUFFER, posSSbo);
        pos *ptr = (pos *) glMapBufferRange(GL_SHADER_STORAGE_BUFFER, 0, NUM_PARTICLES * sizeof(pos), GL_MAP_READ_BIT );
//        fprintf(stderr, "%d, (%f, %f, %f, %f)\n", 0, ptr[0].x, ptr[0].y, ptr[0].z, ptr[0].w);
        glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);

        normalShader.bind();
        glBindVertexArray(vao);
        glBindBuffer(GL_ARRAY_BUFFER, posSSbo);
        glVertexAttribPointer(0, 4, GL_FLOAT, false, 0, (void *) 0);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, velSSbo);
        glVertexAttribPointer(1, 4, GL_FLOAT, false, 0, (void *) 0);
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, colSSbo);
        glVertexAttribPointer(2, 4, GL_FLOAT, false, 0, (void *) 0);
        glEnableVertexAttribArray(2);
        glEnableClientState(GL_VERTEX_ARRAY);

        glDrawArrays(GL_POINTS, 0, NUM_PARTICLES);
        glDisableClientState(GL_VERTEX_ARRAY);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}
