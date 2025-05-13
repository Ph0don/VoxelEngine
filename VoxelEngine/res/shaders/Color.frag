#version 460 core
in vec2 v_UV;
out vec4 FragColor;

uniform sampler2D tex;
uniform float u_col;

void main()
{
	FragColor = texture2D(tex, v_UV, 1);
}