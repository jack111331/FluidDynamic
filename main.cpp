#include <iostream>
#include <cmath>
#include <stdint.h>
#include "Shader.h"
#include "Solver.h"
#include "Density.h"
#include "Velocity.h"
#include "Utility.h"
#include <GLFW/glfw3.h>
#include <Fluid2D.h>

using namespace std;

// #define DEBUG_MODE

static Solver *solver;
static Density *densityField;
static Velocity *velocityField;

static int N = 128;
static int timestep = 20;
static float dt = 0.1f;
static float diffusion = 0.0f;
static float viscosity = 0.0f;
static float source = 100.0f;
static float force = 5.0f;

static const int windowX = 800, windowY = 600;
static double prevMouseXpos, prevMouseYpos, mouseXpos, mouseYpos;
static bool displayMode = true;

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

static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
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

static void keyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
  if(action == GLFW_PRESS) {
    if(key == GLFW_KEY_V) {
      displayMode = !displayMode;
    }
    if(key == GLFW_KEY_C) {
      float *density = densityField->getQuantity();
      for(int i = 0;i < N+2;++i) {
        for(int j = 0;j < N+2;++j) {
          density[indexOf(i, j, N)] = 0.0f;
        }
      }
    }
    if(key == GLFW_KEY_ESCAPE) {
      glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
  }
}


