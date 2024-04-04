#shader vertex 
#version 330 core

layout(location = 0) in vec4 position;
layout (location = 1) in vec3 aNormal;

out vec3 FragPos;
out vec3 Normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;


void main()
{
    FragPos = vec3(model* position);
    Normal = mat3(transpose(inverse(model))) * aNormal;
	gl_Position = projection * view * vec4(FragPos, 1.0);
};

#shader fragment
#version 330 core

layout(location = 0) 
out vec4 color;
uniform vec4 colorTint;

void main()
{
   color = vec4(colorTint.x,colorTint.y,colorTint.z,colorTint.w);
};