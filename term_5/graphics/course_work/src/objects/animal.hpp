#ifndef ANIMAL_HPP
#define ANIMAL_HPP

#include <string>
#include <vector>
#include <memory>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../shader.hpp"
#include "../model.hpp"
#include "../boundary.hpp"

class Animal {
public:
    Animal(const std::string& modelPath, const std::string& texturePath);
    virtual ~Animal();
    
    virtual void update(float deltaTime); // Update animation and AI movement
    virtual void render(Shader& shader); // Render the animal
    
    void setPosition(const glm::vec3& position);
    void setRotation(float rotationAngle);
    void setScale(const glm::vec3& scale);
    void move(const glm::vec3& offset);
    
    glm::vec3 getPosition() const;
    float getRotation() const;
    
protected:
    // Basic components - in a real implementation these would be more complex
    std::unique_ptr<Model> model;
    
    // Transform data
    glm::vec3 position;
    float rotationAngle; // Rotation around Y axis (in radians)
    glm::vec3 scale;
    
    // Animation data
    float animationTime;
    bool isMoving;
    
    // Other common animal properties can be added here
};

// Implementation

Animal::Animal(const std::string& modelPath, const std::string& texturePath) 
    : position(0.0f), 
      rotationAngle(0.0f), 
      scale(glm::vec3(1.0f)),
      animationTime(0.0f),
      isMoving(false) {
    
    // Load model
    model = std::make_unique<Model>(modelPath, texturePath);
}

Animal::~Animal() {
    // Base destructor, nothing specific to clean up
}

void Animal::update(float deltaTime) {
    // Update animation time
    animationTime += deltaTime;
    
    // Base implementation doesn't do much, derived classes will override
}

void Animal::render(Shader& shader) {
    // Calculate model matrix
    glm::mat4 modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, position);
    modelMatrix = glm::rotate(modelMatrix, rotationAngle, glm::vec3(0.0f, 1.0f, 0.0f));
    modelMatrix = glm::scale(modelMatrix, scale);
    
    // Set model matrix in shader
    shader.setMat4("model", modelMatrix);
    
    // Render model
    model->Draw(shader);
}

void Animal::setPosition(const glm::vec3& position) {
    this->position = position;
}

void Animal::setRotation(float rotationAngle) {
    this->rotationAngle = rotationAngle;
}

void Animal::setScale(const glm::vec3& scale) {
    this->scale = scale;
}

void Animal::move(const glm::vec3& offset) {
    // Calculate potential new position
    glm::vec3 newPosition = position + offset;
    
    // Check if new position would be out of bounds
    if (Boundary::isOutOfBounds(newPosition)) {
        // Don't move into water
        return;
    }
    
    // Otherwise, proceed with original code
    position = newPosition;
    
    if (offset.x != 0.0f || offset.z != 0.0f) {
        isMoving = true;
        rotationAngle = atan2(offset.x, offset.z);
    } else {
        isMoving = false;
    }
}

glm::vec3 Animal::getPosition() const {
    return position;
}

float Animal::getRotation() const {
    return rotationAngle;
}

#endif // ANIMAL_HPP