//
// Created by Edge on 2020/6/11.
//

#include <cstdint>
#include <GL/glew.h>
#include <iostream>
#include <ShaderUtility.h>
#include <vo/GLFWWindowInfo.h>
#include "Environment.h"

#include "stb_image.h"

Environment::Environment(const std::string &textureFilename) {
    // Rectangle VAO
    glGenVertexArrays(1, &m_rectVAO);
    glBindVertexArray(m_rectVAO);

    // Rectangle VBO
    const float rectPosition[30] = {
            -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
            1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
            1.0f, 1.0f, 0.0f, 1.0f, 1.0f,

            1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
            -1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
            -1.0f, -1.0f, 0.0f, 0.0f, 0.0f
    };

    glGenBuffers(1, &m_rectDataVBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_rectDataVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(rectPosition), rectPosition, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), nullptr);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    glGenFramebuffers(1, &m_rectFBO);
    glBindFramebuffer(GL_FRAMEBUFFER, m_rectFBO);

    int width, height, channel;
    uint8_t *pixel = stbi_load(textureFilename.c_str(), &width, &height, &channel, 0);
    if (!pixel) {
        std::cerr << "[ERROR] Can't load " << textureFilename << std::endl;
        exit(1);
    }

    GLint level = 0;
    if(channel == 3) {
        level = GL_RGB;
    } else if(channel == 4){
        level = GL_RGBA;
    }

    glGenTextures(1, &m_rawTexture);
    glBindTexture(GL_TEXTURE_2D, m_rawTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, level, width, height, 0, level, GL_UNSIGNED_BYTE, pixel);
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    GLFWWindowInfo *glfwWindowInfo = GLFWWindowInfo::getInstance();
    glGenTextures(2, m_texture);
    for(int i = 0;i < 2;++i) {
        glBindTexture(GL_TEXTURE_2D, m_texture[i]);
        glTexImage2D(GL_TEXTURE_2D, 0, level, glfwWindowInfo->windowWidth, glfwWindowInfo->windowHeight, 0, level, GL_UNSIGNED_BYTE, nullptr);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    }
    glBindTexture(GL_TEXTURE_2D, 0);

    stbi_image_free(pixel);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texture[m_currentContext], 0);
    ShaderUtility::getInstance()->RECTANGLE_PROGRAM.bind();
    ShaderUtility::getInstance()->RECTANGLE_PROGRAM.uniform1i("samplerWeed", 0);
    glBindVertexArray(m_rectVAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_rectDataVBO);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_rawTexture);

    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Environment::advect(float dt, int gridSize, uint32_t u, uint32_t v) {
    glBindFramebuffer(GL_FRAMEBUFFER, m_rectFBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texture[m_currentContext ^ 1], 0);
    // Render advect texture to framebuffer
    ShaderUtility::getInstance()->ADVECT_ENVIRONMENT_PROGRAM.bind();
    ShaderUtility::getInstance()->ADVECT_ENVIRONMENT_PROGRAM.bindBuffer(0, u);
    ShaderUtility::getInstance()->ADVECT_ENVIRONMENT_PROGRAM.bindBuffer(1, v);
    ShaderUtility::getInstance()->ADVECT_ENVIRONMENT_PROGRAM.uniform1f("dt0", dt * gridSize);
    ShaderUtility::getInstance()->ADVECT_ENVIRONMENT_PROGRAM.uniform1i("samplerWeed", 0);
    glBindVertexArray(m_rectVAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_rectDataVBO);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_texture[m_currentContext]);

    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    m_currentContext ^= 1;
}

uint32_t Environment::getCurrentTexture() const {
    return m_texture[m_currentContext];
}

void Environment::bindAndActiveCurrentTexture(int slot) {
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, m_texture[m_currentContext]);
}

void Environment::drawEnvironment() {
    ShaderUtility::getInstance()->RECTANGLE_PROGRAM.bind();
    ShaderUtility::getInstance()->RECTANGLE_PROGRAM.uniform1i("samplerWeed", 0);
    glBindVertexArray(m_rectVAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_rectDataVBO);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_texture[m_currentContext]);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0);
}