#version 330 core

in vec2 fTexCoord;

out vec4 Color;

uniform sampler2D uTex;

void main()
{
	Color = texture(uTex, fTexCoord);
}