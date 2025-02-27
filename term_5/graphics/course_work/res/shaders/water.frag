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

// Water animation parameters
uniform float time;

void main()
{
    // Ambient light component
    vec3 ambient = ambientStrength * lightColor;
    
    // Diffuse light component
    vec3 norm = normalize(Normal);
    vec3 lightDirection = normalize(-lightDir);
    float diff = max(dot(norm, lightDirection), 0.0);
    vec3 diffuse = diff * lightColor;
    
    // Specular light (water is reflective)
    vec3 viewDir = normalize(-FragPos); // Camera is at origin in view space
    vec3 reflectDir = reflect(-lightDirection, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = 0.5 * spec * lightColor;
    
    // Get texture color with ripple effect
    vec2 texCoord = TexCoords + sin(time * 0.5 + TexCoords.x * 10.0 + TexCoords.y * 10.0) * 0.01;
    vec4 texColor = texture(texture_diffuse1, texCoord);
    
    // Enhance blue color for water
    texColor.rgb = mix(texColor.rgb, vec3(0.0, 0.3, 0.7), 0.5);
    
    // Apply lighting
    vec3 result = (ambient + diffuse + specular) * texColor.rgb;
    
    // Add some transparency to water
    FragColor = vec4(result, 0.8);
}