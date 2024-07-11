#version 330 core
out vec4 FragColor;

in vec2 fragUV;
in vec3 geomNormal;
in vec3 fragPos;
in vec4 FragPosLightSpace[10];

uniform sampler2DArray shadowMaps;
uniform vec3 lightPositions[10];

uniform int n_lights;

const float ambient = 0.2f;


float ShadowCalculation(int i)
{
    vec3 projCoords = FragPosLightSpace[i].xyz / FragPosLightSpace[i].w;
    projCoords = projCoords * 0.5 + 0.5;
    float closestDepth = texture(shadowMaps, vec3(projCoords.xy,i)).r; 
    float currentDepth = projCoords.z;
    float shadow = currentDepth > closestDepth  ? (1.0/n_lights) : 0.0;

    return shadow;
}  

void main(){
    vec3 norm = geomNormal;

    float brightness;
    for (int i = 0; i < n_lights; i++)
    {
        float shadow = ShadowCalculation(i);
        float diff = max(0.0f,dot(normalize(lightPositions[i]-fragPos), norm));
        brightness += (diff * (1.0f - shadow) + ambient) / n_lights;
    }

    FragColor = vec4(vec3(brightness),1.0f);
}