#version 330 core

layout (location = 0) in vec3 vPos;
layout (location = 1) in vec2 vTexCoord;

out vec2 fTexCoord;

uniform mat4 uMVP;

void main()
{
  gl_Position = uMVP * vec4(vPos, 1);
  fTexCoord = vTexCoord;
}
