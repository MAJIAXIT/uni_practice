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

void main()
{
    // Ambient light component
    vec3 ambient = ambientStrength * lightColor;
    
    // Diffuse light component
    vec3 norm = normalize(Normal);
    vec3 lightDirection = normalize(-lightDir);
    float diff = max(dot(norm, lightDirection), 0.0);
    vec3 diffuse = diff * lightColor;
    
    // Get texture color
    vec4 texColor = texture(texture_diffuse1, TexCoords);
    
    // Apply lighting
    vec3 result = (ambient + diffuse) * texColor.rgb;
    
    FragColor = vec4(result, 1.0);
}