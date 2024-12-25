#pragma once
#include "shader.hpp"
#include "shape.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <map>
#include <memory>

// Definitions for the second task rotations in shapes 5, 6 and 7
#define KX 2.0f
#define KY 1.5f
#define PX 0.2f
#define PY 0.5f
#define ALPHA 30.0f // degrees
#define ROT_X 3.0f
#define ROT_Y 3.0f
#define BETA -15.0f // degrees

class Renderer {
  protected:
    std::shared_ptr<Shader> shader;
    std::map<int, std::shared_ptr<Shape>> shapes;
    int currentTask;

  public:
    Renderer();
    void init();
    void setupShapes();
    void render(int task);
    void cleanup();
};

Renderer::Renderer() : currentTask(1) {}

void Renderer::init() {
    shader = std::make_shared<Shader>();
    shader->load("vertex.glsl", "fragment.glsl");
    setupShapes();
}

void Renderer::setupShapes() {
    shapes[1] = std::make_shared<Shape>(5, 0.5f, glm::vec3{1, 1, 1});
    shapes[1]->setIndices(std::vector<unsigned int>{
        0, 1, 2, //
        2, 3, 4, //
        2, 4, 0, //
    });
    shapes[1]->drawLogic = [=]() {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    };
    shapes[1]->setupBuffers();

    shapes[2] = std::make_shared<Shape>(5, 0.5f, glm::vec3{1, 1, 0});
    shapes[2]->setIndices(std::vector<unsigned int>{
        0, 2, //
        2, 4, //
        4, 1, //
        1, 3, //
        3, 0, //
    });
    shapes[2]->drawLogic = [=]() {
        glLineWidth(3.0);
        glDrawElements(GL_LINE_STRIP, 10, GL_UNSIGNED_INT, 0);
    };
    shapes[2]->setupBuffers();

    shapes[3] = std::make_shared<Shape>(5, 0.5f, glm::vec3{0, 1, 0});
    shapes[3]->setIndices(std::vector<unsigned int>{
        0, 1, //
        1, 2, //
        2, 3, //
        3, 4, //
        4, 0, //
    });
    shapes[3]->drawLogic = [=]() {
        glLineWidth(3.0);
        glDrawElements(GL_LINE_STRIP, 10, GL_UNSIGNED_INT, 0);
    };
    shapes[3]->setupBuffers();

    shapes[4] = std::make_shared<Shape>(5, 0.5f, glm::vec3{0, 1, 1});
    shapes[4]->setIndices(std::vector<unsigned int>{
        0, 2, //
        2, 4, //
    });
    shapes[4]->drawLogic = [=]() {
        glLineWidth(3.0);
        glDrawElements(GL_LINE_LOOP, 4, GL_UNSIGNED_INT, 0);
    };
    shapes[4]->setupBuffers();

    shapes[5] = std::make_shared<Shape>(
        std::vector<float>{
            -0.2, -0.2, 0, //
            0, 0, 0,       //
            0.2, -0.2, 0,  //
        },
        std::vector<float>{
            1, 1, 1, //
            1, 1, 1, //
            1, 1, 1, //
        });
    shapes[5]->drawLogic = [=]() {
        glDrawArrays(GL_TRIANGLES, 0, 3);

        GLint modelLoc = glGetUniformLocation(shader->getProgram(), "model");

        glm::mat4 scaleMat =
            glm::scale(glm::mat4(1.0f), glm::vec3(KX, KY, 1.0f));
        glm::mat4 translateMat =
            glm::translate(glm::mat4(1.0f), glm::vec3(PX, PY, 0.0f));
        glm::mat4 triangleTransform = translateMat * scaleMat;
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE,
                           glm::value_ptr(triangleTransform));
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Restore shader model variable
        triangleTransform = glm::mat4(1.0f);
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE,
                           glm::value_ptr(triangleTransform));
    };
    shapes[5]->setupBuffers();

    shapes[6] = std::make_shared<Shape>(
        std::vector<float>{
            0.7, 0.7, 0,   //
            -0.3, -0.3, 0, //
        },
        std::vector<float>{
            0.5, 1, 1, //
            0.5, 1, 1, //
        });
    shapes[6]->drawLogic = [=]() {
        glDrawArrays(GL_LINES, 0, 2);

        GLint modelLoc = glGetUniformLocation(shader->getProgram(), "model");

        glm::mat4 lineRotation = glm::rotate(
            glm::mat4(1.0f), glm::radians(ALPHA), glm::vec3(0.0f, 0.0f, 1.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(lineRotation));
        glDrawArrays(GL_LINES, 0, 2);

        // Restore shader model variable
        lineRotation = glm::mat4(1.0f);
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(lineRotation));
    };
    shapes[6]->setupBuffers();

    shapes[7] = std::make_shared<Shape>(
        std::vector<float>{
            0, -0.6, 0,    //
            0.6f, -0.6, 0, //
            0, 0, 0,       //
            0, 0, 0,       //
            0.6f, -0.6, 0, //
            0.6f, 0, 0,    //
        },
        std::vector<float>{
            0.5, 1, 0.5, //
            0.5, 1, 0.5, //
            0.5, 1, 0.5, //
            0.5, 1, 0.5, //
            0.5, 1, 0.5, //
            0.5, 1, 0.5, //
        });
    shapes[7]->drawLogic = [=]() {
        glDrawArrays(GL_TRIANGLES, 0, 6);

        GLint modelLoc = glGetUniformLocation(shader->getProgram(), "model");

        glm::mat4 rectRotation =
            glm::translate(glm::mat4(1.0f), glm::vec3(ROT_X, ROT_Y, 0.0f));
        rectRotation = glm::rotate(rectRotation, glm::radians(BETA),
                                   glm::vec3(0.0f, 0.0f, 1.0f));
        rectRotation =
            glm::translate(rectRotation, glm::vec3(-ROT_X, -ROT_Y, 0.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(rectRotation));
        glDrawArrays(GL_TRIANGLES, 0, 6);

        // Restore shader model variable
        rectRotation = glm::mat4(1.0f);
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(rectRotation));
    };
    shapes[7]->setupBuffers();

    shapes[8] = std::make_shared<Shape>(
        std::vector<float>{
            -0.1, 0.1, 0, //
            0.1, 0.1, 0,  //
        },
        std::vector<float>{
            0.5, 1, 0.5, //
            0.5, 1, 0.5, //
        });
    shapes[8]->drawLogic = [=]() {
        GLint modelLoc = glGetUniformLocation(shader->getProgram(), "model");

        glm::mat4 model;

        std::vector<std::pair<glm::vec3, float>> transformations = {
            {{0.0f, 0.0f, 0.0f}, 0.0f},    //
            {{0.2f, 0.2f, 0.0f}, 90.0f},   //
            {{0.2f, 0.4f, 0.0f}, -90.0f},  //
            {{-0.2f, 0.2f, 0.0f}, -90.0f}, //
            {{-0.2f, 0.4f, 0.0f}, 90.0f},  //
            {{0.0f, 0.6f, 0.0f}, 90.0f},   //
        };

        for (auto trans : transformations) {
            model = glm::translate(glm::mat4(1.0f), trans.first);
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
            glDrawArrays(GL_LINES, 0, 2);

            model = glm::rotate(model, glm::radians(trans.second),
                                glm::vec3(0.0f, 0.0f, 1.0f));
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
            glDrawArrays(GL_LINES, 0, 2);
        }

        // last rotation
        model = glm::rotate(model, glm::radians(180.0f),
                            glm::vec3(0.0f, 0.0f, 1.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_LINES, 0, 2);

        // Restore shader model variable
        model = glm::mat4(1.0f);
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    };
    shapes[8]->setupBuffers();
}

void Renderer::render(int task) {
    currentTask = task;

    if (shapes.find(task) != shapes.end()) {
        shader->use();
        shapes[task]->draw();
    }
}

void Renderer::cleanup() {
    shader->cleanup();
    shapes.clear();
}
