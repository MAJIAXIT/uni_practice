#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

class Window {
  private:
    GLFWwindow *window;
    int width;
    int height;
    std::string title;

  public:
    Window(int width, int height, const std::string &title);
    ~Window();

    bool init();
    bool shouldClose() const;
    GLFWwindow *getHandle() const { return window; }

    static void framebufferSizeCallback(GLFWwindow *window, int width,
                                        int height);
};

Window::Window(int width, int height, const std::string &title)
    : width(width), height(height), title(title), window(nullptr) {}

Window::~Window() {
    if (window) {
        glfwDestroyWindow(window);
    }
    glfwTerminate();
}

bool Window::init() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        return false;
    }

    return true;
}

bool Window::shouldClose() const { return glfwWindowShouldClose(window); }

void Window::framebufferSizeCallback(GLFWwindow *window, int width,
                                     int height) {
    glViewport(0, 0, width, height);
}