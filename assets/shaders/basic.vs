#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 uv;

out vec2 vUv;
out vec3 vPos;
out vec4 PosLightSpace[10];

uniform mat4 viewMatrix;
uniform mat4 modelMatrix;
uniform mat4 projectionMatrix;
uniform mat4 lightSpaceMatrices[10];
uniform int n_lights;

uniform vec3 objectPosition;

uniform float delta_t;

void main() {
    vec4 objectPosition1 = modelMatrix * vec4(objectPosition, 1.0);
    vec4 aPos1 = modelMatrix * vec4(aPos, 1.0);

    for (int i = 0; i < n_lights; i++) {
        PosLightSpace[i] = lightSpaceMatrices[i] * aPos1;
    }

    aPos1.y += sin(delta_t + (objectPosition1.x * objectPosition1.x) + objectPosition1.z) * 2.0;
    vPos = aPos1.xyz;
    vUv = uv;
    gl_Position = projectionMatrix * viewMatrix * aPos1;
}