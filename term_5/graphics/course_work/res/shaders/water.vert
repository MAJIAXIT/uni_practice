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

// Water animation parameters
uniform float time;
uniform float waveSpeed;
uniform float waveStrength;

void main()
{
    // Animate water with sine waves
    vec3 pos = aPos;
    
    // Create moving waves in X and Z directions
    float waveX = sin(aTexCoords.x * 10.0 + time * waveSpeed) * waveStrength;
    float waveZ = cos(aTexCoords.y * 10.0 + time * waveSpeed) * waveStrength;
    
    // Apply waves to Y position
    pos.y += waveX + waveZ;
    
    // Calculate new normal based on waves
    vec3 normal = aNormal;
    normal.x -= waveX * 10.0;
    normal.z -= waveZ * 10.0;
    normal = normalize(normal);
    
    // Pass data to fragment shader
    TexCoords = aTexCoords + vec2(sin(time * 0.05), cos(time * 0.05)) * 0.01; // Slowly moving texture
    FragPos = vec3(model * vec4(pos, 1.0));
    Normal = mat3(transpose(inverse(model))) * normal;
    
    gl_Position = projection * view * model * vec4(pos, 1.0);
}