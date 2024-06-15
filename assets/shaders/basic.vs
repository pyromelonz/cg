#version 330 core

layout(location = 0) in vec3 aPos;

layout(std140, binding = 0) uniform g_GlobalUniforms {
    mat4 g_ProjectionMatrix;
};
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;

void main() {
    gl_Position = g_ProjectionMatrix * viewMatrix * modelMatrix * vec4(aPos, 1.0);
}