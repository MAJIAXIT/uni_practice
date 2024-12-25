#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <functional>
#include <vector>
#include <cmath>

#define PI 2 * acos(0.0)

class Shape {
  protected:
    std::vector<float> vertices;
    std::vector<float> colors;
    GLuint VAO, VBO[2];

    void setupBuffers();

  public:
    Shape();
    Shape(int sides, float radius, glm::vec3 rgb = {1.0, 1.0, 1.0});
    Shape(std::vector<float> vertices, std::vector<float> colors);
    ~Shape();
    using DrawFunction = std::function<void()>;
    DrawFunction drawLogic;
    size_t getVertexCount() const { return vertices.size() / 3; }
    void generateRegularPolygonVertices(int sides, float radius, glm::vec3 rgb);
    void cleanup();
    void draw();
};

Shape::~Shape() { cleanup(); }

Shape::Shape() : drawLogic(nullptr), VAO(0) { VBO[0] = VBO[1] = 0; }

Shape::Shape(int sides, float radius, glm::vec3 rgb) {
    generateRegularPolygonVertices(sides, radius, rgb);
    setupBuffers();
}

Shape::Shape(std::vector<float> vertices, std::vector<float> colors) : Shape() {
    this->vertices = vertices;
    this->colors = colors;
    setupBuffers();
}

void Shape::draw() {
    if (drawLogic) {
        glBindVertexArray(VAO);
        drawLogic();
        glBindVertexArray(0);
    }
}

void Shape::setupBuffers() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(2, VBO);

    glBindVertexArray(VAO);

    // Vertex positions
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float),
                 vertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
                          (void *)0);
    glEnableVertexAttribArray(0);

    // Vertex colors
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(float), colors.data(),
                 GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
                          (void *)0);
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

void Shape::cleanup() {
    if (VAO) {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(2, VBO);
        VAO = 0;
        VBO[0] = VBO[1] = 0;
    }
}

void Shape::generateRegularPolygonVertices(int sides, float radius, glm::vec3 rgb) {
    vertices.clear();
    colors.clear();

    for (int i = 0; i < sides; ++i) {
        float theta = 2.0f * PI * i / sides;
        vertices.push_back(radius * cos(theta));
        vertices.push_back(radius * sin(theta));
        vertices.push_back(0.0f);

        colors.push_back(rgb[0]);
        colors.push_back(rgb[1]);
        colors.push_back(rgb[2]);
    }
}
