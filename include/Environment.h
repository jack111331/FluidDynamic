//
// Created by Edge on 2020/6/11.
//

#ifndef COMPUTESHADERTEST_ENVIRONMENT_H
#define COMPUTESHADERTEST_ENVIRONMENT_H


#include <cstdint>
#include <string>

class Environment {
public:
    Environment(const std::string &textureFilename);

    void advect(float dt, int gridSize, uint32_t gridVAO, uint32_t u, uint32_t v);

    uint32_t getCurrentTexture() const;
    void bindAndActiveCurrentTexture(int slot);
    void drawEnvironment();

private:
    uint32_t m_rectFBO;
    uint32_t m_rectVAO;
    uint32_t m_rectDataVBO;

    uint32_t m_rawTexture;
    uint32_t m_texture[2];
    bool m_currentContext = false;
};


#endif //COMPUTESHADERTEST_ENVIRONMENT_H
