#ifndef WATER_HPP
#define WATER_HPP

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "stb_image.h"
#include <string>
#include <vector>
#include "shader.hpp"

class Water {
public:
    // Constructor takes texture path and dimensions
    Water(const std::string& texturePath, float width, float depth);
    ~Water();
    
    // Render the water surface
    void render(Shader& shader);
    
private:
    // Water mesh data
    unsigned int VAO, VBO, EBO;
    unsigned int textureID;
    
    int vertexCount;
    int indexCount;
    
    float width;
    float depth;
    float height; // Height of water surface
    
    // Setup water mesh and load texture
    void setupWater();
    unsigned int loadTexture(const char* path);
};

// Implementation

Water::Water(const std::string& texturePath, float width, float depth)
    : width(width), depth(depth), height(-0.1f) {
    
    // Create water mesh
    setupWater();
    
    // Load texture
    textureID = loadTexture(texturePath.c_str());
}

Water::~Water() {
    // Cleanup
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteTextures(1, &textureID);
}

void Water::setupWater() {
    // Simple quad for water surface
    // In a more complex implementation, this could be a grid for wave animation
    
    // Create a quad surface
    std::vector<float> vertices = {
        // positions          // normals         // texture coords
        -width/2, height, -depth/2,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f,
         width/2, height, -depth/2,  0.0f, 1.0f, 0.0f,  width, 0.0f,
         width/2, height,  depth/2,  0.0f, 1.0f, 0.0f,  width, depth,
        -width/2, height,  depth/2,  0.0f, 1.0f, 0.0f,  0.0f, depth
    };
    
    std::vector<unsigned int> indices = {
        0, 1, 2,   // first triangle
        0, 2, 3    // second triangle
    };
    
    indexCount = indices.size();
    
    // Create OpenGL buffers
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    
    glBindVertexArray(VAO);
    
    // Position, normal, and texture coords
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
    
    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    // Normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    
    // Texture coordinate attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
    
    // Index buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
    
    glBindVertexArray(0);
}

void Water::render(Shader& shader) {
    // Enable transparency for water
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    // Set model matrix (identity for water - it doesn't move)
    glm::mat4 model = glm::mat4(1.0f);
    shader.setMat4("model", model);
    
    // Bind texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);
    shader.setInt("texture_diffuse1", 0);
    
    // Set water-specific parameters (for animation)
    shader.setFloat("waterHeight", height);
    shader.setFloat("waveSpeed", 1.0f);
    shader.setFloat("waveStrength", 0.02f);
    
    // Render the water surface
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    
    // Disable blend after rendering water
    glDisable(GL_BLEND);
}

unsigned int Water::loadTexture(const char* path) {
    unsigned int textureID;
    glGenTextures(1, &textureID);
    
    int width, height, nrComponents;
    unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data) {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;
        
        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        
        stbi_image_free(data);
    } else {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }
    
    return textureID;
}

#endif // WATER_HPP