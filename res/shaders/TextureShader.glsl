#version 330 core

layout (location = 0) in vec4 position;

uniform mat4 transform;

void main()
{
    gl_Position = transform * position;
};

#version 330 core

layout (location = 0) out vec4 color;
out vec4 FragColor;

uniform vec4 colorTint;
uniform vec2 TexCoord;
uniform sampler2D ourTexture;

void main()
{
    color = vec4(colorTint.x, colorTint.y, colorTint.z, colorTint.w);
    FragColor = texture(ourTexture, TexCoord);
};