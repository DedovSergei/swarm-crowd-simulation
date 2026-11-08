#version 430 core
in vec3 Color;
in vec3 Normal;
out vec4 FragColor;
void main() {
    // Simple Lighting, kept mild (between 0.6 and 1.0) so the agents keep the legend's colours
    vec3 lightDir = normalize(vec3(0.2, -0.5, 1.0));
    float diff = max(dot(Normal, lightDir), 0.0);
    FragColor = vec4(Color * mix(0.6, 1.0, diff), 1.0);
}
