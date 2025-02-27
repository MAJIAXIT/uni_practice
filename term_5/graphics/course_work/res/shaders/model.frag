#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;

uniform sampler2D texture_diffuse1;

// Lighting parameters
uniform vec3 lightDir;
uniform vec3 lightColor;
uniform float ambientStrength;

// Animal flags
uniform bool isAnimal;
uniform bool isDeer;
uniform bool isFox;
uniform bool isRabbit;

void main()
{
    // Ambient light component
    vec3 ambient = ambientStrength * lightColor;
    
    // Diffuse light component
    vec3 norm = normalize(Normal);
    vec3 lightDirection = normalize(-lightDir);
    float diff = max(dot(norm, lightDirection), 0.0);
    vec3 diffuse = diff * lightColor;
    
    // Sample texture
    vec4 texColor = texture(texture_diffuse1, TexCoords);
    
    // Apply lighting to texture
    vec3 result = (ambient + diffuse) * texColor.rgb;
    
    // Apply animal-specific color tweaks
    if (isAnimal) {
        if (isDeer) {
            // Slightly warmer tone for deer
            result.r *= 1.1;
        } else if (isFox) {
            // More vibrant red/orange for fox
            result.r *= 1.2;
            result.g *= 0.9;
        } else if (isRabbit) {
            // Lighter tone for rabbit
            result = mix(result, vec3(1.0), 0.1);
        }
    }
    
    FragColor = vec4(result, texColor.a);
}