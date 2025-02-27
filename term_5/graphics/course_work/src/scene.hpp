#ifndef SCENE_HPP
#define SCENE_HPP

#include <vector>
#include <memory>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.hpp"
#include "camera.hpp"
#include "skybox.hpp"
#include "water.hpp"
#include "terrain.hpp"
#include "objects/animal.hpp"

class Scene {
public:
    Scene();
    ~Scene();

    void initialize();
    void render(const Camera& camera, int screenWidth, int screenHeight);
    void updateDayNightCycle(float time);
    
    void addObject(std::shared_ptr<Animal> object);
    void setTerrain(std::shared_ptr<Terrain> terrain);
    void setWater(std::shared_ptr<Water> water);
    void setSkybox(std::shared_ptr<Skybox> skybox);

private:
    static Scene* instance;

    std::vector<std::shared_ptr<Animal>> objects;
    std::shared_ptr<Terrain> terrain;
    std::shared_ptr<Water> water;
    std::shared_ptr<Skybox> skybox;
    
    // Lighting
    glm::vec3 lightDir;      // Direction of sun/moon
    glm::vec3 lightColor;    // Color of light (changes with day/night)
    float ambientStrength;   // Ambient light level
    
    // Shaders
    std::unique_ptr<Shader> modelShader;
    std::unique_ptr<Shader> terrainShader;
    std::unique_ptr<Shader> waterShader;
};

Scene* Scene::instance = nullptr;

// Implementation

Scene::Scene() 
    : lightDir(glm::vec3(-0.2f, -1.0f, -0.3f)),
      lightColor(glm::vec3(1.0f, 1.0f, 0.9f)),
      ambientStrength(1.f) {
}

Scene::~Scene() {
    // Nothing specific to clean up
}

void Scene::initialize() {
    // Initialize shaders
    modelShader = std::make_unique<Shader>("res/shaders/model.vert", "res/shaders/model.frag");
    terrainShader = std::make_unique<Shader>("res/shaders/terrain.vert", "res/shaders/terrain.frag");
    waterShader = std::make_unique<Shader>("res/shaders/water.vert", "res/shaders/water.frag");
    
    // Load any other resources needed
    std::cout << "Scene initialized successfully" << std::endl;
}

void Scene::render(const Camera& camera, int screenWidth, int screenHeight) {
    // Calculate view/projection matrices
    glm::mat4 view = camera.GetViewMatrix();
    glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), 
                                           (float)screenWidth / (float)screenHeight, 
                                           0.1f, 100.0f);
    
    // Render skybox first
    if (skybox) {
        skybox->render(view, projection);
    }
    
    // Render terrain
    if (terrain) {
        terrainShader->use();
        terrainShader->setMat4("view", view);
        terrainShader->setMat4("projection", projection);
        
        // Set lighting parameters
        terrainShader->setVec3("lightDir", lightDir);
        terrainShader->setVec3("lightColor", lightColor);
        terrainShader->setFloat("ambientStrength", ambientStrength);
        
        terrain->render(*terrainShader);
    }
    
    // Render water
    if (water) {
        waterShader->use();
        waterShader->setMat4("view", view);
        waterShader->setMat4("projection", projection);
        
        // Set lighting parameters
        waterShader->setVec3("lightDir", lightDir);
        waterShader->setVec3("lightColor", lightColor);
        waterShader->setFloat("ambientStrength", ambientStrength);
        
        // Additional water parameters
        waterShader->setFloat("time", glfwGetTime()); // For water animation
        
        water->render(*waterShader);
    }
    
    // Render all objects
    modelShader->use();
    modelShader->setMat4("view", view);
    modelShader->setMat4("projection", projection);
    
    // Set lighting parameters
    modelShader->setVec3("lightDir", lightDir);
    modelShader->setVec3("lightColor", lightColor);
    modelShader->setFloat("ambientStrength", ambientStrength);
    
    for (const auto& object : objects) {
        object->render(*modelShader);
    }
}

void Scene::updateDayNightCycle(float time) {
    // Calculate day/night cycle based on time
    // One complete cycle every 60 seconds
    float cyclePosition = fmod(time, 60.0f) / 60.0f; // 0.0 to 1.0
    
    // Update light direction (sun/moon position)
    float angle = cyclePosition * 2.0f * glm::pi<float>();
    lightDir.x = sin(angle) * 0.7f;
    lightDir.y = -cos(angle);      
    lightDir.z = sin(angle) * 0.7f;
    lightDir = glm::normalize(lightDir);
    
    // Update light color based on time of day
    if (cyclePosition < 0.25f) { // Dawn
        float t = cyclePosition / 0.25f;
        lightColor = glm::mix(glm::vec3(0.2f, 0.2f, 0.6f), glm::vec3(1.0f, 0.9f, 0.7f), t);
        ambientStrength = glm::mix(0.1f, 0.3f, t);
    } 
    else if (cyclePosition < 0.75f) { // Day
        float t = (cyclePosition - 0.25f) / 0.5f;
        lightColor = glm::mix(glm::vec3(1.0f, 0.9f, 0.7f), glm::vec3(1.0f, 0.6f, 0.3f), t);
        ambientStrength = 0.3f;
    } 
    else { // Dusk and night
        float t = (cyclePosition - 0.75f) / 0.25f;
        lightColor = glm::mix(glm::vec3(1.0f, 0.6f, 0.3f), glm::vec3(0.2f, 0.2f, 0.6f), t);
        ambientStrength = glm::mix(0.3f, 0.1f, t);
    }
}

void Scene::addObject(std::shared_ptr<Animal> object) {
    objects.push_back(object);
}

void Scene::setTerrain(std::shared_ptr<Terrain> terrain) {
    this->terrain = terrain;
}

void Scene::setWater(std::shared_ptr<Water> water) {
    this->water = water;
}

void Scene::setSkybox(std::shared_ptr<Skybox> skybox) {
    this->skybox = skybox;
}

#endif // SCENE_HPP