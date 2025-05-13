#version 460 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 uv;
layout (location = 2) in vec4 atlasTransform;
layout (location = 3) in vec2 voxelTiling;

out vec2 v_UV;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Proj;
void main()
{
	v_UV = (uv * voxelTiling * atlasTransform.zw) + atlasTransform.xy;
	gl_Position = u_Proj * u_View * u_Model * vec4(position, 1.0f);
}