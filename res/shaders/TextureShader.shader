#shader vertex 
#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec2 aTexCoord;

uniform mat4 MVP = mat4(1.0f);

out vec4 ourColor;
out vec2 TexCoord;

void main()
{
    gl_Position = MVP * vec4(position, 1.0);
    ourColor = aColor;
    TexCoord = vec2(aTexCoord.x, aTexCoord.y);
}

#shader fragment 
#version 330 core

out vec4 FragColor;

in vec4 ourColor;
in vec2 TexCoord;

uniform sampler2D ourTexture;

void main()
{
    FragColor = texture(ourTexture, TexCoord) * ourColor;
}