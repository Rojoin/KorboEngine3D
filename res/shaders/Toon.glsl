#shader vertex
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in vec3 aTangent;
layout (location = 4) in vec3 aBitangent;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoords;


uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;



void main()
{
    Normal = mat3(transpose(inverse(model))) * aNormal;
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    FragPos = vec3(model * vec4(aPos, 1.0));
    TexCoords = vec2(aTexCoords.x, aTexCoords.y);
}

#shader fragment
#version 330 core

out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;


uniform sampler2D texture_diffuse1;
uniform sampler2D texture_normal1;
uniform sampler2D texture_baseColor1;
uniform sampler2D texture_height1;
uniform vec3 viewPos;

struct DirLight {
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform DirLight dirLight;
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
struct Material {
    sampler2D texture_baseColor1;
    sampler2D texture_diffuse1;
    sampler2D texture_specular1;
    sampler2D texture_metalness1;
    sampler2D texture_height1;
    float shininess;
    float metalness;
};

#define NR_POINT_LIGHTS 4
uniform Material material;
uniform vec4 ambientColor;
void main()
{

    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);

    vec3 result = CalcDirLight(dirLight, norm, viewDir);

    FragColor = result * texture(texture_diffuse1, TexCoords);

}

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);

    float diff = max(dot(normal, lightDir), 0.0);

    float specular = 0.0;
    if (material.metalness < 0.5) {

        vec3 halfwayDir = normalize(lightDir + viewDir);
        float NdotH = max(dot(normal, halfwayDir), 0.0);
        specular = pow(NdotH, material.shininess);
    } else {

        vec3 reflectDir = reflect(-lightDir, normal);
        specular = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    }

    float lightIntensity = smoothstep(0, 0.01, NdotL);
    
    float lightIntensity = diff > 0 ? 1 : 0;
    vec3 ambient  = light.ambient  * lightIntensity * texture(material.texture_baseColor1);
    vec3 diffuse  = light.diffuse  *  texture(material.texture_diffuse1, TexCoords).rgb;
    vec3 specularColor = light.specular * specular * texture(material.texture_specular1, TexCoords).rgb;

    vec3 light = light.ambient*lightIntensit;

    return (ambient + diffuse + specularColor);
}

