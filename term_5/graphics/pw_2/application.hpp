#pragma once
#include "renderer.hpp"
#include "window.hpp"
#include <map>
#include <memory>

class Application {
  private:
    std::unique_ptr<Window> window;
    std::unique_ptr<Renderer> renderer;

    static void keyCallback(GLFWwindow *window, int key, int scancode,
                            int action, int mods);

  public:
    Application();
    ~Application();

    bool init();
    void run();
    void cleanup();
};

Application::Application()
    : window(std::make_unique<Window>(800, 600, "pw_2")),
      renderer(std::make_unique<Renderer>()) {}

Application::~Application() { cleanup(); }

bool Application::init() {
    if (!window->init()) {
        return false;
    }

    glfwSetWindowUserPointer(window->getHandle(), this);
    glfwSetKeyCallback(window->getHandle(), keyCallback);

    renderer->init();
    return true;
}

void Application::run() {
    while (!window->shouldClose()) {
        glfwPollEvents();
    }
}

void Application::cleanup() { renderer->cleanup(); }

void Application::keyCallback(GLFWwindow *window, int key, int scancode,
                              int action, int mods) {
    if (action != GLFW_PRESS)
        return;

    auto app = static_cast<Application *>(glfwGetWindowUserPointer(window));
    
    glClear(GL_COLOR_BUFFER_BIT);

    switch (key) {
    case GLFW_KEY_1:
        app->renderer->render(1);
        break;
    case GLFW_KEY_2:
        app->renderer->render(2);
        break;
    case GLFW_KEY_3:
        app->renderer->render(3);
        break;
    case GLFW_KEY_4:
        app->renderer->render(4);
        break;
    case GLFW_KEY_5:
        app->renderer->render(5);
        break;
    case GLFW_KEY_6:
        app->renderer->render(6);
        break;
    case GLFW_KEY_7:
        app->renderer->render(7);
        break;
    case GLFW_KEY_8:
        app->renderer->render(8);
        break;
    case GLFW_KEY_9:
        app->renderer->render(9);
        break;
    case GLFW_KEY_0:
        app->renderer->render(10);
        break;
    case GLFW_KEY_Q:
        app->renderer->render(11);
        break;
    case GLFW_KEY_W:
        app->renderer->render(12);
        break;
    case GLFW_KEY_E:
        app->renderer->render(13);
        break;
    case GLFW_KEY_ESCAPE:
        glfwSetWindowShouldClose(window, true);
        break;
    }

    glfwSwapBuffers(window);
}