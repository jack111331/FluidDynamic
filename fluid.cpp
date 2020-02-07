#include <iostream>
#include <stdint.h>
#include "Shader.h"
#include "Solver.h"
#include "Density.h"
#include "Velocity.h"
#include "Utility.h"
#include <GLFW/glfw3.h>
using namespace std;

static Solver *solver;
static Density *densityField;
static Velocity *velocityField;

static int N = 64;
static int timestep = 20;
static float dt = 0.1f;
static float diffusion = 0.0f;
static float viscosity = 0.0f;
static float source = 100.0f;
static float force = 5.0f;

static const int windowX = 800, windowY = 600;
static double prevMouseXpos, prevMouseYpos, mouseXpos, mouseYpos;
static bool displayMode = false;

bool mouseAction[2];

static void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos) {
  if(mouseAction[0] || mouseAction[1]) {
    mouseXpos = xpos;
    mouseYpos = ypos;
  } else {
    prevMouseXpos = mouseXpos = xpos;
    prevMouseYpos = mouseYpos = ypos;
  }
}

static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
  if(action == GLFW_PRESS) {
    if(button == GLFW_MOUSE_BUTTON_RIGHT) {
      mouseAction[1] = true;
    } else if(button == GLFW_MOUSE_BUTTON_LEFT) {
      mouseAction[0] = true;
    }
  } else if(action == GLFW_RELEASE) {
    if(button == GLFW_MOUSE_BUTTON_RIGHT) {
      mouseAction[1] = false;
    } else if(button == GLFW_MOUSE_BUTTON_LEFT) {
      mouseAction[0] = false;
    }
  }
}

static void mouseActionHandler() {
  int i = ((windowY-mouseYpos)/(double)windowY) * N + 1;
  int j = (mouseXpos/(double)windowX) * N + 1;
  if(i >= 1 && i <= N && j >= 1 && j <= N) {
    float *density = densityField->getPrevQuantity();
    float *u = velocityField->getPrevQuantity(Velocity::uComponent);
    float *v = velocityField->getPrevQuantity(Velocity::vComponent);
    if(mouseAction[0]) {
      u[indexOf(i, j, N)] = force * (prevMouseYpos - mouseYpos);
      v[indexOf(i, j, N)] = force * (mouseXpos - prevMouseXpos);
    }
    if(mouseAction[1]) {
      density[indexOf(i, j, N)] = source;
    }
  }
  prevMouseXpos = mouseXpos;
  prevMouseYpos = mouseYpos;
}

static void GLFWErrorCallback(int error, const char *description) {
  cout << "[GLFW] " << description << endl;
}

static uint32_t *createMeshIndices(int N) {
  uint32_t *meshIndices = new uint32_t[6*(N+1)*(N+1)];
  for(int i = 0;i < N+1;++i) {
    for(int j = 0;j < N+1;++j) {
      meshIndices[6 * (i*(N+1)+j)] = indexOf(i, j, N);
      meshIndices[6 * (i*(N+1)+j) + 1] = indexOf(i+1, j, N);
      meshIndices[6 * (i*(N+1)+j) + 2] = indexOf(i+1, j+1, N);
      meshIndices[6 * (i*(N+1)+j) + 3] = indexOf(i, j, N);
      meshIndices[6 * (i*(N+1)+j) + 4] = indexOf(i+1, j+1, N);
      meshIndices[6 * (i*(N+1)+j) + 5] = indexOf(i, j+1, N);
    }
  }
  return meshIndices;
}

static float *createMeshPosition(int N) {
  float *meshPosition = new float[3*(N+2)*(N+2)];
  float gridSize = 2.0f/(N+1);
  for(int i = 0;i <= N+1;++i) {
    for(int j = 0;j <= N+1;++j) {
      meshPosition[3 * indexOf(i, j, N)] = -1.0f + gridSize * j;
      meshPosition[3 * indexOf(i, j, N) + 1] = -1.0f + gridSize * i;
      meshPosition[3 * indexOf(i, j, N) + 2] = 0.0f;
    }
  }
  return meshPosition;
}

int main() {
    // Environment preparation
    if(!glfwInit()) {
      cout << "[GLFW] init Failed" << endl;
      return 0;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwSetErrorCallback(GLFWErrorCallback);

    GLFWwindow *window = glfwCreateWindow(800, 600, "Fluid Simulation", NULL, NULL);
    if(window == nullptr) {
      std::cout << "[GLFW] failed to create window" << std::endl;
      glfwTerminate();
      return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    glfwSetCursorPosCallback(window, cursorPositionCallback);

    glewInit();

    // Initial Setup

    solver = new GaussSeidelSolver(timestep);
    densityField = new Density(N, solver);
    velocityField = new Velocity(N, solver);

    // Shader init
    Shader meshShader;
    meshShader.CreateShader("mesh.vs", "mesh.fs");

    // Prepare mesh
    uint32_t *meshIndices = createMeshIndices(N);
    float *meshPosition = createMeshPosition(N);

    uint32_t meshVAO;
    glGenVertexArrays(1, &meshVAO);
    glBindVertexArray(meshVAO);

    // Create necessary VBO
    uint32_t positionVBO;
    glGenBuffers(1, &positionVBO);
    glBindBuffer(GL_ARRAY_BUFFER, positionVBO);
    glBufferData(GL_ARRAY_BUFFER, 3 * (N+2)*(N+2) * sizeof(float), meshPosition, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    uint32_t colorVBO;
    glGenBuffers(1, &colorVBO);
    glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
    glBufferData(GL_ARRAY_BUFFER, (N+2)*(N+2) * sizeof(float), nullptr, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, sizeof(float), nullptr);
    glEnableVertexAttribArray(1);

    // EBO
    uint32_t indicesEBO;
    glGenBuffers(1, &indicesEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * (N+1)*(N+1) * sizeof(uint32_t), meshIndices, GL_STATIC_DRAW);

    // glBindVertexArray(0);

    while(!glfwWindowShouldClose(window)) {
      glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT);

      meshShader.Use();
      glBindVertexArray(meshVAO);

      // Process density and velocity field
      float *u = velocityField->getPrevQuantity(Velocity::uComponent), *v = velocityField->getPrevQuantity(Velocity::vComponent);
      float *density = densityField->getPrevQuantity();
      for(int i = 0;i < N+2;++i) {
        for(int j = 0;j < N+2;++j) {
          u[indexOf(i, j, N)] = v[indexOf(i, j, N)] = density[indexOf(i, j, N)] = 0.0f;
        }
      }
      glfwPollEvents();
      mouseActionHandler();
      velocityField->process(dt, viscosity, u, v);

      u = velocityField->getQuantity(Velocity::uComponent);
      v = velocityField->getQuantity(Velocity::vComponent);
      densityField->process(dt, diffusion, u, v);
      density = densityField->getQuantity();

      // Prepare density
      glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
      glBufferSubData(GL_ARRAY_BUFFER, 0, (N+2)*(N+2) * sizeof(float), density);

      glDrawElements(GL_TRIANGLES, 6*(N+1)*(N+1), GL_UNSIGNED_INT, 0);        

      glBindVertexArray(0);

      glfwSwapBuffers(window);
    }
    glfwTerminate();
    return 0;
}
