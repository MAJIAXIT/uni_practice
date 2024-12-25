#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

int WinWidth = 800;
int WinHeight = 600;

using namespace std;

void framebufferSizeCallback(GLFWwindow *window, int w, int h);
void windowSizeCallback(GLFWwindow *window, int w, int h);
void processInput(GLFWwindow *window);

const char *vertexShaderSource = R"(
#version 330 core
layout(location = 0) in vec3 aPos;     // Position of the vertex
layout(location = 1) in vec3 aColor;   // Color of the vertex
out vec3 vertexColor; // Output a color to the fragment shader

void main()
{
    gl_Position = vec4(aPos, 1.0); // Set the position of the vertex
    vertexColor = aColor;          // Pass the color to the fragment shader
}
)";

const char *fragmentShaderSource = R"(
#version 330 core
in vec3 vertexColor; // Input color from the vertex shader
out vec4 FragColor;  // Output color of the fragment

void main()
{
    FragColor = vec4(vertexColor, 1.0); // Set the fragment color
}
)";

const float vertices[] = {
    // First triangle (red)
    -0.9f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // Bottom-left
    -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,  // Top-left
    -0.1f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // Bottom-right

    // Second triangle (green)
    0.1f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // Bottom-left
    0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f,  // Top-left
    0.9f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // Bottom-right

    // Third triangle (blue)
    -0.3f, -0.9f, 0.0f, 0.0f, 0.0f, 1.0f, // Bottom-left
    0.0f, -0.3f, 0.0f, 0.0f, 0.0f, 1.0f,  // Top-center
    0.3f, -0.9f, 0.0f, 0.0f, 0.0f, 1.0f   // Bottom-right
};
