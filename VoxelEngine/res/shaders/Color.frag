#version 460 core
in vec2 v_UV;
in vec4 v_AtlasTransform;
in vec2 v_VoxelTiling;
out vec4 FragColor;

uniform sampler2D tex;
uniform float u_col;

void main()
{
	vec2 tiledUV = fract(v_UV * v_VoxelTiling) * v_AtlasTransform.zw;
	FragColor = texture(tex, (tiledUV + v_AtlasTransform.xy));
}