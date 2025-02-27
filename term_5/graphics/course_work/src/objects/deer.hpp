#ifndef DEER_HPP
#define DEER_HPP

#include "animal.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <cmath>

class Deer : public Animal {
public:
    Deer(const std::string& modelPath, const std::string& texturePath);
    ~Deer() override;
    
    void update(float deltaTime) override;
    void render(Shader& shader) override;
    
private:
    // Animation parameters for deer-specific movements
    float legAngle;
    float headBobAngle;
    float tailSwingAngle;
    
    // Animation speeds
    float legAnimSpeed;
    float headBobSpeed;
    float tailSwingSpeed;
};

// Implementation

Deer::Deer(const std::string& modelPath, const std::string& texturePath)
    : Animal(modelPath, texturePath),
      legAngle(0.0f),
      headBobAngle(0.0f),
      tailSwingAngle(0.0f),
      legAnimSpeed(5.0f),
      headBobSpeed(2.0f),
      tailSwingSpeed(3.0f) {
    
    // Set deer-specific scale
    setScale(glm::vec3(0.3f));
}

Deer::~Deer() {
    // Nothing to clean up specifically for Deer
}

void Deer::update(float deltaTime) {
    // Call base class update
    Animal::update(deltaTime);
    
    // Update animation parameters
    if (isMoving) {
        // Legs animation (walking/running)
        legAngle = sin(animationTime * legAnimSpeed) * 0.25f;
        
        // Head bobbing animation
        headBobAngle = sin(animationTime * headBobSpeed) * 0.1f;
        
        // Tail swinging animation
        tailSwingAngle = sin(animationTime * tailSwingSpeed) * 0.3f;
    } else {
        // Idle animations
        legAngle = sin(animationTime * 0.5f) * 0.05f;
        headBobAngle = sin(animationTime * 0.7f) * 0.05f;
        tailSwingAngle = sin(animationTime * 1.2f) * 0.1f;
    }
}

void Deer::render(Shader& shader) {
    // Set animation parameters in the shader before rendering
    shader.setFloat("legAngle", legAngle);
    shader.setFloat("headBobAngle", headBobAngle);
    shader.setFloat("tailSwingAngle", tailSwingAngle);
    shader.setBool("isAnimal", true);
    shader.setBool("isDeer", true);
    
    // Call base class render
    Animal::render(shader);
}

#endif // DEER_HPP