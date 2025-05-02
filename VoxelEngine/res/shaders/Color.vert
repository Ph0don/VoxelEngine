#version 460 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 uv;
layout (location = 2) in vec4 atlasTransform;
layout (location = 3) in vec2 voxelTiling;

out vec2 v_UV;
out vec4 v_AtlasTransform;
out vec2 v_VoxelTiling;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Proj;
void main()
{
	v_UV = uv;
	v_AtlasTransform = atlasTransform;
	v_VoxelTiling = voxelTiling;
	gl_Position = u_Proj * u_View * u_Model * vec4(position, 1.0f);
}