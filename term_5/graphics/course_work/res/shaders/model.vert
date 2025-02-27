#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec2 TexCoords;
out vec3 Normal;
out vec3 FragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

// Animation variables
uniform float legAngle;
uniform float headBobAngle;
uniform float tailSwingAngle;
uniform float earAngle;
uniform float hopHeight;
uniform float tailSwishAngle;
uniform float earTwitchAngle;
uniform bool isDeer;
uniform bool isFox;
uniform bool isRabbit;
uniform bool isHopping;

void main()
{
    vec3 pos = aPos;
    vec3 normal = aNormal;
    
    // Animal-specific animations
    // This is a simplified implementation - in a real project, 
    // you would have a more sophisticated animation system
    
    if (isDeer) {
        // Apply deer animations (simplified)
        if (pos.y > 0.5) {
            // Head area
            pos.y += sin(headBobAngle) * 0.05;
        } else if (pos.x > 0.2 || pos.x < -0.2) {
            // Legs
            pos.y += sin(legAngle) * 0.1;
        }
    } else if (isFox) {
        // Apply fox animations (simplified)
        if (pos.y > 0.5 && pos.z < -0.3) {
            // Tail area
            pos.y += sin(tailSwishAngle) * 0.08;
            pos.x += cos(tailSwishAngle) * 0.05;
        } else if (pos.y > 0.5 && pos.x > 0.15) {
            // Ear area
            pos.y += sin(earTwitchAngle) * 0.05;
        }
    } else if (isRabbit) {
        // Apply rabbit animations (simplified)
        if (pos.y > 0.3 && pos.y < 0.6) {
            // Ear area
            pos.y += sin(earAngle) * 0.1;
        }
        
        // Apply hopping animation if the rabbit is hopping
        if (isHopping) {
            pos.y += hopHeight;
        }
    }
    
    TexCoords = aTexCoords;
    FragPos = vec3(model * vec4(pos, 1.0));
    Normal = mat3(transpose(inverse(model))) * normal;
    
    gl_Position = projection * view * model * vec4(pos, 1.0);
}