#version 330 core
layout(location = 0) in vec3 aPos;

uniform mat4 lightSpaceMatrix;
uniform mat4 modelMatrix;
uniform vec3 objectPosition;

uniform float delta_t;

void main() {
    vec4 objectPosition1 = modelMatrix * vec4(objectPosition, 1.0);
    vec4 aPos1 = modelMatrix * vec4(aPos, 1.0);

    aPos1.y += sin(delta_t + (objectPosition1.x * objectPosition1.x) + objectPosition1.z) * 2.0;
    gl_Position = lightSpaceMatrix * aPos1;
}