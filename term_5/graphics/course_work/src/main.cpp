#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <vector>
#include <string>
#include <memory>

#include "shader.hpp"
#include "camera.hpp"
#include "scene.hpp"
#include "objects/animal.hpp"
#include "objects/deer.hpp"
#include "objects/fox.hpp"
#include "objects/rabbit.hpp"
#include "skybox.hpp"
#include "water.hpp"
#include "terrain.hpp"
#include "boundary.hpp"

// Window dimensions
const unsigned int SCR_WIDTH = 1280;
const unsigned int SCR_HEIGHT = 720;

// Camera
Camera camera(glm::vec3(0.0f, 2.0f, 10.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// Timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

// Scene management
std::unique_ptr<Scene> scene;

// Controls for deer
bool moveForward = false;
bool moveBackward = false;
bool moveLeft = false;
bool moveRight = false;

// Function prototypes
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

int main() {
    // Initialize GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // Create window
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Forest Wildlife Sanctuary", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetKeyCallback(window, key_callback);

    // Tell GLFW to capture mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Configure global OpenGL state
    glEnable(GL_DEPTH_TEST);

    // Create and initialize scene
    scene = std::make_unique<Scene>();
    
    // Load textures and models
    scene->initialize();
    
    // Create animals
    std::shared_ptr<Deer> deer = std::make_shared<Deer>("res/models/deer.glb", "res/textures/deer.png");
    std::shared_ptr<Fox> fox = std::make_shared<Fox>("res/models/fox.glb", "res/textures/fox.png");
    std::shared_ptr<Rabbit> rabbit = std::make_shared<Rabbit>("res/models/rabbit.glb", "res/textures/rabbit.png");
    
    // Position animals
    deer->setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
    fox->setPosition(glm::vec3(5.0f, 0.0f, -3.0f));
    rabbit->setPosition(glm::vec3(-4.0f, 0.0f, -2.0f));
    
    // Add animals to scene
    scene->addObject(deer);
    scene->addObject(fox);
    scene->addObject(rabbit);
    
    // Create environment
    std::shared_ptr<Terrain> terrain = std::make_shared<Terrain>("res/textures/grass.png", 50.0f, 50.0f);
    Boundary::setTerrainDimensions(50.0f, 50.0f); // The same values passed to terrain
    std::shared_ptr<Water> water = std::make_shared<Water>("res/textures/water.png", 500.0f, 500.0f);
    std::shared_ptr<Skybox> skybox = std::make_shared<Skybox>("res/textures/skybox");
    
    // Add environment to scene
    scene->setTerrain(terrain);
    scene->setWater(water);
    scene->setSkybox(skybox);
    
    // Render loop
    while (!glfwWindowShouldClose(window)) {
        // Per-frame time logic
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Input
        processInput(window);
        
        // Update deer movement based on user input
        glm::vec3 deerMovement(0.0f);
        if (moveForward)
            deerMovement.z -= 1.0f;
        if (moveBackward)
            deerMovement.z += 1.0f;
        if (moveLeft)
            deerMovement.x -= 1.0f;
        if (moveRight)
            deerMovement.x += 1.0f;
        
        if (glm::length(deerMovement) > 0.0f) {
            deerMovement = glm::normalize(deerMovement) * 5.0f * deltaTime;
            deer->move(deerMovement);
        }
        
        // Update animations
        deer->update(deltaTime);
        fox->update(deltaTime);
        rabbit->update(deltaTime);
        
        // Update day/night cycle
        scene->updateDayNightCycle(currentFrame);

        // Clear buffers
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Render scene
        scene->render(camera, SCR_WIDTH, SCR_HEIGHT);

        // Swap buffers and poll events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Clean up
    scene.reset();
    glfwTerminate();
    return 0;
}

// Process input
void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    // Camera movement
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}

// Process keyboard input for deer movement
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        switch (key) {
            case GLFW_KEY_UP:
                moveForward = true;
                break;
            case GLFW_KEY_DOWN:
                moveBackward = true;
                break;
            case GLFW_KEY_LEFT:
                moveLeft = true;
                break;
            case GLFW_KEY_RIGHT:
                moveRight = true;
                break;
        }
    } else if (action == GLFW_RELEASE) {
        switch (key) {
            case GLFW_KEY_UP:
                moveForward = false;
                break;
            case GLFW_KEY_DOWN:
                moveBackward = false;
                break;
            case GLFW_KEY_LEFT:
                moveLeft = false;
                break;
            case GLFW_KEY_RIGHT:
                moveRight = false;
                break;
        }
    }
}

// Callback for window resize
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    int framebufferWidth, framebufferHeight;
    glfwGetFramebufferSize(window, &framebufferWidth, &framebufferHeight);
    
    glViewport(0, 0, framebufferWidth, framebufferHeight);
}

// Callback for mouse movement
void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // Reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// Callback for mouse scroll
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    camera.ProcessMouseScroll(yoffset);
}