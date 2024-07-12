#version 330 core
out vec4 FragColor;

in vec2 fragUv;
in vec3 geomNormal;
in vec3 fragPos;
in vec4 FragPosLightSpace[10];

uniform sampler2D squareTexture;
uniform sampler2DArray shadowMaps;
uniform vec3 lightPositions[10];
uniform vec3 lightColors[10];
uniform vec3 viewPos;

uniform int n_lights;

const float ambient = 0.2f;

void main(){

    vec3 light = vec3(0.0f);
    for (int i = 0; i < n_lights; i++)
    {
        vec3 lightDir = normalize(lightPositions[i] - fragPos);
        //diffuse lighting
        float diff = max(0.0f,dot(lightDir, geomNormal));
        
        //shadow calculation
        float shadow;
        {
            vec3 projCoords = FragPosLightSpace[i].xyz / FragPosLightSpace[i].w;
            projCoords = projCoords * 0.5 + 0.5;
            float closestDepth = texture(shadowMaps, vec3(projCoords.xy,i)).r; 
            float currentDepth = projCoords.z;
        
            float bias = 0.005; //max(0.02 * (1.0 - diff), 0.005); 
            shadow = currentDepth - bias > closestDepth  ? 1.0 : 0.0;
        }

        //specular
        float spec;
        {
            vec3 viewDir = normalize(viewPos - fragPos);
            float spec = 0.0;
            vec3 halfwayDir = normalize(lightDir + viewDir);  
            spec = pow(max(dot(geomNormal, halfwayDir), 0.0), 64.0);
        }
        //add to color
        light += ((diff * (1.0f - shadow) + ambient)+spec) * lightColors[i];

    }
    vec3 color =  (light) * (texture(squareTexture, fragUv).rgb );

    FragColor = vec4(color,1.0f);
}