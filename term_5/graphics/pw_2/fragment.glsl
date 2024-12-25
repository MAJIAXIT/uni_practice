#version 330 core
in vec3 fragColor;  // Receive color from vertex shader

out vec4 color;

void main() {
    color = vec4(fragColor, 1.0);  // Set output color with alpha = 1.0
}
