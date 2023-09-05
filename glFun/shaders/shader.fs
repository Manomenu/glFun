#version 330 core

out vec4 FragColor;

// in vec2 TexCoord;

// uniform sampler2D texture1;
uniform vec3 objectColor;
uniform vec3 lightColor;

void main()
{
    // FragColor = texture(texture1, vec2(1.0 - TexCoord.x, TexCoord.y));
    FragColor = vec4(lightColor * objectColor, 1.0);
};