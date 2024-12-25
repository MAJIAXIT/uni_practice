#pragma once
#include "shader.hpp"
#include "shape.hpp"
#include <glm/glm.hpp>
#include <map>
#include <memory>

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
    auto polygon1 = std::make_shared<Shape>(5, 0.5f, glm::vec3{1, 1, 1});
    polygon1->drawLogic = [=]() {
        glEnable(GL_POINT_SMOOTH);
        glPointSize(10.0f);
        glDrawArrays(GL_POINTS, 0, polygon1->getVertexCount());
        glDisable(GL_POINT_SMOOTH);
    };
    shapes[1] = polygon1;

    auto polygon2 = std::make_shared<Shape>(5, 0.5f, glm::vec3{1, 1, 0});
    polygon2->drawLogic = [polygon2]() {
        glLineWidth(3.0f);
        glDrawArrays(GL_LINE_LOOP, 0, polygon2->getVertexCount());
    };
    shapes[2] = polygon2;

    auto polygon8 = std::make_shared<Shape>(5, 0.5f, glm::vec3{0, 1, 0});
    polygon8->drawLogic = [polygon8]() {
        glLineWidth(3.0f);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glDrawArrays(GL_TRIANGLE_FAN, 0, polygon8->getVertexCount());
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    };
    shapes[8] = polygon8;

    std::vector<float> vertices3 = {
        -0.5f, 0.3f,  0.0f, //
        -0.1f, 0.5f,  0.0f, //
        0.2f,  0.0f,  0.0f, //
        -0.2f, -0.5f, 0.0f, //
        0.5f,  -0.5f, 0.0f, //
        0.7f,  -0.1f, 0.0f, //
    };
    std::vector<float> colors3 = {
        1.0f, 0.0f, 1.0f, //
        1.0f, 0.0f, 1.0f, //
        1.0f, 0.0f, 1.0f, //
        1.0f, 0.0f, 1.0f, //
        1.0f, 0.0f, 1.0f, //
        1.0f, 0.0f, 1.0f, //
    };
    auto shape3 = std::make_shared<Shape>(vertices3, colors3);
    shape3->drawLogic = [shape3]() {
        glLineWidth(3.0f);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glDrawArrays(GL_LINE_STRIP, 0, shape3->getVertexCount());
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    };
    shapes[3] = shape3;

    std::vector<float> vertices4 = {
        0.0f,  0.7f,  0.0f, //
        0.3f,  0.5f,  0.0f, //
        0.1f,  0.1f,  0.0f, //
        0.4f,  -0.1f, 0.0f, //
        0.2f,  -0.5f, 0.0f, //
        -0.4f, -0.1f, 0.0f, //
    };
    std::vector<float> colors4 = {
        0.0f, 1.0f, 1.0f, //
        0.0f, 1.0f, 1.0f, //
        0.0f, 1.0f, 1.0f, //
        0.0f, 1.0f, 1.0f, //
        0.0f, 1.0f, 1.0f, //
        0.0f, 1.0f, 1.0f, //
    };
    auto shape4 = std::make_shared<Shape>(vertices4, colors4);
    shape4->drawLogic = [shape4]() {
        glLineWidth(3.0f);
        glDrawArrays(GL_LINE_LOOP, 0, shape4->getVertexCount());
    };
    shapes[4] = shape4;

    std::vector<float> vertices5 = {
        0.0f,  0.7f,  0.0f, //
        0.3f,  0.5f,  0.0f, //
        0.1f,  0.1f,  0.0f, //

        0.0f,  0.7f,  0.0f, //
        0.1f,  0.1f,  0.0f, //
        -0.4f, -0.1f, 0.0f, //

        0.1f,  0.1f,  0.0f, //
        0.4f,  -0.1f, 0.0f, //
        0.2f,  -0.5f, 0.0f, //

        0.1f,  0.1f,  0.0f, //
        0.2f,  -0.5f, 0.0f, //
        -0.4f, -0.1f, 0.0f, //
    };
    std::vector<float> colors5 = {
        1.0f, 0.0f, 0.0f, //
        1.0f, 0.0f, 0.0f, //
        1.0f, 0.0f, 0.0f, //

        0.0f, 1.0f, 0.0f, //
        0.0f, 1.0f, 0.0f, //
        0.0f, 1.0f, 0.0f, //

        0.0f, 0.0f, 1.0f, //
        0.0f, 0.0f, 1.0f, //
        0.0f, 0.0f, 1.0f, //

        1.0f, 1.0f, 0.0f, //
        1.0f, 1.0f, 0.0f, //
        1.0f, 1.0f, 0.0f, //
    };
    auto shape5 = std::make_shared<Shape>(vertices5, colors5);
    shape5->drawLogic = [shape5]() {
        glLineWidth(3.0f);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glDrawArrays(GL_TRIANGLES, 0, shape5->getVertexCount());
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    };
    shapes[5] = shape5;

    std::vector<float> vertices6 = {
        0.3f,  0.5f,  0.0f, //
        0.0f,  0.7f,  0.0f, //
        0.1f,  0.1f,  0.0f, //

        -0.4f, -0.1f, 0.0f, //
        0.4f,  -0.1f, 0.0f, //
        0.2f,  -0.5f, 0.0f, //
    };
    std::vector<float> colors6 = {
        1.0f, 0.0f, 0.0f, //
        0.0f, 1.0f, 0.0f, //
        0.0f, 0.0f, 1.0f, //

        1.0f, 1.0f, 0.0f, //
        0.0f, 1.0f, 1.0f, //
        1.0f, 1.0f, 1.0f, //
    };
    auto shape6 = std::make_shared<Shape>(vertices6, colors6);
    shape6->drawLogic = [shape6]() {
        glLineWidth(3.0f);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, shape6->getVertexCount());
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    };
    shapes[6] = shape6;

    std::vector<float> vertices7 = {
        -0.4f, -0.1f, 0.0f, //
        0.0f,  0.7f,  0.0f, //
        0.3f,  0.5f,  0.0f, //
        0.1f,  0.1f,  0.0f, //
        0.4f,  -0.1f, 0.0f, //
        0.2f,  -0.5f, 0.0f  //
    };
    std::vector<float> colors7 = {
        1.0f, 0.0f, 0.0f, //
        0.0f, 1.0f, 0.0f, //
        0.0f, 0.0f, 1.0f, //

        1.0f, 1.0f, 0.0f, //
        0.0f, 1.0f, 1.0f, //
        1.0f, 1.0f, 1.0f, //
    };
    auto shape7 = std::make_shared<Shape>(vertices7, colors7);
    shape7->drawLogic = [shape7]() {
        glLineWidth(3.0f);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glDrawArrays(GL_TRIANGLE_FAN, 0, shape7->getVertexCount());
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    };
    shapes[7] = shape7;

    std::vector<float> vertices9 = {
        -0.7f, 0.8f,  0.0f, //
        0.1f,  0.8f,  0.0f, //
        -0.5f, 0.2f,  0.0f, //

        -0.2f, -0.2f, 0.0f, //
        0.3f,  0.3f,  0.0f, //
        0.3f,  0.7f,  0.0f, //

        0.7f,  0.5f,  0.0f, //
        0.7f,  -0.6f, 0.0f, //
        -0.7f, -0.6f, 0.0f, //
    };
    std::vector<float> colors9 = {
        1.0f, 1.0f, 1.0f, //
        1.0f, 1.0f, 1.0f, //
        1.0f, 1.0f, 1.0f, //

        1.0f, 1.0f, 1.0f, //
        1.0f, 1.0f, 1.0f, //
        1.0f, 1.0f, 1.0f, //

        1.0f, 1.0f, 1.0f, //
        1.0f, 1.0f, 1.0f, //
        1.0f, 1.0f, 1.0f, //
    };
    auto shape9 = std::make_shared<Shape>(vertices9, colors9);
    shape9->drawLogic = [shape9]() {
        glDrawArrays(GL_LINE_LOOP, 0, shape9->getVertexCount());
    };
    shapes[9] = shape9;

    std::vector<float> vertices10 = {
        -0.7f, 0.8f,  0.0f, //
        0.1f,  0.8f,  0.0f, //
        -0.7f, 0.0f,  0.0f, //

        -0.7f, 0.0f,  0.0f, //
        -0.5f, 0.2f,  0.0f, //
        -0.7f, -0.6f, 0.0f, //

        -0.5f, 0.2f,  0.0f, //
        -0.7f, -0.6f, 0.0f, //
        0.1f,  -0.6f, 0.0f, //

        -0.2f, -0.2f, 0.0f, //
        0.1f,  -0.6f, 0.0f, //
        0.7f,  -0.6f, 0.0f, //

        -0.2f, -0.2f, 0.0f, //
        0.7f,  -0.6f, 0.0f, //
        0.3f,  0.3f,  0.0f, //

        0.7f,  -0.6f, 0.0f, //
        0.3f,  0.3f,  0.0f, //
        0.3f,  0.7f,  0.0f, //

        0.7f,  -0.6f, 0.0f, //
        0.3f,  0.7f,  0.0f, //
        0.7f,  0.5f,  0.0f, //
    };
    std::vector<float> colors10 = {
        0.0f, 0.0f, 1.0f, //
        0.0f, 0.0f, 1.0f, //
        0.0f, 0.0f, 1.0f, //

        0.0f, 1.0f, 0.0f, //
        0.0f, 1.0f, 0.0f, //
        0.0f, 1.0f, 0.0f, //

        0.0f, 1.0f, 1.0f, //
        0.0f, 1.0f, 1.0f, //
        0.0f, 1.0f, 1.0f, //

        1.0f, 0.0f, 0.0f, //
        1.0f, 0.0f, 0.0f, //
        1.0f, 0.0f, 0.0f, //

        1.0f, 0.0f, 1.0f, //
        1.0f, 0.0f, 1.0f, //
        1.0f, 0.0f, 1.0f, //

        1.0f, 1.0f, 0.0f, //
        1.0f, 1.0f, 0.0f, //
        1.0f, 1.0f, 0.0f, //

        1.0f, 1.0f, 1.0f, //
        1.0f, 1.0f, 1.0f, //
        1.0f, 1.0f, 1.0f, //
    };

    // auto shape9 = std::make_shared<Shape>(vertices10, colors10);
    // shape9->drawLogic = [shape9]() {
    //     glDrawArrays(GL_TRIANGLES, 0, shape9->getVertexCount());
    // };
    // shapes[9] = shape9;

    auto shape10 = std::make_shared<Shape>(vertices10, colors10);
    shape10->drawLogic = [shape10]() {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glDrawArrays(GL_TRIANGLES, 0, shape10->getVertexCount());
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    };
    shapes[10] = shape10;

    auto shape11 = std::make_shared<Shape>(vertices10, colors10);
    shape11->drawLogic = [shape11]() {
        glEnable(GL_CULL_FACE);

        glCullFace(GL_FRONT);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glDrawArrays(GL_TRIANGLES, 0, shape11->getVertexCount());

        glCullFace(GL_BACK);
        glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
        glEnable(GL_POINT_SMOOTH);
        glPointSize(10.0f);
        glDrawArrays(GL_TRIANGLES, 0, shape11->getVertexCount());

        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glDisable(GL_CULL_FACE);
    };
    shapes[11] = shape11;

    auto shape12 = std::make_shared<Shape>(vertices10, colors10);
    shape12->drawLogic = [shape12]() {
        glEnable(GL_CULL_FACE);

        glCullFace(GL_FRONT);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glLineWidth(3.0f);
        glDrawArrays(GL_TRIANGLES, 0, shape12->getVertexCount());

        glCullFace(GL_BACK);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glDrawArrays(GL_TRIANGLES, 0, shape12->getVertexCount());

        glDisable(GL_CULL_FACE);
    };
    shapes[12] = shape12;

    auto shape13 = std::make_shared<Shape>(vertices10, colors10);
    shape13->drawLogic = [shape13]() {
        glEnable(GL_CULL_FACE);
        glLineWidth(3.0f);

        glCullFace(GL_FRONT);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glDrawArrays(GL_TRIANGLES, 0, shape13->getVertexCount());

        glCullFace(GL_BACK);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glDrawArrays(GL_TRIANGLES, 0, shape13->getVertexCount());

        glDisable(GL_CULL_FACE);
    };
    shapes[13] = shape13;
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