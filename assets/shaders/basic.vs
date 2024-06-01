#version 330 core

layout (location = 0) in vec3 aPos;
void main(){
    gl_Position = MVP * vec4(aPos.x, aPos.y, aPos.z, 1.0);
}

layout (location = 1) uniform mat4 VP_Matrix;
layout (location = 2) uniform mat4 M_Matrix