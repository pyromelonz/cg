#version 330 core

layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

in vec2 vUv[];
in vec3 vPos[];

out vec3 fragPos;
out vec2 fragUv;
out vec3 geomNormal; // Output geometry normal to fragment shader

void main() {

    vec3 edge1 = vPos[2] - vPos[0];
    vec3 edge2 = vPos[1] - vPos[0];

    geomNormal = normalize(cross(edge1, edge2));
    for (int i = 0; i < 3; ++i) {
        gl_Position = gl_in[i].gl_Position;
        fragPos = vPos[i];
        fragUv = vUv[i];
        EmitVertex();
    }
    
    EndPrimitive();
}