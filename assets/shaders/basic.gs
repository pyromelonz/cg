#version 430 core

layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

in vec2 vUv[];
in vec3 vPos[];
in vec4 PosLightSpace[][10];

out vec4 FragPosLightSpace[10]; // Output light space position to fragment shader
out vec3 fragPos; // Output position to fragment shader
out vec2 fragUv; // Output uv to fragment shader
out vec3 geomNormal; // Output geometry normal to fragment shader

void main() {

    vec3 edge1 = vPos[2] - vPos[0];
    vec3 edge2 = vPos[1] - vPos[0];

    geomNormal = normalize(cross(edge1, edge2));
    for (int i = 0; i < 3; ++i) {
        gl_Position = gl_in[i].gl_Position;
        fragPos = vPos[i];
        fragUv = vUv[i];
        for (int j = 0; j < 10; ++j) {
            FragPosLightSpace[j] = PosLightSpace[i][j];
        }
        EmitVertex();
    }
    
    EndPrimitive();
}