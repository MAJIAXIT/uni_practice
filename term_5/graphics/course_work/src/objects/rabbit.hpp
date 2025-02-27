#ifndef RABBIT_HPP
#define RABBIT_HPP

#include "animal.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <cmath>
#include <random>

class Rabbit : public Animal {
public:
    Rabbit(const std::string& modelPath, const std::string& texturePath);
    ~Rabbit() override;
    
    void update(float deltaTime) override;
    void render(Shader& shader) override;
    
private:
    // Animation parameters for rabbit-specific movements
    float earAngle;
    float hopHeight;
    
    // Animation speeds
    float earAnimSpeed;
    float hopAnimSpeed;
    
    // AI movement
    glm::vec3 movementDirection;
    float timeSinceDirectionChange;
    float directionChangeInterval;
    
    // Hopping state
    bool isHopping;
    float hopProgress;
    float hopDuration;
    float restDuration;
    float timeInCurrentState;
    float originalY;  // Base Y position (ground level)
    
    // Helper method to randomize movement direction
    void randomizeDirection();
};

// Implementation

Rabbit::Rabbit(const std::string& modelPath, const std::string& texturePath)
    : Animal(modelPath, texturePath),
      earAngle(0.0f),
      hopHeight(0.0f),
      earAnimSpeed(4.0f),
      hopAnimSpeed(3.0f),
      timeSinceDirectionChange(0.0f),
      directionChangeInterval(2.0f),
      isHopping(false),
      hopProgress(0.0f),
      hopDuration(0.6f),
      restDuration(1.2f),
      timeInCurrentState(0.0f) {
    
    // Set rabbit-specific scale
    setScale(glm::vec3(0.2f));
    
    // Initialize resting position
    originalY = position.y;
    
    // Initialize movement direction
    movementDirection = glm::vec3(0.0f);
    randomizeDirection();
}

Rabbit::~Rabbit() {
    // Nothing to clean up specifically for Rabbit
}

void Rabbit::update(float deltaTime) {
    // Call base class update
    Animal::update(deltaTime);
    
    // Update AI behavior
    timeInCurrentState += deltaTime;
    
    if (isHopping) {
        // Handle hopping animation
        hopProgress = timeInCurrentState / hopDuration;
        
        if (hopProgress >= 1.0f) {
            // Finished hopping, enter rest state
            isHopping = false;
            timeInCurrentState = 0.0f;
            hopProgress = 0.0f;
            
            // Ensure we're on the ground
            position.y = originalY;
        } else {
            // Update hop height using sine curve for smooth up and down
            hopHeight = sin(hopProgress * glm::pi<float>()) * 0.4f;
            position.y = originalY + hopHeight;
            
            // Move forward during hop
            move(movementDirection * deltaTime * 4.0f);
        }
    } else {
        // Resting between hops
        if (timeInCurrentState >= restDuration) {
            // Time to hop again
            isHopping = true;
            timeInCurrentState = 0.0f;
            
            // Pick a new direction sometimes
            timeSinceDirectionChange += restDuration;
            if (timeSinceDirectionChange >= directionChangeInterval) {
                randomizeDirection();
                timeSinceDirectionChange = 0.0f;
            }
        }
    }
    
    // Update animation parameters
    if (isHopping) {
        // Hopping animations - ears back during hop
        earAngle = -0.2f + sin(hopProgress * glm::pi<float>() * 2) * 0.1f;
    } else {
        // Idle animations - ear twitching
        earAngle = sin(animationTime * earAnimSpeed) * 0.1f;
    }
}

void Rabbit::render(Shader& shader) {
    // Set animation parameters in the shader before rendering
    shader.setFloat("earAngle", earAngle);
    shader.setFloat("hopHeight", hopHeight);
    shader.setBool("isAnimal", true);
    shader.setBool("isRabbit", true);
    shader.setBool("isHopping", isHopping);
    
    // Call base class render
    Animal::render(shader);
}

void Rabbit::randomizeDirection() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution<float> dis(-1.0f, 1.0f);
    static std::uniform_real_distribution<float> probability(0.0f, 1.0f);
    
    // Small chance of changing direction
    if (probability(gen) < 0.7f) {
        // Random direction (only on XZ plane)
        movementDirection = glm::vec3(dis(gen), 0.0f, dis(gen));
        
        // Normalize if not zero
        if (glm::length(movementDirection) > 0.0f) {
            movementDirection = glm::normalize(movementDirection);
        }
    }
}

#endif // RABBIT_HPP