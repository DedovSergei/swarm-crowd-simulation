#version 430 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in float aRiser;   // a step riser the overlay paints (src/viewer/scene.cpp)

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 Normal;
out vec3 WorldPos;   // for the heatmap overlay's cell lookup (stadium.frag)
out float Riser;

void main() {
    Normal = mat3(transpose(inverse(model))) * aNormal;
    WorldPos = vec3(model * vec4(aPos, 1.0));
    Riser = aRiser;
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}