static void mouseActionHandler() {
  int i = ((windowY-mouseYpos)/(double)windowY) * N + 1;
  int j = (mouseXpos/(double)windowX) * N + 1;
  if(i >= 1 && i < N && j >= 1 && j < N) {
    float *density = densityField->getPrevQuantity();
    float *u = velocityField->getPrevQuantity(Velocity::uComponent);
    float *v = velocityField->getPrevQuantity(Velocity::vComponent);
    if(mouseAction[0]) {
      u[indexOfVelocityU(i, j, N)] = force * (mouseXpos - prevMouseXpos);
      u[indexOfVelocityU(i, j+1, N)] = force * (mouseXpos - prevMouseXpos);
      v[indexOfVelocityV(i, j, N)] = force * (prevMouseYpos - mouseYpos);
      v[indexOfVelocityV(i+1, j, N)] = force * (prevMouseYpos - mouseYpos);
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

static uint32_t *createGridIndices(int N) {
  uint32_t *gridIndices = new uint32_t[2*N*N];
  int offset = N*N;
  for(int i = 0;i < N;++i) {
    for(int j = 0;j < N;++j) {
      gridIndices[2 * (i*N+j)] = (i*N+j);
      gridIndices[2 * (i*N+j) + 1] = (i*N+j) + offset;
    }
  }
  return gridIndices;
}

static float *createGridPosition(int N) {
  float *gridPosition = new float[3*N*N];
  float gridSize = 2.0f/N;
  for(int i = 0;i < N;++i) {
    for(int j = 0;j < N;++j) {
      gridPosition[3 * (i*N+j)] = -1.0f + gridSize * ((float)j + 0.5f);
      gridPosition[3 * (i*N+j) + 1] = -1.0f + gridSize * ((float)i + 0.5f);
      gridPosition[3 * (i*N+j) + 2] = 0.0f;
    }
  }
  return gridPosition;
}

static float *changeGridPosition(float *gridPosition, float *u, float *v, int N) {
  float gridSize = 2.0f/N;
  for(int i = 0;i < N;++i) {
    for(int j = 0;j < N;++j) {
      gridPosition[3 * (i*N+j)] = -1.0f + gridSize * ((float)j + 0.5f) + (u[indexOfVelocityU(i, j+1, N)] + u[indexOfVelocityU(i, j, N)]) * 0.5f;
      gridPosition[3 * (i*N+j) + 1] = -1.0f + gridSize * ((float)i + 0.5f) + (v[indexOfVelocityV(i+1, j, N)] + v[indexOfVelocityV(i, j, N)]) * 0.5f;
      gridPosition[3 * (i*N+j) + 2] = 0.0f;
    }
  }
  return gridPosition;
}

static void addGaussianWindForce(int gridWidth, float width, float *windDirection, int initWindLocation[][2], int amount) {
  float *u = velocityField->getQuantity(Velocity::uComponent);
  float *v = velocityField->getQuantity(Velocity::vComponent);

  for(int k = 0;k < amount;++k) {
    float uDirection = sin(windDirection[k]), vDirection = cos(windDirection[k]);
    for(int i = max(initWindLocation[k][0] - gridWidth, 1);i <= min(initWindLocation[k][0] + gridWidth, N);++i) {
      for(int j = max(initWindLocation[k][1] - gridWidth, 1);j <= min(initWindLocation[k][1] + gridWidth, N);++j) {
        int deltaC[2] = {initWindLocation[k][0] - i, initWindLocation[k][1] - j};
        float gaussFalloff = exp(-width * (deltaC[0] * deltaC[0] + deltaC[1] * deltaC[1]));
        u[indexOf(i, j, N)] += gaussFalloff * uDirection;
        v[indexOf(i, j, N)] += gaussFalloff * vDirection;
      }
    }
  }
}

static void addVortexForce(int gridWidth, float width, float r, int initVortexLocation[][2], int amount) {
  float *u = velocityField->getQuantity(Velocity::uComponent);
  float *v = velocityField->getQuantity(Velocity::vComponent);

  for(int k = 0;k < amount;++k) {
    for(int i = max(initVortexLocation[k][0] - gridWidth, 1);i <= min(initVortexLocation[k][0] + gridWidth, N);++i) {
      for(int j = max(initVortexLocation[k][1] - gridWidth, 1);j <= min(initVortexLocation[k][1] + gridWidth, N);++j) {
        int deltaC[2] = {initVortexLocation[k][0] - i, initVortexLocation[k][1] - j};
        float uDirection = -deltaC[1], vDirection = deltaC[0];
        float gaussFalloff = exp(-width * (deltaC[0] * deltaC[0] + deltaC[1] * deltaC[1]));
        #ifdef DEBUG_MODE
          cout << gaussFalloff << " " << uDirection << " " << vDirection << endl;
        #endif
        u[indexOf(i, j, N)] += r * gaussFalloff * uDirection;
        v[indexOf(i, j, N)] += r * gaussFalloff * vDirection;
      }
    }
  }
}

static void initializeState() {
  float *density = densityField->getQuantity();
  int initDensityLocation[10][2] = {
                              {7, 8},
                              {7, 9},
                              {8, 7},
                              {8, 8},
                              {9, 7},
                              {7, 7},
                              {9, 9},
                              {34, 34},
                              {34, 35},
                              {35, 34},
  };
  for(int i = 0;i < 10;++i) {
    density[indexOf(initDensityLocation[i][0], initDensityLocation[i][1], N)] += source;
  }

  float windDirection[3] = {0.3f, 1.7f, 1.0f}; // rad
  const int gridWidth = 4;
  const float width = 2.0f;
  int initVelocityLocation[3][2] = {
                              {50, 50},
                              {23, 22},
                              {20, 10}
  };
  const float r = 2.0f;
  addVortexForce(gridWidth, width, r, initVelocityLocation, 1);
  addGaussianWindForce(gridWidth, width, windDirection, initVelocityLocation, 3);
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

    GLFWwindow *window = glfwCreateWindow(800, 600, "Fluid2D Simulation", NULL, NULL);
    if(window == nullptr) {
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
    Fluid2D *fluid2D = new Fluid2D();
    fluid2D->init(N, timestep);

    solver = new GaussSeidelSolver(timestep);
    densityField = new Density(N, solver);
    velocityField = new Velocity(N);

    // initializeState();

    // mesh shader init
    Shader meshShader;
    meshShader.CreateShader("resources/shader/mesh.vs", "resources/shader/mesh.fs");

    // velocity shader init
    Shader velocityShader;
    velocityShader.CreateShader("resources/shader/velocity.vs", "resources/shader/velocity.fs");

    // Mesh VAO
    uint32_t *meshIndices = createMeshIndices(N);
    float *meshPosition = createMeshPosition(N);

    uint32_t meshVAO;
    glGenVertexArrays(1, &meshVAO);
    glBindVertexArray(meshVAO);

    // Mesh VBO
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

    // Mesh EBO
    uint32_t indicesEBO;
    glGenBuffers(1, &indicesEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * (N+1)*(N+1) * sizeof(uint32_t), meshIndices, GL_STATIC_DRAW);


    // Velocity VAO
    uint32_t *velocityIndices = createGridIndices(N);
    float *velocityPosition = createGridPosition(N);

    uint32_t velocityVAO;
    glGenVertexArrays(1, &velocityVAO);
    glBindVertexArray(velocityVAO);

    // Velocity VBO
    uint32_t velocityPositionVBO;
    glGenBuffers(1, &velocityPositionVBO);
    glBindBuffer(GL_ARRAY_BUFFER, velocityPositionVBO);
    glBufferData(GL_ARRAY_BUFFER, 2 * 3 * N*N * sizeof(float), nullptr, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, 3 * N*N * sizeof(float), velocityPosition);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    // EBO
    uint32_t velocityIndicesEBO;
    glGenBuffers(1, &velocityIndicesEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, velocityIndicesEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 2 * N*N * sizeof(uint32_t), velocityIndices, GL_STATIC_DRAW);

    #ifdef DEBUG_MODE
      velocityShader.Use();
      glBindVertexArray(velocityVAO);
      glBindBuffer(GL_ARRAY_BUFFER, velocityPositionVBO);
      float *uu = velocityField->getQuantity(Velocity::uComponent);
      float *vv = velocityField->getQuantity(Velocity::vComponent);
      changeGridPosition(velocityPosition, uu, vv, N);
      glBufferSubData(GL_ARRAY_BUFFER, 3 * N*N * sizeof(float), 3 * N*N * sizeof(float), velocityPosition);

      glDrawElements(GL_LINES, 2*N*N, GL_UNSIGNED_INT, 0);

      glBindVertexArray(0);

      glfwSwapBuffers(window);
      getchar();
    #endif

    while(!glfwWindowShouldClose(window)) {
      glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT);

      // Process density and velocity field
      float *u = velocityField->getPrevQuantity(Velocity::uComponent), *v = velocityField->getPrevQuantity(Velocity::vComponent);
      float *density = densityField->getPrevQuantity();
      for(int i = 0;i < N+2;++i) {
        for(int j = 0;j < N+2;++j) {
          density[indexOf(i, j, N)] = 0.0f;
        }
      }
      for(int i = 0;i <= N;++i) {
        for(int j = 0;j <= N+1;++j) {
          u[indexOfVelocityU(j, i, N)] = v[indexOfVelocityV(i, j, N)] = 0.0f;
        }
      }
      glfwPollEvents();
      mouseActionHandler();
      velocityField->process(dt, viscosity, u, v);

      u = velocityField->getQuantity(Velocity::uComponent);
      v = velocityField->getQuantity(Velocity::vComponent);
      densityField->process(dt, diffusion, u, v);
      density = densityField->getQuantity();

      if(!displayMode) {
        // Prepare density
        meshShader.Use();
        glBindVertexArray(meshVAO);
        glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, (N+2)*(N+2) * sizeof(float), density);

        glDrawElements(GL_TRIANGLES, 6*(N+1)*(N+1), GL_UNSIGNED_INT, 0);

        glBindVertexArray(0);
      } else {
        // Prepare velocity
        velocityShader.Use();
        glBindVertexArray(velocityVAO);
        glBindBuffer(GL_ARRAY_BUFFER, velocityPositionVBO);
        changeGridPosition(velocityPosition, u, v, N);
        glBufferSubData(GL_ARRAY_BUFFER, 3 * N*N * sizeof(float), 3 * N*N * sizeof(float), velocityPosition);

        glDrawElements(GL_LINES, 2*N*N, GL_UNSIGNED_INT, 0);

        glBindVertexArray(0);
      }

      glfwSwapBuffers(window);
      #ifdef DEBUG_MODE
        getchar();
      #endif
    }
    delete meshIndices;
    delete meshPosition;
    delete velocityIndices;
    delete velocityPosition;

    glfwTerminate();
    return 0;
}
