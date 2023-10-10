#shader vertex 
#version 330 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec2 aTexCoord;
uniform mat4 transform;

void main()
{
    gl_Position = transform * position;
    TexCoord = aTexCoord;
};

#shader fragment 
#version 330 core


out vec4 FragColor;
in vec2 TexCoord;

uniform vec4 colorTint;

uniform sampler2D ourTexture;

void main()
{
    FragColor = texture(ourTexture, TexCoord);
};