#version 330 core
out vec4 FragColor;

in vec2 fragUV;
in vec3 geomNormal;
in vec3 fragPos;

const float ambient = 0.2f;

void main(){
    vec3 norm = geomNormal;

    float diff = max(0.0f,dot(norm, normalize(vec3(2.0f,-1.0f,-0.5f))));

    FragColor = vec4(vec3(ambient + diff),1.0f);
}