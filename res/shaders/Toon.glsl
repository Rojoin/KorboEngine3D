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

uniform sampler2D texture_baseColor1;
uniform vec3 viewPos;

struct DirLight {
    vec3 direction;
    vec3 color;
    float intensity;
};
uniform DirLight dirLight;

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);

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

    // Final color
    FragColor = result * _Color * texColor;
}

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);

    // Diffuse calculation
    float diff = max(dot(normal, lightDir), 0.0);

    // Specular calculation
    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(normal, halfwayDir), 0.0), _Glossiness * _Glossiness);

    // Rim lighting
    float rim = max(0.0, 1.0 - dot(viewDir, normal));
    rim = smoothstep(_RimAmount - 0.01, _RimAmount + 0.01, rim) * _RimThreshold;

    vec3 color = light.color * (diff + spec) * light.intensity;
    color += rim * vec3(_RimColor);

    return color;
}
