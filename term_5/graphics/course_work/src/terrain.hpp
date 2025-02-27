#ifndef TERRAIN_HPP
#define TERRAIN_HPP

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "stb_image.h"
#include <vector>
#include <string>
#include "shader.hpp"

class Terrain {
public:
    // Constructor takes texture path and dimensions
    Terrain(const std::string& texturePath, float width, float depth);
    ~Terrain();
    
    // Render the terrain
    void render(Shader& shader);
    
    // Get height at position (for collision detection, not used in basic implementation)
    float getHeightAt(float x, float z);
    float getWidth() const { return width; }
    float getDepth() const { return depth; }
    
private:
    // Terrain data
    unsigned int VAO, VBO, EBO;
    unsigned int textureID;
    
    int vertexCount;
    int indexCount;
    
    float width;
    float depth;
    
    // Setup terrain mesh and load texture
    void setupTerrain();
    unsigned int loadTexture(const char* path);
};

// Implementation

Terrain::Terrain(const std::string& texturePath, float width, float depth)
    : width(width), depth(depth) {
    
    // Create terrain mesh
    setupTerrain();
    
    // Load texture
    textureID = loadTexture(texturePath.c_str());
}

Terrain::~Terrain() {
    // Cleanup
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteTextures(1, &textureID);
}

void Terrain::setupTerrain() {
    // Simple flat terrain for this implementation
    // In a more complex version, we could use a heightmap
    
    // Define resolution (number of vertices in each dimension)
    const int resolution = 20;
    vertexCount = resolution * resolution;
    
    // Create vertices and indices
    std::vector<float> vertices;
    std::vector<unsigned int> indices;
    
    // Calculate spacing between vertices
    float spacingX = width / (resolution - 1);
    float spacingZ = depth / (resolution - 1);
    
    // Generate vertices (position, normal, texture coordinates)
    for (int z = 0; z < resolution; z++) {
        for (int x = 0; x < resolution; x++) {
            // Position
            float xPos = x * spacingX - width / 2.0f;
            float yPos = 0.0f; // Flat terrain
            float zPos = z * spacingZ - depth / 2.0f;
            
            // Normal (pointing up for flat terrain)
            float nx = 0.0f;
            float ny = 1.0f;
            float nz = 0.0f;
            
            // Texture coordinates
            float s = (float)x / (resolution - 1);
            float t = (float)z / (resolution - 1);
            
            // Add vertex data (position, normal, texcoords)
            vertices.push_back(xPos);
            vertices.push_back(yPos);
            vertices.push_back(zPos);
            vertices.push_back(nx);
            vertices.push_back(ny);
            vertices.push_back(nz);
            vertices.push_back(s * 10.0f); // Repeat texture 10 times
            vertices.push_back(t * 10.0f);
        }
    }
    
    // Generate indices for triangles
    for (int z = 0; z < resolution - 1; z++) {
        for (int x = 0; x < resolution - 1; x++) {
            unsigned int topLeft = z * resolution + x;
            unsigned int topRight = topLeft + 1;
            unsigned int bottomLeft = (z + 1) * resolution + x;
            unsigned int bottomRight = bottomLeft + 1;
            
            // First triangle (top-left, bottom-left, bottom-right)
            indices.push_back(topLeft);
            indices.push_back(bottomLeft);
            indices.push_back(bottomRight);
            
            // Second triangle (top-left, bottom-right, top-right)
            indices.push_back(topLeft);
            indices.push_back(bottomRight);
            indices.push_back(topRight);
        }
    }
    
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

void Terrain::render(Shader& shader) {
    // Set model matrix (identity for terrain - it doesn't move)
    glm::mat4 model = glm::mat4(1.0f);
    shader.setMat4("model", model);
    
    // Bind texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);
    shader.setInt("texture_diffuse1", 0);
    
    // Render the terrain
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

float Terrain::getHeightAt(float x, float z) {
    // In a real implementation with a heightmap, this would return the interpolated height
    // For a flat terrain, just return 0
    return 0.0f;
}

unsigned int Terrain::loadTexture(const char* path) {
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

#endif // TERRAIN_HPP