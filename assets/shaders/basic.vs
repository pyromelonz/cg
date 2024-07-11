#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 uv;

out vec2 vUv;
out vec3 vPos;

uniform mat4 viewMatrix;
uniform mat4 modelMatrix;
uniform mat4 g_ProjectionMatrix;

void main() {
    vPos = aPos.xyz;
    vUv = uv;
    gl_Position = g_ProjectionMatrix * viewMatrix * modelMatrix * vec4(aPos, 1.0);
}