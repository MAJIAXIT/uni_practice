#ifndef FOX_HPP
#define FOX_HPP

#include "animal.hpp"
#include <vector>
#include <glm/gtc/matrix_transform.hpp>
#include <cmath>
#include <random>

class Fox : public Animal {
public:
    Fox(const std::string& modelPath, const std::string& texturePath)
        : Animal(modelPath, texturePath),
          legAngle(0.0f),
          tailSwishAngle(0.0f),
          earTwitchAngle(0.0f),
          legAnimSpeed(6.0f),
          tailSwishSpeed(4.0f),
          earTwitchSpeed(3.0f),
          timeSinceDirectionChange(0.0f),
          directionChangeInterval(3.0f) {
        
        // Set fox-specific scale
        setScale(glm::vec3(0.2f));
        
        // Initialize movement direction
        movementDirection = glm::vec3(0.0f);
        randomizeDirection();
    }
    
    ~Fox() override {}
    
    void update(float deltaTime) override {
        // Call base class update
        Animal::update(deltaTime);
        
        // Update AI behavior
        timeSinceDirectionChange += deltaTime;
        if (timeSinceDirectionChange >= directionChangeInterval) {
            randomizeDirection();
            timeSinceDirectionChange = 0.0f;
        }
        
        // Move the fox according to its current direction
        if (glm::length(movementDirection) > 0.0f) {
            isMoving = true;
            move(movementDirection * deltaTime * 2.0f);
        } else {
            isMoving = false;
        }
        
        // Update animation parameters
        if (isMoving) {
            // Running/walking animations
            legAngle = sin(animationTime * legAnimSpeed) * 0.3f;
            tailSwishAngle = sin(animationTime * tailSwishSpeed) * 0.4f;
            earTwitchAngle = sin(animationTime * earTwitchSpeed) * 0.1f;
        } else {
            // Idle animations
            legAngle = sin(animationTime * 0.8f) * 0.05f;
            tailSwishAngle = sin(animationTime * 1.5f) * 0.2f;
            earTwitchAngle = sin(animationTime * 2.0f) * 0.05f;
        }
    }
    
    void render(Shader& shader) override {
        // Set animation parameters in the shader before rendering
        shader.setFloat("legAngle", legAngle);
        shader.setFloat("tailSwishAngle", tailSwishAngle);
        shader.setFloat("earTwitchAngle", earTwitchAngle);
        shader.setBool("isAnimal", true);
        shader.setBool("isFox", true);
        
        // Call base class render
        Animal::render(shader);
    }
    
private:
    // Animation parameters for fox-specific movements
    float legAngle;
    float tailSwishAngle;
    float earTwitchAngle;
    
    // Animation speeds
    float legAnimSpeed;
    float tailSwishSpeed;
    float earTwitchSpeed;
    
    // AI movement
    glm::vec3 movementDirection;
    float timeSinceDirectionChange;
    float directionChangeInterval;
    
    // Helper method to randomize movement direction
    void randomizeDirection() {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_real_distribution<float> dis(-1.0f, 1.0f);
        static std::uniform_real_distribution<float> probability(0.0f, 1.0f);
        
        // Small chance of stopping
        if (probability(gen) < 0.2f) {
            movementDirection = glm::vec3(0.0f);
            return;
        }
        
        // Random direction (only on XZ plane)
        movementDirection = glm::vec3(dis(gen), 0.0f, dis(gen));
        
        // Normalize if not zero
        if (glm::length(movementDirection) > 0.0f) {
            movementDirection = glm::normalize(movementDirection);
        }
    }
};

#endif // FOX_HPP