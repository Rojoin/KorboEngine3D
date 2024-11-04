#shader vertex
#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    Normal = mat3(transpose(inverse(model))) * aNormal;
    FragPos = vec3(model * vec4(aPos, 1.0));
    TexCoords = aTexCoords;
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}


#shader fragment
#version 330 core

out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

uniform vec4 _Color;
uniform vec4 _AmbientColor;
uniform vec4 _SpecularColor;
uniform vec4 _RimColor;
uniform float _Glossiness;
uniform float _RimAmount;
uniform float _RimThreshold;
uniform float _LightIntensity;

uniform sampler2D texture_baseColor1;
uniform vec3 viewPos;

uniform float fadeStartDistance;
uniform float fadeEndDistance;

struct DirLight {
    vec3 direction;
    vec3 ambient;
};
uniform DirLight dirLight;

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);

float ditherMatrix[16] = float[16](
0.0, 0.5, 0.125, 0.625,
0.75, 0.25, 0.875, 0.375,
0.1875, 0.6875, 0.0625, 0.5625,
0.9375, 0.4375, 0.8125, 0.3125
);


void main()
{
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);

    // Lighting calculations
    vec3 lightColor = CalcDirLight(dirLight, norm, viewDir);

    // Texture sampling
    vec4 texColor = texture(texture_baseColor1, TexCoords);

    // Apply ambient and color multipliers
    vec4 ambient = _AmbientColor;
    vec4 result = ambient + vec4(lightColor, 1.0);

    vec4 finalColor = result * texColor;

    float distanceToView = length(viewPos- FragPos);
    float fadeFactor = smoothstep(fadeEndDistance, fadeStartDistance, distanceToView);

    if(distanceToView < fadeEndDistance)
    {
        discard;
    }
    //  finalColor.a *= fadeFactor;
    ivec2 screenPos = ivec2(gl_FragCoord.xy) %4;
    int ditherIndex = screenPos.y * 4 + screenPos.x;
    float threshold = ditherMatrix[ditherIndex];


    if (fadeFactor < threshold && finalColor.a != 0)
    {
        finalColor.a = threshold* fadeFactor;
discard;
    }

    FragColor = finalColor;
}

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);

    // Diffuse calculation
    float diff = max(dot(normal, lightDir), 0.0);
    float quantizedDiff= floor(diff * 4.0)/4.0;

    // Specular calculation
    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(normal, halfwayDir), 0.0), _Glossiness * _Glossiness);
    //TODO: Add 3.0 as a Variable
    float quantizedSpec = floor(spec * 3.0)/3.0;

    // Rim lighting
    float rim = max(0.0, 1.0 - dot(viewDir, normal));
    rim = smoothstep(_RimAmount - 0.01, _RimAmount + 0.01, rim) * _RimThreshold;

    vec3 color = light.ambient * (quantizedDiff + quantizedSpec) * _LightIntensity;
    color += rim * vec3(_RimColor);

    return color;
}
